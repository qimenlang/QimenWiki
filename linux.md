1. 移动文件   mv [file] [directory]
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
   - 
7. 工程调试
   - core 下运行 ./gradlew assembleDebug --debug  查看编译细节
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
    - adb shell am start -s com.irisview.irisxr/.MainActivity   启动
    - adb shell am force-stop com.irisview.irisxr  关闭
    - adb forward tcp:8081 tcp:8081     [http://localhost:8081](http://localhost:8081/)
    - 