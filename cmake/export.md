## 总结：vsgXchange 的导出宏与 CMake

### `Export.h` 的作用

在 Windows/MinGW 上，给对外 API 选对可见性属性；非 Windows 则宏为空。

```c
VSGXCHANGE_DECLSPEC =
  vsgXchange_EXPORTS 已定义     → __declspec(dllexport)  // 正在造 DLL
  VSGXCHANGE_SHARED_LIBRARY 已定义 → __declspec(dllimport) // 正在用 DLL
  否则                          → 空                     // 静态库 / 非 Windows
```

类/函数写成 `class VSGXCHANGE_DECLSPEC Foo`，由上述分支决定导出还是导入。

---

### 各宏何时定义、做什么

| 宏                                                 | 谁定义                                                      | 何时有                                                       | 作用                                   |
| -------------------------------------------------- | ----------------------------------------------------------- | ------------------------------------------------------------ | -------------------------------------- |
| `vsgXchange_EXPORTS`                               | **CMake 默认**（`DEFINE_SYMBOL`）                           | 编译 **SHARED** target `vsgXchange` 自己的源码时             | 让 `DECLSPEC` → `dllexport`            |
| `VSGXCHANGE_SHARED_LIBRARY`                        | CMake 显式：`target_compile_definitions(... INTERFACE ...)` | `BUILD_SHARED_LIBS=ON`，且下游 `target_link_libraries` 了该库 | 让消费者 `DECLSPEC` → `dllimport`      |
| （无静态专用宏）                                   | —                                                           | 静态构建时上面两个都不定义                                   | `DECLSPEC` 为空，静态库正确行为        |
| `VSGXCHANGE_STATIC_LIBRARY` / `XXX_LIBRARY_STATIC` | **本库没有**                                                | —                                                            | 别的库自己的命名；名字不同就不是同一宏 |

`INTERFACE`：宏只传给**链接者**，不传给库自己编译单元（避免和 `EXPORTS` 搅在一起）。

---

### CMake 相关默认机制

1. **`add_library(vsgXchange ...)` 不写 SHARED/STATIC**  
   由 `BUILD_SHARED_LIBS` 决定：`ON` → DLL，`OFF` → 静态库。

2. **SHARED target 自动 `DEFINE_SYMBOL`**  
   默认是 `<target名>_EXPORTS` → 这里即 `vsgXchange_EXPORTS`。只作用于**编这个库**。

3. **本库再补一层消费者宏**  
   ```cmake
   if (BUILD_SHARED_LIBS)
     target_compile_definitions(vsgXchange INTERFACE VSGXCHANGE_SHARED_LIBRARY)
   endif()
   ```

4. **`add_library(vsgXchange::vsgXchange ALIAS vsgXchange)`**  
   只是命名别名，方便链接；不定义任何导出宏。

---

### 三条场景对照

| 场景             | `vsgXchange_EXPORTS` | `VSGXCHANGE_SHARED_LIBRARY` | `VSGXCHANGE_DECLSPEC` |
| ---------------- | -------------------- | --------------------------- | --------------------- |
| 编共享库自身     | ✅                    | 通常不加（INTERFACE）       | `dllexport`           |
| 链接共享库的应用 | ❌                    | ✅（INTERFACE 传播）         | `dllimport`           |
| 静态库（编或用） | ❌                    | ❌                           | 空                    |

---

### 和其他库命名的关系

`XXX_LIBRARY_STATIC` 与 `XXX_STATIC_LIBRARY` **不是同一宏**，只是常见“静态库标记”的不同起名。以各库自己的 `Export.h` + CMake 为准；vsgXchange 用「有无共享宏」区分，不靠静态宏。