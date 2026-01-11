### **本地编译流程**：

1. **下载源码** → 从 GitHub 等源码仓库下载
2. **解压到特定目录** → 通常是 `buildtrees/[库名]/src/`
3. **配置编译选项** → 根据你的平台、架构、编译工具链
4. **编译二进制文件** → 调用 CMake、MSBuild、make 等工具
5. **安装到 vcpkg 目录** → 头文件、库文件分别放到特定位置



Ports中可以配置各种库的版本、下载路径等；



vcpkg bash中临时会话

```
export VCPKG_MAX_CONCURRENCY=8 //8核编译
export VCPKG_PLATFORM_TOOLSET=v143 //指定编译器
//v142 → Visual Studio 2019;v143 → Visual Studio 2022;v144 → Visual Studio 2023
```