1. 闪退

2. 手势无法正常交互，检测结果position数据来回跳跃

   ```
   01-09 19:39:39.491  2241  4887 I [IrisXR][WindowManager][CommonState]: checkAim block {5914,10096,1} s_overlapBlock 0 interactive : 0
   01-09 19:39:39.501  2241  4887 I [IrisXR][WindowManager][CommonState]: checkAim block {5914,10096,1} s_overlapBlock 0 interactive : 0
   01-09 19:39:39.512  2241  4887 I [IrisXR][WindowManager][CommonState]: checkAim block {5914,10096,1} s_overlapBlock 0 interactive : 0
   01-09 19:39:39.524  2241  4887 I [IrisXR][WindowManager][CommonState]: axisActionCallback focus {5914,10096,1}
   01-09 19:39:39.524  2241  4887 I [IrisXR][WindowManager][WindowManagerImpl]: setFocusWindow android://com.vivo.gallery {5914,10096,1}
   01-09 19:39:39.524  2241  4887 I [IrisXR][WindowManager]: setFocusWindow {5914,10096,1} from 3
   01-09 19:39:39.524  2241  4887 I [IrisXR][WindowManager][CommonState]: checkAim block {5914,10096,1} s_overlapBlock 1 interactive : 0
   01-09 19:39:39.527  5914  6817 I [IrisXR][UI]: TrackedInputDeviceEventCaster::onAxisUpdate Click axis : (name:input/trigger/click, id:30009, characteristics:(Click|RightHand|Primary), type:Vector1D, data:1, device:VIVO, 390
   01-09 19:39:39.536  2241  4887 I [IrisXR][WindowManager][CommonState]: checkAim block {5914,10096,1} s_overlapBlock 1 interactive : 0
   01-09 19:39:39.547  2241  4887 I [IrisXR][WindowManager][CommonState]: checkAim block {5914,10096,1} s_overlapBlock 1 interactive : 0
   01-09 19:39:39.556  2241  4887 I [IrisXR][WindowManager][CommonState]: checkAim block {5914,10096,1} s_overlapBlock 1 interactive : 0
   01-09 19:39:39.568  2241  4887 I [IrisXR][WindowManager][CommonState]: checkAim block {5914,10096,1} s_overlapBlock 1 interactive : 0
   ```

3. 手柄能够打开JS应用，偶现无法打开安卓应用

4. 偶现手柄点击Launcher后，手柄不再能交互

5. XRWindow.cpp中增加LOG，push libixrsdk_compositor.so后，XR启动，无法进入场景

6. android 应用中射线与hit不一致

   ```
   01-10 14:44:14.804  4404  4459 I [IrisXR][Internal][WM][DeprecatedLog]: LJXAndroidDebug id:2, DeviceAxisSpace::getSpacePose for Controller  pose : vec3(-0.037711, -0.255468, 0.438732)quat(0.969534, {0.234514, 0.041389, 0.057395}),m_pose: vec3(-0.010000, -0.027030, 0.031135)quat(0.953717, {-0.300706, 0.000000, 0.000000}),m_localPoseIdentity: 0
   
   ```

   ```
   01-10 15:01:06.738  6286  9269 I [IrisXR][AppStartup][WindowManager]: createWindow from pid {9079,10109,1} windowType = 0 title = 哔哩哔哩HD
   
   ```

7. pose 与pose with aim的计算方法，前后是否一致；

