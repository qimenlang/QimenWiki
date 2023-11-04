Poke交互支持触发Click、Drag事件，与已有的APP进行交互 

-  创建虚拟设备、轴，通过事件系统，触发click事件

   -  存在bug：无法与jsapp的ui控件进行交互
   -  使用现有的手柄设备，直接模拟手柄事件？
   -  在食指位置，放置虚拟设备
   -  每个应用，单独一个进程，一个scene,三个设备；从A进程中，手动更新某个设备某个轴，只影响当前进程；事件无法做到全局转发；设备管理器，及设备，应该作为全部进程共享的资源，不应该每个进程有各自设备拷贝；
   -  实际按下手柄按钮的事件，可以在所有进程中收到；验证
   -  C接口的轴更新事件，如何在event caster中接收到？默认支持接收？重写event caster?

   

Snap、Grab手势交互，需要支持现有app？？







高通手势接入

-  数据驱动高通sdk中拿到的手模型，效果不正确；
-  数据驱动iris手模型，手变形严重；







2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis form device : PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:input/device/width/value, id:10001, characteristics:), type:Integer, data:864, device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:input/device/height/value, id:10002, characteristics:), type:Integer, data:1687, device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:input/screen_touch/value, id:10003, characteristics:(Touch|RightHand), type:Vector2D, data:(0,0), device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:input/screen_touch/offset, id:10004, characteristics:(Value|Touch|RightHand), type:Vector2D, data:(0,0), device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:input/screen_touch/action, id:10005, characteristics:(Click|Touch|RightHand|Primary), type:Integer, data:0, device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:input/screen_touch/coord, id:10006, characteristics:(Value|Touch|RightHand), type:Vector2D, data:(0,0), device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:input/home/click, id:10007, characteristics:(Click|RightHand), type:Vector1D, data:0, device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:input/pose/offset, id:10008, characteristics:(Touch|LeftHand), type:Vector1D, data:0, device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:input/device/followHead, id:10009, characteristics:(RightHand), type:Custom, data:(size16), device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:input/trigger/click, id:10010, characteristics:(Click|Touch|RightHand|Primary), type:Vector1D, data:0, device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:input/thumbstick/coord, id:10011, characteristics:(Value|Touch|RightHand), type:Vector2D, data:(0,0), device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:input/thumbstick/action, id:10012, characteristics:(Click|Touch|RightHand), type:Vector1D, data:0, device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:input/thumbstick/value, id:10013, characteristics:(Value|Touch|RightHand), type:Vector2D, data:(0,0), device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:output/pose/state, id:10014, characteristics:(RightHand), type:Integer, data:2, device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:input/pose/state, id:10015, characteristics:(RightHand), type:Integer, data:2, device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:internal/service/name, id:10016, characteristics:), type:Custom, data:(size9), device:PhoneRightController
2023-06-30 19:13:57.387 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis: (name:internal/ipcserver/name, id:10017, characteristics:), type:Custom, data:(size15), device:PhoneRightController
2023-06-30 19:13:57.388 22696-22826 IRIS-ERROR              com.irisview.irisxr                  E  LJX Get all axis form device : PhoneRightController

