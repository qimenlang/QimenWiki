#### 手势高通版本[10.11]

1. 手势相关bug
2. 手模型材质调整：半透明效果+边缘高亮
3. 手势射线交互优化：使用手腕关节点作为射线原点
4. checkfoucs server端检测事件，分发给client端；

#### controller重构

1. 需求分析

   - 样式定制
     - controller模型\line\cursor\pointer配置	
       - cursor的状态，由交互对象状态、当前交互类型等决定
       - 模型数据
         - 实时手势检测
         - 手柄、手模型文件
     - 为SE Client提供样式定制接口
   - 交互状态机
     - controller 动画状态机：手柄模拟手、手柄模型
     - cursor及line的状态： default\hover\press
     - 状态机输入：事件、交互对象状态
   - replace Controller
     - 系统维护一个controller列表，应用启动时，如果应用包含controller,则添加进列表中；
     - controller含有应用白名单包含自身应用、共享应用；
     - replaceController时，激活对应Controller，同一时间只有一个Controller激活
     - 手柄与手势的切换

2. 架构设计

   - 类设计
     - controller manager
       - 6DOF Handler Controller
       - touch screen\ mouse Controller
       - Hand Gesture Controller
     - Device Manager
       - 6DOF Handler Device
       - touch screen\ mouse device
       - Hand Gesture Virtual Device
     - Interactor component
       - PokeInteractor
       - PinchInteractor
       - GripInteractor
       - RayInteractor
         - line / cursor / pointer

3. 重构计划

   1. 将cursor / line 重构到RayInteractor中，RayInteractor同时支持handlerController和GestureController
   2. 直接交互事件检测整理，同时支持手和手柄，增加VirtualDeviceEventCaster
   3. controller 和 interactor 移到 irisengineUI/irisengine中，在WindowManager中继承controller和interactor，并且将inputDeviceManager替换为iris::InputManagerClient；方便在irisEditor中对controller和interactor进行测试。

4. 测试

   - 测试组进行回测
   - 在IrisEditor中搭建测试场景/虚拟仿真测试/自动化测试

   

   