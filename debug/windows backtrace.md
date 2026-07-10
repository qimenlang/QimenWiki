Windows 上抓 backtrace 有从"最省事"到"最深入"四条路。你的场景（进程直接跑 OK，ctest / VSCode launch 崩）大概率不是内存 
  bug，而是环境差异——所以推荐先用能保留崩溃时环境的方式取栈。

  先给你排个优先级：

  ┌──────────────────────────────────┬──────────────────────────────────────────┬──────┐
  │               场景               │                 推荐工具                 │ 难度 │
  ├──────────────────────────────────┼──────────────────────────────────────────┼──────┤
  │ 只想快速看栈                     │ procdump + Visual Studio                 │ ★    │
  ├──────────────────────────────────┼──────────────────────────────────────────┼──────┤
  │ 想让代码自己打栈                 │ C++23 std::stacktrace + 未处理异常过滤器 │ ★★   │
  ├──────────────────────────────────┼──────────────────────────────────────────┼──────┤
  │ 系统级自动落 dump                │ WER LocalDumps 注册表                    │ ★★   │
  ├──────────────────────────────────┼──────────────────────────────────────────┼──────┤
  │ 深入分析（heap 损坏、gflags 等） │ WinDbg / cdb + PageHeap                  │ ★★★  │
  └──────────────────────────────────┴──────────────────────────────────────────┴──────┘

  你项目里根 CMakeLists.txt 有 CMAKE_CXX_STANDARD 23，方案 B（std::stacktrace）几乎是零成本，我会重点讲这个。

---
  方案 A：procdump（不改代码，最快）

  Sysinternals 里的小工具，不用装 VS 完整版：

  # 下载：https://learn.microsoft.com/sysinternals/downloads/procdump
  # -e 只在未处理异常时抓；-ma 完整 dump；> 追踪日志
  procdump -accepteula -e -ma -x C:\dumps UnitTest.exe -s --verbosity high

  崩溃后：
  - 拿到 C:\dumps\UnitTest.dmp
  - 用 Visual Studio 打开 .dmp（File → Open → Crash Dump Analysis）
  - 点右侧 "使用仅限本机调试"，直接看到崩溃线程 + 完整调用栈 + 源码定位（前提是 build 时开了 /Zi 且 .pdb 还在原路径）。

  用 ctest 触发时把 procdump 挂在 exe 前面：

  find_program(PROCDUMP procdump)
  if(PROCDUMP)
      add_test(NAME ${TARGET_NAME}
          COMMAND ${PROCDUMP} -accepteula -e -ma -x ${CMAKE_BINARY_DIR}/dumps
                  $<TARGET_FILE:${TARGET_NAME}> -s --verbosity high)
  endif()

