### Pilot代码走读

1. ​    class ThreeFrameBuffers

   双缓冲 vs 三缓冲：三缓冲有两个buffer可以缓存绘制的一帧画面，双缓冲只有一个，三缓冲相对于双缓冲节省了从帧缓存拷贝到视频缓存的时间；

   

   ![img](https://upload.wikimedia.org/wikipedia/commons/thumb/7/73/Comparison_double_triple_buffering.svg/1024px-Comparison_double_triple_buffering.svg.png)

    

2. eidtor 

   - editor UI
   - engine
     - run 中的while(true)
       - logic tick  : 逻辑tick，包括世界、物理、IO等
       - render tick  ：渲染  
     - 

3. 

4. 