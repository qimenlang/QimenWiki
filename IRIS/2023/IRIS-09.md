

**2023 8/9双月OKR**

- O1 : 在高通 AR 眼镜设备上，完成系统基础手势交互的实现。目标用于8月高通演示 Demo  [O1-KR1]
  - KR1：直接交互相关bug跟进，交互成功率95%以上；
  - KR2 : 间接交互测试、合入 ；
  - KR3 : 关节点驱动Mesh
  - KR4 : **手势模型材质达到美术要求；** 
- O2 : 支持多人场景使用手交互效果，保证关节点的显示。目标用于8月高通演示 Demo  [O1-KR2] **DONE** 
  - KR1 : 多人场景手势直接交互、间接交互
  - KR2 : 多人场景手势关节点显示
- O3 : 完善基础手势交互体验
  - KR1 : UI事件体系更新
  - **KR2 : 对比quest interaction , 针对性复刻quest  Interaction demo** 
  - KR3 : 
- O4 : 动画系统功能迭代，对标RealityKit，优先满足vivo需求 [O1-KR6]
  - KR1 : 支持动画事件
  - KR2 : 支持基础动画
  - KR3 : 已有接口对标reality kit接口进行改造
  - KR4 : 使用reality kit动画接口，做一些简单demo 
  - KR5 : **cache2 CI实践**



返回动画播放状态

#### UI事件体系更新

1. vr视觉反馈 ： 物体旋转到手掌固定轴，dragbar怎么旋转？

2. 间接交互状态下，不应该显示射线，什么是pointer？  **不显示。**

3. 对interactable提供交互，对只含有collider的object，是否提供默认的平移旋转缩放？ **对Interactable提供默认的平移旋转缩放。**

   - dragbar在处理drag、hold事件时，对平移旋转进行了特殊处理。

4. 对android应用，如何交互。

5. 射线的事件和手势的事件不应该分开处理，且不应该区分射线事件和手势事件；

   -   **所有事件统一在一个EventCaster中做分发；**
   - 根据检测方式的不同，区分为DirectEventCaster和IndirectEventCaster.
     - DirectEventCaster : 检测数据只需要collider 
     - IndirectEventCaster : 射线检测，检测数据包含collider,worldpos,worldNormal等；
   - RayCatstResults 信息WorldNormal\LocalNormal等填不满的问题
     - **先overlap，再从相机位置发射线检测，填充RayCastResults；[临时方案]**
     - 事件参数中，不使用RayCatstResults，替换为更通用的检测结果结构体；
   - 事件参数信息：继续沿用之前的事件参数，再增加一个 DirectInteraction/Indirectinteraction enum值；
   - 为每个事件定义一个轴；

6. 所有事件统一在trackedInputDeviceEventCaster中分发，trackedInputDeviceEventCaster不应该负责collider的检测，collider的检测由device（或者interactor\射线)进行；

7. collider检测的职责

   - 在直接/间接交互中，先由interactor检测到交互对象，再触发轴事件；因此collider检测由interactor负责
   - 在手柄射线交互中，先由手柄触发事件，再由trackedeventcaster检测交互对象，collider的检测由trackedeventcaster负责；

8. EventCaster分发事件逻辑

   - 不断检测交互对象，raycast\overlap；
   - 轴事件上报之后，根据轴的类型、数据内容，分类为不同事件；
   - 触发交互对象的对应事件；

9. 交互检测类型，交互检测逻辑放在interactor中；

   - raycast 
   - overlap
   - sweep

10. 轴数据与事件的转换关系

   - 事件名称： Tap、Hold、Drag、Snap、Throw、Resize、Rotate、HoverWithHold
   - 事件类型：
     - 瞬时事件：仅触发一次轴数据更新
     - 持续事件 ：触发之后需要不断更新轴数据，进而持续的invoke对应的 handler callback;
   - 轴定义需要与目前的手柄事件分发TrackeDeviceEventCaster兼容吗
     - 由于仅能通过手柄trigger触发，目前的TrackeDeviceEventCaster的Hold、Drag、Click事件使用的是同一个轴，存在一个轴更新同时触发两个事件（drag、hold）的可能
   - 转换关系 

