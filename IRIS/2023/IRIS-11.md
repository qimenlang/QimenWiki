#### Controller重构-样式定制

1. Json文件配置
   - 在json文件中定义Controller各组件的模型、材质、动画等配置，规定死配置文件的格式，应用端通过更改json配置文件的内容，来定制样式；
   - 在事件处理函数中，写死事件（轴数据）与样式变化的逻辑；
2. ReplaceSceneObject
   - 应用端自定义Controller各个组件的模型、材质、动画等，通过ReplaceSceneObject接口，更换Server端 Controller上的模型；
   - 应用端自定义事件回调，自己完成事件与样式变化的逻辑；
3. 其他问题
   - ReplaceSceneObject方案中，应用侧自行添加各个Interactor组件？ [手柄controller不使用 RayInteractor,或者RayInteractor暴露給應用]
   - 键盘、鼠标等控制器，需要样式定制？
   - 只需要屏蔽一部分事件，继续复用剩余部分事件的情况；



#### Controller重構

1. ModelController從Json加載，規定json格式
2. **replaceSceneObject**
   - **可以指定替换 constroller，line，cursor** 
     - replace  帶collider的cursor，將collider置爲false之後，raycastall能夠檢測到錯誤的sceneobject;
     - replace 不帶collider的cursor，window bar 不響應、新cursor旋轉有問題；
     - 
   - 手勢手柄切換
   - 事件僅部分屏蔽
3. **共享應用交互[暫不考慮]**
   - 如何確認應用白名單？
4. **CorsurManager取消，功能合併到ControllerManager**
   - cursor是controller一部分
   - cursor與controller狀態同步
5. RealTimeGesrtureController只保留一個deivice，分離detector
6. device 需要提供disable指定軸的功能



### 交互检测

1. UI事件交互重构--Poke

   - hovering和selection都是通过检测点的transform去检测
   - 以最近的pokeinteractable为最佳
   - selection：检测点在连续两帧之间沿着平面的法线方向，穿过该平面；[需要给所有交互控件增加该平面组件]
   - 平面由无穷大的背面和有限的检测区域组成
   - 在selection发生期间，手mesh会被约束，wrist的position不再由识别数据控制，会被覆写；

2. 手势触发事件

   | 手势       | 事件          | 直接交互                                                     | 间接交互 |
   | ---------- | ------------- | ------------------------------------------------------------ | -------- |
   | Poke       | click         | the point transform across two consecutive frames intersects the **ISurface** of the **PokeInteractable** in the direction of the surface normal |          |
   | Poke       | press         |                                                              |          |
   | Pinch/Grab | hold          |                                                              |          |
   | Pinch/Grab | drag          |                                                              |          |
   |            | HoverWithHold |                                                              |          |

3. Operation To Event

   - Tap 事件与ShortTap \ LongPress两个事件互斥
   - LongPress 
     - 动态button时，按到底才触发LongPress Begin、LongPress Repeat、LongPress end;
   - Operation 与axis基本类似？
     - axis由数据类型、数据、轴角色等组成
   - 所有的interactor均绑定一个device ,在interactor中检测interacterable,在eventcaster中根据operation信息 invoke interacterable 对应的event

4. 重构内容

   - 优化PokeInteractor的检测方式，增加PokePlane组件
     - PokeIneractor/PokePlane移植到IrisUI **DONE**
     - PokeIneractor使用InputDeviceManager创建的device,生成axis数据
     - Poke Press支持平面Scroll ： 包含pos信息
   - 状态转换
     - PokeInteractor的状态转换：default-(大范围overlap)->hover-(小碰撞体碰撞)->select
     - PinchInteractor/GrabInteractor的状态状换：default-(小范围overlap)->hover-(Pinch/Grab手势)->select
   - RayInteractor同时支持手势和手柄
   - **基于碰撞检测触发事件** OR 基于检测点与几何体的位置关系
     - 手势碰撞体、交互对象碰撞体的 Group\Mask 设置问题 **可以在进入hovering状态之后，设置mask&group DONE**
     - 碰撞体每帧移动距离小于0.11m时，不触发碰撞 **FIX**
     - 碰撞体每帧移动距离大于0.11m时，可以触发碰撞，但是碰撞几十次之后，不再触发 **FIX**
     - 基于检测点与几何体位置关系触发事件的优势
       - 处理面片的click时，up触发事件更自然；[只针对planeCollider使用位置关系的方式]
   - 缺少类似PokePlane的有限面片状的碰撞体
   - PlaneCollider不支持pointDistance，使用其他备选方式？
   - 各interactor依赖于同一个device，各自维护一个offset；

   重构进展：

   - 基于碰撞检测实现交互，解决手势碰撞体、交互对象碰撞体的 Group\Mask 设置问题 ；
   - 完成pokeinteractor支持click、shortclick、longpress事件；
   - 完成pinchinteractor支持drag事件；
   - 在iriseditor中进行模拟测试；

   遇到的问题：

   - 在yvr设备上自测，有崩溃的bug，没有堆栈信息；
   - interactable  rttr_enable超过8个父类会在运行时崩溃，暂未解决；

   * 解决老版手势交互不响应问题，配合系统组串流应用测试；

5. 重构步骤

   - 检测interactable从TrackedEventCaster中移到interactor中
   - iriseditor中搭建仿真测试环境
     - 设备管理： inputDeviceManager 与iris::InputManagerClient 相互替换
     - interactor/interactable代码从windowmanager移植到irisui中？
   - 重构各interactor
     - 实现PokePlane组件 [50%]
     - PokeInteractor
     - PinchInteractor
     - 各个InterActor共用同一个device **暂时不做**





1. 模块职责

   - Interactor 
     -  检测interactable 
     - 生成axis数据（描述operation）
     - 绑定一个device,
   - eventcaster : 接收处理axis数据，映射interactable对应的事件
2. Drag&Drop
   - 需求分析
     - Base 
       - 在空间中创建应用内的对象（UI控件）
     - Drag
       - 从源应用Drag对象到空间，需要支持在空间中显示被拖拽的对象
     - Drop
       - 从空间中将对象Drop到目的应用，目的应用是否支持被drop的对象；
   - 设计
     - 
   - 
3. 