---
  方案 B：C++23 std::stacktrace（推荐，永久留在代码里）

  你已经开 C++23，MSVC 19.34+（VS 2022 17.4+）原生支持 <stacktrace>。加一段全局初始化，无论谁怎么起进程都能拿到栈：

  // framework/crash_handler.cpp
  #include <stacktrace>
  #include <iostream>
  #include <fstream>
  #include <windows.h>

  static LONG WINAPI zeusCrashFilter(EXCEPTION_POINTERS* info)
  {
      auto st = std::stacktrace::current();
      auto msg = std::to_string(st);

      std::cerr << "\n=== Unhandled exception 0x"
                << std::hex << info->ExceptionRecord->ExceptionCode
                << " at " << info->ExceptionRecord->ExceptionAddress << " ===\n"
                << msg << std::endl;
    
      std::ofstream("crash_backtrace.txt") << msg;
      return EXCEPTION_EXECUTE_HANDLER;   // 让进程正常退出，写完盘
  }

  struct InstallCrashHandler {
      InstallCrashHandler() { SetUnhandledExceptionFilter(zeusCrashFilter); }
  };
  static InstallCrashHandler _install;

  CMake 侧只需要：

  target_link_libraries(${TARGET_NAME} PRIVATE ...)
  # MSVC 下 std::stacktrace 需要这两个库
  if(MSVC)
      target_link_libraries(${TARGET_NAME} PRIVATE Advapi32.lib)
  endif()

  # 必须有调试符号，否则栈里只有地址
  target_compile_options(${TARGET_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/Zi>)
  target_link_options(${TARGET_NAME} PRIVATE $<$<CXX_COMPILER_ID:MSVC>:/DEBUG /INCREMENTAL:NO>)

  崩了之后 stderr 和 crash_backtrace.txt 里都是函数名 + 文件 + 行号（前提 .pdb 在 exe 同目录或 _NT_SYMBOL_PATH 指到）：

  0# ZeusEngine::render(...) at engine/runtime/render.cpp:142
  1# TEST_CASE_...::test() at engine/rendering_test/cases/basic.cpp:37
  2# Catch::TestInvokerAsFunction::invoke() at catch2/...
  ...

  用 ctest -V 就能直接看到这段输出，不用再找 dump。

  ▎ Catch2 自己也有信号处理器，可能吃掉 SEH。启动时用 --allow-running-no-tests --no-signals 或在 CLI 参数里加 -e（禁用异常捕获）能规避。 

---
  方案 C：WER LocalDumps（系统级自动落 dump）

  不用装 procdump，Windows 自带：

  # 管理员 PowerShell
  $key = "HKLM:\SOFTWARE\Microsoft\Windows\Windows Error Reporting\LocalDumps\UnitTest.exe"
  New-Item -Path $key -Force | Out-Null
  New-ItemProperty -Path $key -Name DumpFolder -PropertyType ExpandString -Value "C:\dumps" -Force
  New-ItemProperty -Path $key -Name DumpType   -PropertyType DWord        -Value 2         -Force  # 2=Full
  New-ItemProperty -Path $key -Name DumpCount  -PropertyType DWord        -Value 10        -Force

  之后任何来源（ctest、VSCode、双击）导致 UnitTest.exe 未处理异常都会自动落到 C:\dumps\UnitTest.exe.<pid>.dmp。用 VS 打开即可。

  优点：对进程零侵入，不改 exe 也不改 ctest 命令。缺点：要管理员权限，且需要事后清理 dump。

---
  方案 D：WinDbg / cdb（重症用）

  命令行直接跑，遇异常自动断下：

  cdb -g -G -o -c "!analyze -v; kb; q" UnitTest.exe -s --verbosity high > cdb.log

  kb 是栈，!analyze -v 是自动诊断。适合怀疑堆损坏、栈溢出时配合 gflags /p /enable UnitTest.exe
  /full（PageHeap）用，能把随机崩变成"访问越界立刻崩"。

---
  但先别急着抓栈——这个模式非常可疑

  你描述的**"直接跑 OK，ctest/launch 崩"**，backtrace 出来八成会指向下面之一：

  1. CWD 不同：直接双击 exe 的 CWD 是 exe 目录；ctest 的 CWD 是你运行 ctest 的目录（一般是 build 根目录）；VSCode 的"启动"和"调试"CWD    
    又可能不同。你的引擎里如果有 fopen("shaders/xxx.glsl") 这种相对路径加载，另一个 CWD 就是空指针崩溃。

    - 验证：add_test 里显式设 CWD
  set_tests_properties(${TARGET_NAME} PROPERTIES
      WORKING_DIRECTORY $<TARGET_FILE_DIR:${TARGET_NAME}>)
    - 若这样就好了，就是 CWD 问题。
  2. PATH 差异：debugger 会继承 VSCode 的完整 PATH（含 Vulkan SDK、Qt bin 等），"启动"和 ctest 拿到的可能是精简 PATH。某些 dll
    在静态析构阶段才被延迟加载（比如 Vulkan Loader 卸载 ICD），此时找不到 dll 就崩在退出路径上——现象正是"用例跑完了、断言过了、才崩"。     

    - 验证：Process Monitor 过滤 Result != SUCCESS + Path contains .dll，能一眼看到崩前谁 NAME NOT FOUND。
  3. 静态析构顺序：Catch2 全局对象析构 vs VSG/vulkan device 析构 vs 你的引擎单例析构，顺序不同会不同崩法。debugger
    下堆检查更严格但反而有时能让指针"暂时还活着"。

    - 验证：在你自己 main 末尾（或 fixture 析构里）显式 engine.shutdown()，看是否消失。

  栈抓出来后，关键看崩在 ExitProcess / _cexit / dll_unload 
  附近还是业务代码里，能立刻区分是"跑的时候崩"还是"退出时崩"，这两种问题方向完全不同。

---
  我的建议顺序

  1. 先在 add_test 里加 WORKING_DIRECTORY $<TARGET_FILE_DIR:UnitTest>，ctest -C Debug -V 再跑一次。如果好了，问题结束。
  2. 没好，就加方案 B（std::stacktrace + 未处理异常过滤器），十分钟落地，ctest -V 直接打出栈。
  3. 栈还看不出来（比如崩在纯地址），再上**方案 A（procdump）**拿 dump 到 VS 里翻。

  要不要我帮你把方案 B 的完整代码 + CMake 配置写成一个可直接 include 的头文件？告诉我一下：Catch2 版本（v2 还是
  v3？影响它自己的信号处理是否要关），以及编译器是 MSVC 还是 clang-cl。