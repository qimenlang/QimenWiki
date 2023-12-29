### 实现方案分析

#### windows

1. UI Property
   - CanDrag
   - AllowDrop : 决定UI是否是Drop Target；
2. Events
   - DragStarting : Occurs when a drag operation is initiated by calling the [StartDragAsync](https://learn.microsoft.com/en-us/uwp/api/windows.ui.xaml.uielement.startdragasync?view=winrt-22621#windows-ui-xaml-uielement-startdragasync(windows-ui-input-pointerpoint)) method
   - DragEventHandler
     - DragEnter
     - DragLeave
     - DragOver 
     - Drop
   - DropCompeleted 
3. Here's an overview of what you need to do to enable drag and drop in your app:
   - Enable dragging on an element by setting its **CanDrag** property to true. 
   - Build the **data package**. The system handles images and text automatically, but for other content, you'll need to handle the [**DragStarting**](https://learn.microsoft.com/en-us/uwp/api/windows.ui.xaml.uielement.dragstarting) and [**DropCompleted**](https://learn.microsoft.com/en-us/uwp/api/windows.ui.xaml.uielement.dropcompleted) events and use them to construct your own data package.
   - Enable dropping by setting the **AllowDrop** property to **true** on all the elements that can receive dropped content.[一般是listview / gridview中的子节点]
   - Handle the **DragOver** event to let the system know what type of drag operations the element can receive.
   - Process the **Drop** event to receive the dropped content.[支持同时drop多个不同类型的元素]
   - 定制DragUI : 使用data Package , 生成一张缩略图，source 和target 都可以定制；
4. 事件参数
   - DragStartingEventArgs
   - DragEventArgs：存储了数据包、指定DragUI样式（缩略图、状态图）
5. 相关概念
   - drag source
     - drag操作触发的应用或区域；
     - 负责封装用于传输的数据包，数据包有指定格式；
     - 指定操作类型：none、copy、move、**link**；
   - drop target
     - drop操作触发时所处的应用或区域；
     - 处理数据包
     - 返回操作类型[为什需要返回]
     - ui是drop的前置条件是allow drop为true
   - 视觉反馈：由drag source指定的操作类型据决定，受drag over target 影响；
   - 剪切板
   - routed event : 在树的子节点向父节点传递；类似冒泡；

#### Apple

1. 相关概念

   - drag source
   - drag destination
   - 单个app内的drag&drop操作，该app分饰两角；
   - drag activity : The complete user action from start to finish
   - drag session : 
   - UIDragItem : 封装数据,生成一张缩略图；

2. 组件

   - UIDragInteractionDelegate : for drag source app constructs DragItem.
   - UIDropInteractionDelegate :  for drag destination consumes DragItem.

3. 数据读写协议

4. 其他

   - 弹簧加载：drag over时自动打开文件夹；

   - 需要同时支持多个drag 活动，drop destination可以通知响应多个drop;

     

### IRIS Drap&Drop设计方案

1. Drag&Drop流程

   - 普通Drag事件触发，且操作对象为支持draggable 的2D UI或3D SceneObject，则触发DragBegin事件；
   -  draggable对象封装为数据包对象，该对象同时产生缩略图和状态图；
   - 数据包对象跟随Cursor移动；
   - Hover到DragTarget对象时，触发DragOver事件[包括DragEnter、DragOver、DragLeave]，影响视觉反馈；
   - 在DragTarget对象上释放Item，触发Drop事件，根据操作方向确定操作类型，处理数据包对象包；

2. Draggable & DropTarget（非必须）

   - 同时支持2D UI和3D SceneObject **OR** 2D UI添加属性、3D SceneObjecy 添加component
   - 没有DropTarget时，操作类型为open；有DropTarget，操作类型为Copy/Move

3. 操作类型：Copy / Move / Open 

   - 操作类型由操作方向类型

4. 操作方向&默认操作类型

   - 方案1:
     - Window --> Server [Move]
     - Server --> Client [Move]
     - Client A --> Client B [Copy]
     - Client --> Self [Move]
     - Server --> Self [Move]  ，存在的问题：drop到Server打开的Item,是否应该和3D SceneObject区分；OR 原本存在与Server上的 3D SceneObject 不能触发Drag&Drop操作；
   - 方案2:
     - UI --> NoneUI  [Open]
     - UI --> UI [Copy]
     - NoneUI --> UI [Move]
     - NoneUI --> NoneUI [Move]

   Client Window作为最外层的DragTarget , Client Window内部的UI View 组件也可以是DragTarget。

5. Visual FadeBack

6. 其他支持

   - 弹簧加载
   - 同时支持多个Drag & Drop活动，一个Drag操作可以打包多个不同类型的对象，一个Drop Target可以同时响应多个drop事件；

7. 