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

   - **Drag事件触发**，且操作对象为支持draggable 的2D UI或3D SceneObject，则触发DragStart事件；
     - 操作对象为interactable，则触发普通drag事件；
     - 操作对象为draggable , 则触发drag&drop流程的DragStart事件；
   - **封装数据包**，将draggable对象或传输数据 封装为数据包对象，该对象同时产生缩略图和状态图；
     - DragStart事件触发，构建数据包，在dragSource上触发;
     - DragEnd 事件触发，在dragSource上触发，例如move时，在drag Source 上删除item；
     - 数据包内容：传输数据、缩略图、状态图；
   - **处理DragOver事件**： 数据包对象跟随Cursor移动，Hover到DragTarget对象时，触发DragOver事件[包括DragEnter、DragOver、DragLeave]，影响视觉反馈；
   - 在DropTarget对象上释放dragged element，触发Drop事件，根据操作方向确定操作类型，处理数据包对象包；
     - Drop事件触发，消费数据包；
2. 相关事件 

   - DragStart : 发生在drag source，生成数据包。
     - 由使用方通过DragStart回调函数指定数据包的操作方式、数据包内容等； 
   - DragEnter、DragOver、DragLeave : 发生在drop target
     - 使用方通过DragEnter回调函数，修改状态图样式；
   - Drop : 发生在drop target ,真正处理数据包
     - 
   - DropCompeleted : 发生在drag source，例如move时，在drag Source 上删除item；
3. 事件参数:

   - DragStartingEventArgs
   - DragEventArgs 
     - GetDeferral() ： 获取异步对象，支持异步拖放操作。
   - DropCompletedEventArgs 
     - DropResult
     - Original Source
4. Draggable & DropTarget（非必须）

   - 2D UI添加canDrag、allowDrop属性、3D SceneObject 添加dragable component 、dropTarget component ；
   - 没有DropTarget时，操作类型为open；有DropTarget，操作类型为Copy/Move
5. 操作类型：None/ Copy / Move / Open 

   - 操作类型由drag source 指定，或者通过draggable设定；

     - Open 操作只在2DUI --> 3D 空间时发生； 如何确定一个UI Element的 Drag Operation是 Open 而不是 Copy；
6. DataPackage： 包含需要传输的数据

   - 支持哪几种数据类型、格式 ？ txt、modelPath、sceneobject、png；
   - 由drag Source 直接生成，发送给drop target ;也可以使用一个代理来生成 [ 适用于不立即传输，直到drop target请求数据时传输的情况 ];
   - DataPackageView : DataPackage的只读版本，drop target收到该对象，使用该对象包含的信息，获取传输的数据；
   - DataPackage填充数据，DataPackageView获取数据；
7. Visual FadeBack
8. 其他支持

   - 弹簧加载
   - 同时支持多个Drag & Drop活动，一个Drag操作可以打包多个不同类型的对象，一个Drop Target可以同时响应多个drop事件；



### Drap&Drop实现

1. 