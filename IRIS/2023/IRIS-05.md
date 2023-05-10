**手势交互一期功能实现**

1. poke
   - 食指推动按钮
   - 食指滑动scroll view
   - **视觉手**
   - **食指点击产生事件**
   
2. snap
   - 碰撞：snap时，手指碰撞后，停止；伸展时，手指恢复动画；
   - transformer： 物体跟随手移动

3. grip

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
- 