8. 手势poke hit position存在跳跃问题：

   ```
   03-17 00:36:39.315 12063 12205 I [IrisXR][WindowManager][WindowImpl][EventDistribution]: onAxisUpdate id:80001 data:1.000000 timeStamp:914726717982 window:{12063,10111,1}
   03-17 00:36:39.315 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate Click axis : (name:input/trigger/click, id:80001, characteristics:(Click|Primary), type:Vector1D, data:1, device:RightGestureDevice , timestamp: 914726717982, 494, scene :0x7c2b90b330
   03-17 00:36:39.315 12063 12205 I [IrisXR][EventInvoker][EventDistribution]: onAxisUpdate id[80001] name[input/trigger/click] data [1.000000] detector[VIVO_EYE] result size[1]
   03-17 00:36:39.315 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate result : Board, 0x7c2b91c630, distance : 1.086499
   03-17 00:36:39.316 12063 12205 I [IrisXR][FusionUI]: EventCastLog N7irisgui18BoardComponentImplE::procCursorImpl, type : 0, invoker:{8,RightGestureDevice} detector:{4,VIVO_EYE}, target obj : Board , 0x7c2b91c630
   03-17 00:36:39.318 12063 12205 I [IrisXR][FusionUI]: EventCastLog N7irisgui18BoardComponentImplE::procEyeHandScrollImpl, type : 0, invoker:{8,RightGestureDevice} detector:{4,VIVO_EYE}, target obj : Board , 0x7c2b91c630
   03-17 00:36:39.318 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate Result : 0, scene : 0x7c2b90b330
   03-17 00:36:39.318 12063 12205 I [IrisXR][Internal][UI]: DeviceEventCaster::onAxisUpdate : (name:input/trigger/click, id:80001, characteristics:(Click|Primary), type:Vector1D, data:1, device:RightGestureDevice , timestamp: 914726717982
   03-17 00:36:39.318 12063 12205 I [IrisXR][WindowManager][WindowImpl][EventDistribution]: onAxisUpdate id:80001 data:0.000000 timeStamp:914726717982 window:{12063,10111,1}
   03-17 00:36:39.318 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate Click axis : (name:input/trigger/click, id:80001, characteristics:(Click|Primary), type:Vector1D, data:0, device:RightGestureDevice , timestamp: 914726717982, 494, scene :0x7c2b90b330
   03-17 00:36:39.318 12063 12205 I [IrisXR][EventInvoker][EventDistribution]: onAxisUpdate id[80001] name[input/trigger/click] data [0.000000] detector[VIVO_EYE] result size[1]
   03-17 00:36:39.318 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate result : Board, 0x7c2b91c630, distance : 1.086499
   03-17 00:36:39.318 12063 12205 I [IrisXR][FusionUI]: EventCastLog N7irisgui18BoardComponentImplE::procCursorImpl, type : 1, invoker:{8,RightGestureDevice} detector:{4,VIVO_EYE}, target obj : Board , 0x7c2b91c630
   03-17 00:36:39.318 12063 12205 I [IrisXR][FusionUI]: EventCastLog N7irisgui18BoardComponentImplE::procEyeHandScrollImpl, type : 1, invoker:{8,RightGestureDevice} detector:{4,VIVO_EYE}, target obj : Board , 0x7c2b91c630
   03-17 00:36:39.318 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate Result : 0, scene : 0x7c2b90b330
   03-17 00:36:39.318 12063 12205 I [IrisXR][Internal][UI]: DeviceEventCaster::onAxisUpdate : (name:input/trigger/click, id:80001, characteristics:(Click|Primary), type:Vector1D, data:0, device:RightGestureDevice , timestamp: 914726717982
   03-17 00:36:39.318 12063 12205 I [IrisXR][WindowManager][WindowImpl][EventDistribution]: onAxisUpdate id:80001 data:1.000000 timeStamp:914726717982 window:{12063,10111,1}
   03-17 00:36:39.318 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate Click axis : (name:input/trigger/click, id:80001, characteristics:(Click|Primary), type:Vector1D, data:1, device:RightGestureDevice , timestamp: 914726717982, 494, scene :0x7c2b90b330
   03-17 00:36:39.318 12063 12205 I [IrisXR][EventInvoker][EventDistribution]: onAxisUpdate id[80001] name[input/trigger/click] data [1.000000] detector[VIVO_EYE] result size[1]
   03-17 00:36:39.318 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate result : Board, 0x7c2b91c630, distance : 1.086499
   03-17 00:36:39.318 12063 12205 I [IrisXR][FusionUI]: EventCastLog N7irisgui18BoardComponentImplE::procCursorImpl, type : 0, invoker:{8,RightGestureDevice} detector:{4,VIVO_EYE}, target obj : Board , 0x7c2b91c630
   03-17 00:36:39.319 12063 12205 I [IrisXR][FusionUI]: EventCastLog N7irisgui18BoardComponentImplE::procEyeHandScrollImpl, type : 0, invoker:{8,RightGestureDevice} detector:{4,VIVO_EYE}, target obj : Board , 0x7c2b91c630
   03-17 00:36:39.319 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate Result : 0, scene : 0x7c2b90b330
   03-17 00:36:39.319 12063 12205 I [IrisXR][Internal][UI]: DeviceEventCaster::onAxisUpdate : (name:input/trigger/click, id:80001, characteristics:(Click|Primary), type:Vector1D, data:1, device:RightGestureDevice , timestamp: 914726717982
   03-17 00:36:39.319 12063 12205 I [IrisXR][WindowManager][WindowImpl][EventDistribution]: onAxisUpdate id:80001 data:0.000000 timeStamp:914726717982 window:{12063,10111,1}
   03-17 00:36:39.319 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate Click axis : (name:input/trigger/click, id:80001, characteristics:(Click|Primary), type:Vector1D, data:0, device:RightGestureDevice , timestamp: 914726717982, 494, scene :0x7c2b90b330
   03-17 00:36:39.319 12063 12205 I [IrisXR][EventInvoker][EventDistribution]: onAxisUpdate id[80001] name[input/trigger/click] data [0.000000] detector[VIVO_EYE] result size[1]
   03-17 00:36:39.319 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate result : Board, 0x7c2b91c630, distance : 1.086499
   03-17 00:36:39.319 12063 12205 I [IrisXR][FusionUI]: EventCastLog N7irisgui18BoardComponentImplE::procCursorImpl, type : 1, invoker:{8,RightGestureDevice} detector:{4,VIVO_EYE}, target obj : Board , 0x7c2b91c630
   03-17 00:36:39.319 12063 12205 I [IrisXR][FusionUI]: EventCastLog N7irisgui18BoardComponentImplE::procEyeHandScrollImpl, type : 1, invoker:{8,RightGestureDevice} detector:{4,VIVO_EYE}, target obj : Board , 0x7c2b91c630
   03-17 00:36:39.319 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate Result : 0, scene : 0x7c2b90b330
   03-17 00:36:39.319 12063 12205 I [IrisXR][Internal][UI]: DeviceEventCaster::onAxisUpdate : (name:input/trigger/click, id:80001, characteristics:(Click|Primary), type:Vector1D, data:0, device:RightGestureDevice , timestamp: 914726717982
   03-17 00:36:39.319 12063 12205 I [IrisXR][WindowManager][WindowImpl][EventDistribution]: onAxisUpdate id:80001 data:1.000000 timeStamp:914726717982 window:{12063,10111,1}
   03-17 00:36:39.319 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate Click axis : (name:input/trigger/click, id:80001, characteristics:(Click|Primary), type:Vector1D, data:1, device:RightGestureDevice , timestamp: 914726717982, 494, scene :0x7c2b90b330
   03-17 00:36:39.319 12063 12205 I [IrisXR][EventInvoker][EventDistribution]: onAxisUpdate id[80001] name[input/trigger/click] data [1.000000] detector[VIVO_EYE] result size[1]
   03-17 00:36:39.319 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate result : Board, 0x7c2b91c630, distance : 1.086499
   03-17 00:36:39.319 12063 12205 I [IrisXR][FusionUI]: EventCastLog N7irisgui18BoardComponentImplE::procCursorImpl, type : 0, invoker:{8,RightGestureDevice} detector:{4,VIVO_EYE}, target obj : Board , 0x7c2b91c630
   03-17 00:36:39.320 12063 12205 I [IrisXR][FusionUI]: EventCastLog N7irisgui18BoardComponentImplE::procEyeHandScrollImpl, type : 0, invoker:{8,RightGestureDevice} detector:{4,VIVO_EYE}, target obj : Board , 0x7c2b91c630
   03-17 00:36:39.320 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate Result : 0, scene : 0x7c2b90b330
   03-17 00:36:39.320 12063 12205 I [IrisXR][Internal][UI]: DeviceEventCaster::onAxisUpdate : (name:input/trigger/click, id:80001, characteristics:(Click|Primary), type:Vector1D, data:1, device:RightGestureDevice , timestamp: 914726717982
   03-17 00:36:39.320 12063 12205 I [IrisXR][WindowManager][WindowImpl][EventDistribution]: onAxisUpdate id:80001 data:0.000000 timeStamp:914726717982 window:{12063,10111,1}
   03-17 00:36:39.320 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate Click axis : (name:input/trigger/click, id:80001, characteristics:(Click|Primary), type:Vector1D, data:0, device:RightGestureDevice , timestamp: 914726717982, 494, scene :0x7c2b90b330
   03-17 00:36:39.320 12063 12205 I [IrisXR][EventInvoker][EventDistribution]: onAxisUpdate id[80001] name[input/trigger/click] data [0.000000] detector[VIVO_EYE] result size[1]
   03-17 00:36:39.320 12063 12205 I [IrisXR][UI]: EventInvoker::onAxisUpdate result : Board, 0x7c2b91c630, distance : 1.086499
   03-17 00:36:39.320 12063 12205 I [IrisXR][FusionUI]: EventCastLog N7irisgui18BoardComponentImplE::procCursorImpl, type : 1, invoker:{8,RightGestureDevice} detector:{4,VIVO_EYE}, target obj : Board , 0x7c2b91c630
   03-17 00:36:39.320 12063 12205 I [IrisXR][FusionUI]: EventCastLog N7irisgui18BoardComponentImplE::procEyeHandScrollImpl, type : 1, invoker:{8,RightGestureDevice} detector:{4,VIVO_EYE}, target obj : Board , 0x7c2b91c630
   
   ```

   

9. 
