手势交互

1. Poke交互支持触发Click、Drag事件，与已有的APP进行交互  **06/21**

   -  创建虚拟设备、轴信息，填充事件参数 **DONE**
   -  在compositor中，创建虚拟设备、使用现有事件检测系统
      -  实现Poke手势触发Click事件 **DONE**
      -  实现Snap手势触发Drag事件 **DONE**
         -  DRAG事件在射线中是长按之后触发
   -  测试
      -  **web应用无法启动问题**
      -  **Poke触发Click事件不够准确**  DONE 
      -  **Pinch触发drag，不稳  ** DONE 
      -  Pinch触发drag时，还会与pinch范围外的其他物体交互  DONE
      -  Pihch、Drag 移动速度太快时，脱离绑定 DONE 
      -  射线点击后，Pinch Drag失效问题  DONE 
      -  同时支持Poke\Pinch  DONE 
      -  高通版本中，支持interactor
         -  虚拟设备创建之后，interactor过程中未获取到虚拟设备 DONE
         -  解决Mesh偏移问题 
      -  应用测试：象棋、白板网页、player;(只web应用)
      -  **重置位置之后，识别手位置错误；  DONE**
      -  手势间接交互； DONE
         -  自定义虚拟设备：轴数据可以和poke、pinch的轴类似；绘制射线；
         -  目前手上的射线依赖关节点，由于手势识别关节点不稳，导致射线不稳，不好控制；尤其在射线指向交互物体，做pinch手势的时候，手动更容易导致射线偏移，体验较差；
         -  使用头控射线实现间接交互；
         -  射线基本样式改变
      -  解决手势识别关节点抖动问题:
         -  平滑过往几帧
         -  找到一个阈值，解决抖动，不影响位移
      -  获取手势识别模块运行成功信息或者增加全局开关 DONE
      -  **Poke需要支持两种交互：长按、点击**
      -  **虚拟设备射线范围设置  DONE**
      -  Button按下效果
      -  **poke、pinch互斥**
      -  手、射线切换；
      -  手心位置增加虚拟设备  DONE 
      -  **代码合入提测** 
         -  **重构增加设备功能的代码逻辑**   DONE 
         -  替换模型文件、文件放到resource DONE
   -  接入高通手势识别算法
   
   - AR版本irisview应用存在的问题
     - web应用无法打开；android应用打开之后，只有一个框；
     - 启动irisview应用，经常打不开，有时需要重启手机，才能打开；
     - 手势识别运行几分钟之后，手机发烫，手mesh会错乱，irisview会崩 **DONE** 
   - 手mesh驱动问题：
     - mesh有时会错乱，两只手同时渲染时，后填充的手mesh错乱，可能是算力不足导致； **DONE** 
     - **显示的手mesh的位置相对真实手的位置存在偏移**  
       - **关节点与手mesh错位问题：每次启动，偏移量都不一样，但是该偏移量在运行期间保持不变；** 
   - 高通版本中配置手部控制器、事件触发等  **06/25**
     - **需要实现配置手势识别数据源的控制器**
     - 使用关节点立方体代替手模型
     - 手指末端检测器，检测交互物体
       - 食指、拇指同时检测到交互物体，触发拖拽事件
       - 只食指检测到交互物体，触发点击事件
     - 检测不到手时，将手mesh不显示；**DONE** 
   
3. 远程交互效果实现   **06/28**
   - 使用射线选择交互对象：相机位置向正前方发出射线；
   - 使用识别手势，触发事件
     - 捏合手势，触发点击事件
     - 拖拽：使用什么位置？
   
3. 直接交互优化及测试

5. 提供数据，配合完善手部模型

