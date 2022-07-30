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

10. 
