1. ad移动文件   mv [file] [directory]

2. 环境变量
   - vim ~/.bashrc 只对当前用户生效的环境变量
   - source ~/.bashrc 使修改的环境变量马上生效

3. 软件安装
   - deb ： dpkg -i **.deb

4. 查看磁盘空间
   - df -hl

5. 关机 ： sudo shutdown -r now / sudo reboot

6. ADB
   -  adb push 电脑路径  手机存储路径  
   - adb push models/female_motion.fbx /sdcard/iris/female_motion.fbx
   - 查看移动端cpu架构 ： adb shell getprop ro.product.cpu.abi

7. 工程调试
   - core 下运行 ./gradlew assembleDebug --debug  查看编译细节
   - ./scripts/makepush.ps1 debug arm64 -pl

8. apt-file
   - 用于查看缺少的某个文件属于哪个依赖库、包
   - 用法：
     - apt-file search xxx
     - 安装上一步返回的查询结果

9. vscode
   - 代码格式化：Ctrl+Shift+I

10. zip解压缩 unzip

11. adb调试
    - 手机重启之后：adb root  \  adb remount
    - adb install -t IrisUISample.apk  测试版
    - adb uninstall com.irisview.irisxr 卸载
    - adb shell am start com.irisview.irisxr/.MainActivity  启动
    - adb shell am force-stop com.irisview.irisxr  关闭
    - adb shell setenforce 0 vr每次重新开机之后输入
    - adb forward tcp:8081 tcp:8081     [http://localhost:8081/](http://localhost:8081/)
    - adb shell pm clear com.irisview.irisxr  清除irisxr程序cache的数据
    - adb shell dumpsys battery
    - ./scripts/core/graphics_core_build.sh  编译 compositor
    - ./scripts/makepush.ps1 release arm64 -m g -p -sh "am start -S com.irisview.irisxr/.MainActivity" -r window  编译+替换+运行
    - adb shell su 0 pm list packages 获取应用包名
    - adb shell getprop | grep ro.product.build.type 获取rom版本
    - adb shell am start com.android.settings 连接wifi
    - watch -n 0.5 adb shell cat /sys/class/kgsl/kgsl-3d0/gpu_busy_percentage  gpu占用
    - adb shell atrace -t 5 -b 80960 -z gfx input view wm sm am audio hal res power pm ss database aidl sched freq idle sync ion memreclaim -a com.irisview.irisxr -o /sdcard/trace.html     抓trace
    - priority_tool priority tid rt 99 设置线程优先级到最高 []
    - du -a ./ | sort -n -r | head -n 20  磁盘最大文件
    - adb shell "input keyevent 223" 灭屏指令
    
    
    
12. 手势

    - YVR手势开关 ：  adb shell setprop persist.tracking.hand.enable true

13. 查看崩溃行数

    adb logcat -d|ndk-stack -sym .

    ndk-stack -sym . -i /home/lijiaxiang/Desktop/log.txt 

    adb logcat | $NDK/ndk-stack -sym $PROJECT_PATH/obj/local/armeabi-v7a

    ./scripts/makepush.ps1 release arm64 -pl

    addr2line -Cfe xxx.so 00000000001bef84

    查找so，按时间排序：find -name libirisui.so -print0| xargs -0 stat --format '%Y:%y %n' | sort -n

14. 内存

    watch -n 1 adb shell dumpsys meminfo com.irisview.irisxr

15. 判断一个库、可执行文件是debug版本还是release版本

    readelf -S libassimp.so | grep debug

    如果release 版本，不会打印出任何信息

16.編譯UISAMPLE ： /Work/iris/sdk/web/uisample$ ./gradlew assembleDebug

17.repo 

​	repo 多git 指令

​	repo forall -c "git rev-parse --show-toplevel && git status"

18.android 模块编译

​	./scripts/core/android_deploy_build.sh 

19.log转换    **清理控制字符并转换**

使用 `tr` 或 `sed` 过滤不可见字符：

```
cat 0317_1538.log | tr -cd '\11\12\15\40-\176' | iconv -f ASCII -t UTF-8//IGNORE > output_utf8.txt
```

- **作用**：
  - `tr -cd ...`：仅保留 ASCII 可打印字符（空格、换行符、常规文本）。
  - `iconv`：二次清理非 UTF-8 字符。
- **适用场景**：文件包含大量控制字符（如终端日志）。







vr Launcher start open app





20号的rom开始 加上了SAR sensor+ 眼动双重检测息屏亮屏功能，可以通过

adb root

adb remount

adb shell setprop persist.sar.screencontrol 0
adb shell setprop persist.eyedetect.enable 0 

命令来关闭该检测

