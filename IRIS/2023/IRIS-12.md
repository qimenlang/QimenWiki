1. Drag分类
   - Begin时 SetParent
   - Update时 更新Position
   - 受限制的运动
     - 沿指定轴运动
     - 在指定平面运动
   - 触发条件：
     - 只pinch手势可以触发，Poke手势不能触发
     - 交互目标支持移动，则优先触发Drag
     - **触点在交互对象上移动超过阈值，触发Drag 事件，不触发click事件，不超过阈值，触发click事件；**
       - interactor状态使用了Activate : 可以在eventcaster侧延后触发drag begin;
       - **使用Click轴特征，无法与Click事件区分，导致Click与Drag同时触发：只能优先响应Drag；** 
       - 有阈值，体验相对会差；  
   - 与应用侧同步：
     - **取消Hold只保留drag事件 : 所有应用及DragBar**
     - 取消按照轴名称过滤轴事件的机制，采用按照轴特征过滤
     - 区分前后的button组件（pokeplane）,是否需要；
2. 测试版本bug跟进
3. 手势重构代码整理合入
4. 手势重构版本实现方案
5. Drag&Drop
   - 系统应用之间、应用和Scene之间；
   - UI事件体系，事件的捕获、冒泡机制；[EventCaster基本可用]
   - **UI图标在三维空间、射线cursor位置显示；**
   - 被Drag对象在三维空间显示；
6. 手柄样式代码合入 **DONE** 
7. **手势可靠性测试**： 在设备性能极差、手势识别结果不准的情况下，保证稳定交互；