| 事件名称 | 事件类型   | 轴定义               | 触发条件                       |
| -------- | ---------- | -------------------- | ------------------------------ |
| Hover    | 瞬时       | input/gesture/hover  | 触碰既触发                     |
| Tap      | 瞬时       | input/gesture/tap    | 触碰既触发，仅一次             |
| Press    | 持续       | input/gesture/press  | 触碰之后，一直触发             |
| Hold     | 持续       | input/gesture/hold   | 一直overlap300ms以上           |
| Drag     | 持续       | input/gesture/drag   | 位移或者角位移，超过阈值       |
| resize   | 持续、双手 | input/gesture/resize | 两个检测器，均overlap超过300ms |

   

11. 交互状态转换 ： Disabled <-> Normal <-> Hover <-> Select

    - disabled
    - default ： 检测器未检测到交互对象
    - hover : 检测器检测到交互对象[在hover状态进入select的过程中，不能实时更新hover对象，因为改过程伴随检测器的移动，可能hover对象被移除]；
    - select ： 与交互对象完成交互，已经触发对应交互逻辑

    interactor\ineractable都有这四个状态，并且interactor与interactable的状态会同步变化；

12. VRX相关

    1. **vxr手势与所有应用的交互测试**
    2. VRX交互BUG测试 
       - **[project/irisview-xr2.1#1949] tmp fix crash on vrx. 需要revert继续查  DONE **；
       - 直接交互象棋dragbar拖动时，有可能直接关闭象棋应用；
       - RayInteractor drag/hold不是100%触发；
       - Poke连续触发；
    3. **rayInteractor** 
       - 射线方向改为以头控为原点，连向掌心；
       - 头控固定方向
       - 以掌心关节点为原点
    4. 手势调用重置功能; 
    5. **VRX手柄手势切换**  
    6. 棋子释放（手势检测失败）之后，棋子不要立即被放下

13. server端处理事件的逻辑梳理

    - window = 进程

14. VRX展示

    - 直接交互象棋稳定的问题

    - VRX 手柄切换

    - 直接交互时，间接交互控件隐藏

15. 















reality kit animation system 梳理

| reality kit Animation功能列表 |                             | reality kit                           | irisengine         |
| ----------------------------- | --------------------------- | ------------------------------------- | ------------------ |
| **Playback**                  |                             |                                       |                    |
|                               | AnimationPlayBackController |                                       | Y                  |
|                               | **AnimationEvents**         | 动画事件                              | N                  |
|                               | AnimationRepeatMode         |                                       | N                  |
| **Animation Resources**       |                             |                                       |                    |
|                               | AnimationResource           |                                       |                    |
| **Animation definitions**     |                             |                                       |                    |
|                               | **SampledAnimation**        | 采样动画，支持对指定数据进行采样      | N                  |
|                               | FromToByAnimation           |                                       | N                  |
|                               | **AnimationTimingFunction** | 定义动画过渡，ease in、 ease out 等； | N                  |
|                               | AnimationView               | 对动画进行重新配置                    | N                  |
|                               | OrbitAnimation              | 轨道动画                              | N                  |
|                               | AnimationDefinition         | #                                     | N                  |
|                               | AnimationFillMode           |                                       | N                  |
|                               | AnimationGroup              |                                       | N                  |
|                               | AnimationHandoffType        |                                       | N                  |
| **Blend Trees**               |                             |                                       | 功能不完善，待补充 |
|                               | BlendTreeAnimation          |                                       | Y                  |
|                               | BlendTreeNode               |                                       | Y                  |
|                               | BlendTreeBlendNode          |                                       | N                  |
|                               | BlendTreeSourceNode         |                                       | Y                  |
|                               | BlendTreeInvalidNode        |                                       | N                  |



reality composer能生产动画资源,平移旋转缩放，也支持骨骼动画。

1. reality kit的动画系统，侧重于基础动画，而非角色动画。我们是否有基础动画的需求？
2. reality kit的动画系统架构设计很灵活，可以参考
3. irisengine动画系统的迭代目标是reality kit还是unity/unreal
4. 使用reality kit动画接口，做一些简单demo 















