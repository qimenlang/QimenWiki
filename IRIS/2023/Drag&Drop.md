### 实现方案分析

#### windows

1. UI Property
   - CanDrag
   - AllowDrop : 决定UI是否是Drop Target；
2. Events
   - DragEventHandler
     - DragEnter
     - DragLeave
     - DragOver
     - Drop
   - DragStarting : Occurs when a drag operation is initiated.
   - DropCompeleted : 
3. Here's an overview of what you need to do to enable drag and drop in your app:
   - Enable dragging on an element by setting its **CanDrag** property to true. 
   - Build the **data package**. The system handles images and text automatically, but for other content, you'll need to handle the [**DragStarting**](https://learn.microsoft.com/en-us/uwp/api/windows.ui.xaml.uielement.dragstarting) and [**DropCompleted**](https://learn.microsoft.com/en-us/uwp/api/windows.ui.xaml.uielement.dropcompleted) events and use them to construct your own data package.
   - Enable dropping by setting the **AllowDrop** property to **true** on all the elements that can receive dropped content.
   - Handle the **DragOver** event to let the system know what type of drag operations the element can receive.
   - Process the **Drop** event to receive the dropped content.
4. 事件参数
   - DragStartingEventArgs
   - 
5. others
   - routed event : 在树的子节点向父节点传递；类似冒泡；
   - 
6. 



​	

#### Apple

