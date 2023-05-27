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
    - adb shell pm clear com.irisview.irisxr  
    - adb shell dumpsys battery
    - ./scripts/core/graphics_core_build.sh  编译 compositor
    
12. 内存

    watch -n 1 adb shell dumpsys meminfo com.irisview.irisxr

13. 判断一个库、可执行文件是debug版本还是release版本

    readelf -S libassimp.so | grep debug

    如果release 版本，不会打印出任何信息



1.仅使用关节点的rotation数据，驱动iris的手模型，存在整体变形的问题：

![Screenshot_from_2023-05-16_13-44-56](/uploads/079a87d2f5586a920f98baf05358a3a4/Screenshot_from_2023-05-16_13-44-56.png)

2.使用关节点的rotation+position数据，驱动iris手模型，并且对iris手模型重新刷权重，每个关节点影响的mesh顶点范围尽可能的大，得到如下效果：

- proximal关节处还存在变形
- ![Screenshot_from_2023-05-24_21-07-01](/uploads/8db0eb3112abfecb187ac76dc06daf18/Screenshot_from_2023-05-24_21-07-01.png)
-   -- 在爱奇艺设备中实时驱动，存在拇指与中指、无名指、小指无法捏合的问题且整体效果存在变形；























