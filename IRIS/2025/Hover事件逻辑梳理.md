1. 关键需求：
   - 眼手交互时，一手pinch，眼动能继续hover；
   - 手柄射线交互时，手柄pinch，无法继续hover；
   - 按下状态的手柄，无法hover；（对空白位置Pinch时，Client端无法收到轴事件，设备状态管理）
   - FusionUI组件无基础事件互斥，Hover 不能被中断；
2. Hover设计
   - 按键按下时，设备invoker中断触发Hover Update；Invoker有Idle态、Press态；
   - 事件互斥时，交互对象不能被触发Hover Update；交互对象有Idle态、Press态；
   - 
3. Iris Hover逻辑梳理
   - 不同交互模式：眼手（眼动的hover事件在手势invoker中触发）、手柄
   - 事件互斥：对不同类型对象FusionUI、SceneObject，单设备事件中断、不中断Hover事件
   - 不同交互对象：
     - 优先级覆盖：优先锁定交互对象的Hover,覆盖实时检测对象的Hover
   - Hover 事件与Select事件分离：按下任意按键之后，不再触发Hover ，中断已触发的Hover Update
4. 交互模式
   - 单个设备的Hover
     - 对实时检测对象触发hover,设备触发其他事件后，根据交互对象类型决定是否中断hover update
   - 多个设备的hover
     - 允许多个设备对同一个交互对象分别触发hover;
   - 眼手：在双手的invoker中触发hover，但只触发一次；（重构到眼动设备 invoker触发 Hover？）
5. 事件互斥逻辑
   - press down之后，优先对选中对象继续触发hover，若无选中对象，则对实时检测对象触发hover;
   - FsuionUI对象无事件互斥机制，不被设备invoker独占，SceneObject对象有事件互斥机制，会被设备独占
6. 





本次修改的实现方案

- 优先级覆盖：优先选中交互对象Hover,覆盖实时检测对象Hover

可解决case2的新方案

- Hover 事件与Select事件分离：按下任意Primary按键之后，不再触发Hover ，中断已触发的Hover Update

