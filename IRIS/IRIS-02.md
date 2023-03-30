### Week1-Week2

1. 解决内存碎片问题
   - scudo实验	
     - 参数配置未成功
     - 可以尝试回退到jemalloc测试
   - mimalloc调研
     - 直接引入,会与scudo冲突
2. 动画系统原型设计
   - 动画事件
   - 状态机重构
   - IK手部测试
   - 混和树完善
3. 手柄接入
   - 注册回调，实现手柄控制动画 flex 
4. **rendermanager exit bug**  2.10  **PENDING**
   - adb shell am broadcast -a xr.intent.action.ACTION_REQUEST_SHUTDOWN    广播系统退出
   - SIGSEGV和SIGABRT信号，如果收到这种信号，说明进程处于一个不确定的状态，很可能会直接挂起。
     - `abort()` sends the calling process the `SIGABRT` signal,
   - detach的子线程结束，会发出SIGABRT??
5. **动画相关功能支持**
   - **蝴蝶应用支持**  2.14 - 16 **DONE**
     - 状态机测试、出uisample  2.15
     - 状态机重构

   - **代码合入，回归测试**  2.15　**DONE**
   - **动画结束事件** 2.16
   - **手势完整接入**
     - IK功能，验证手指拿握物体
6. **传送门功能**  2.17-24
   - stencil模板缓冲实现传送门demo  **DONE**
   - SE中实现传送门  
     - 场景切换
     - 小球放大动画
     - bug:
       - 切换时球第一真不在最小状态 DONE
       - 连续切换背景是空  DONE
       - 在头控设备前放置传送球  DONE
     - ibl 天空盒切换 DONE
     - 支持确认取消 
       - 增加确认、取消、标题等3D按钮
       - 3D按钮支持实时朝向相机、支持点击等事件
     - 传送球增加光圈效果  
   - 
7. 





 