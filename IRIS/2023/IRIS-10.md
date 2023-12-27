#### 手势高通版本[10.11]

1. 手势相关bug
2. 手模型材质调整：半透明效果+边缘高亮
3. 手势射线交互优化：使用手腕关节点作为射线原点
4. checkfoucs server端检测事件，分发给client端；

#### controller重构

1. 需求分析

   - 样式定制
     - controller
       - 由handler、cursor、Indicator三部分组成，这三个类共用一套状态转换逻辑、事件处理逻辑；	
         - handler模型数据
           - 实时手势检测
           - 手柄、手模型文件
         - cursor的状态，由交互对象状态、当前交互类型等决定
         - Indicator
       - 负责状态管理 
     - 为SE Client提供Controller定制接口
       - 样式定制 : 从配置文件以固定格式配置资源路径；
       - 事件定制
   - 交互状态机
     - controller 动画状态机：手柄模拟手、手柄模型
     - cursor及line的状态： default\hover\press
     - 状态机输入：事件、交互对象状态
   - Controller功能
     - 
   - replace Controller
     - 系统维护一个controller列表，应用启动时，如果应用包含controller,则添加进列表中；
     - controller含有应用白名单包含自身应用、共享应用；
     - replaceController时，激活对应Controller，同一时间只有一个Controller激活
     - 手柄与手势的切换
     - SE、CSE、应用三方Controller切换的逻辑梳理
       - 替换SceneObject
         - 应用自定义样式，先屏蔽已有事件响应，再自定义事件响应，[device 信息直接暴露给应用？]
         - 缺点：客戶端事件响应相較於服務器端，會有一點延遲
       - 应用直接调用创建Controller接口（解析json，json中定义样式、需要屏蔽的轴）
         - 系统定义样式，系统定义事件响应；
         - 

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

   1. controller/cursor/interactor重构
      - Cursor、Indicator 重构，保留SceneCursor、OverlayCursor，分离CursorIndicator
      - RayInteractor使用SceneCursor
      - Controller重构 ，保留ModelController、HandController 、GestureController;
        - HandlerController 高亮、模型动画、材质动画
        - GestureController 实时动画数据
      - 重构CursorManager、ModelControllerManager、RealTimeHandControllerManager，只保留ControllerManager
      - RayInteractor同时支持handlerController和GestureController
      - 为SE Client提供样式定制接口
      - ReplaceController 功能
   2. controller与白名单应用交互，通过设置layer实现[CommonState]
   3. 直接交互事件检测整理，同时支持手和手柄，增加VirtualDeviceEventCaster
   4. controller 和 interactor 移到 irisengineUI/irisengine中，在WindowManager中继承controller和interactor，并且将inputDeviceManager替换为iris::InputManagerClient；方便在irisEditor中对controller和interactor进行测试

4. 测试

   - 测试组进行回测
   - 在IrisEditor中搭建测试场景/虚拟仿真测试/自动化测试

   

   