1. 防止osg与imgui之间的渲染状态相互污染

   - ImGui 作为 2D UI，需要关闭深度测试，并设置特定的混合函数;
   - 如果在osg的渲染指令执行过程中，执行了imgui的渲染指令，会导致二者相互污染；
   - 解决方案：
     - imgui作为一个单独的HUD Pass ,在所有Pass的最后执行，相机的 `draw` 回调中，必须**手动保存/恢复** OSG 的状态属性
       - 可以通过 `osg::State` 的 `captureCurrentState()` 和 `applyStateSet()` 来保存和恢复状态。
       - 状态保存、恢复的开销，远小于上下文切换和离屏渲染合成；
     - osg渲染指令中间插入了imgui渲染指令时，强制保存、恢复osg的渲染状态，
     - 上下文隔离：imgui与osg都单独上下文
       - 两个上下文渲染到同一个窗口，每帧需要切换上下文，耗时几微秒到几十微秒
     - **使用离屏渲染合成**：OSG 渲染到离屏帧缓冲（FBO），ImGui 渲染到另一个 FBO，最后合成到窗口。

2. 事件系统适配

   - osg事件处理机制：osgGA::GUIEventHandler
   - 事件路由：鼠标点击imgui控件时，事件如何传递到imgui,并且osg不对事件进行处理；点击到osg场景物体时，imgui不应该获得焦点；
   - 坐标系统：osg鼠标原点在左下角，imgui原点在左上角
   - 键盘输入的映射

3. 线程安全问题

   - osg线程模式：
     - SingleThreaded：单线程串行
     - CullDrawThreadPerContext：每个上下文一个线程，执行cull\draw；
     - DrawThreadPerContext:主线程update\cull，每个上下文一个draw线程
     - CullThreadPerCameraDrawThreadPerContext:每个相机一个cull线程，每个上下文一个draw线程；
   - imgui不是线程安全的，应该只在主线程调用 ImGui，或关闭 OSG 多线程

4. 

