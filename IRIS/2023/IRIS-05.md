**手势交互一期功能实现**

1. poke
   - 食指推动按钮
   - 食指滑动scroll view
   - **视觉手**
   - **食指点击产生事件**

2. snap
   - 碰撞：snap时，手指碰撞后，停止；伸展时，手指恢复动画；
   - transformer： 物体跟随手移动

3. grip **TODO**

4. 手势功能优化+bugfix **12-13**
   - 使用碰撞体、连续碰撞检测，替换短射线方案，解决snap过程中速度过快导致手势不自然贴合物体表面问题和poke时速度快无法贴合问题；
   - poke时，手指粘连问题 : 临时使用向量点乘解决；**DONE**
   - Poke与Snap冲突  

5. 支持当前引擎已有的所有交互事件（Interactable）；
   - aim 不需要支持
   - click
   - axis 未发现使用
   - hold ： 具体行为不清楚；
   - scroll 安卓底层实现，未发现使用；具体行为是android底层实现；
   - drag ： 射线中，射线拖拽UI; poke或Snap中，不适合实现拖拽UI； 

6. 触发事件

   控制器：手柄输入+射线

   模拟手：碰撞检测+手柄输入

   识别手：碰撞检测+手势？？？

7. 轴如何使用

   


手势接入：

- 骨骼重定向产生了动画扭曲、外观变形的问题：

   - 拇指食指不能捏合问题 
   - 四指正常并拢时，iris中手势模型，四指会挤向中间；

   需要重新绑定骨骼： 重新调整各个关节的偏移量；

**复刻occulus手势交互**

1. visual studio + unity 调试occulus interaction sdk 
2. 复刻occulus sdk 提供的 samples

目前实现手捏物体交互，物体跟随手移动、旋转；
存在的问题：

- interactor / interactable整体架构不完善
- 手捏物体时，检测算法不精确，手指运动越快，穿模程度越重；

后续优先实现poke食指按按钮交互效果、GRAB 手握物体效果；

**识别手数据驱动**

- XrHandJointLocationsEXT
- 提供动画设置关节transform接口，接入及驱动手模型  





