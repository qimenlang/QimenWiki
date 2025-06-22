### GPU架构

1. Frame Buffer : FrameBuffer缓存的内容和显示器上显示的像素是一一对应的；每个像素由32位的RGBA组成；

2. 可编程渲染管线

   ![image-20220520134900344](C:\Users\51039\AppData\Roaming\Typora\typora-user-images\image-20220520134900344.png)

   - Input Assmbler:将内存中的VBO组装成顶点数据，传递给顶点着色器；
   - CPU擅长在小数据上做复杂串行计算和逻辑控制；GPU擅长在大量数据上做简单的并行计算；

3. GPU 逻辑上的模块

   ![image-20220609002245162](C:\Users\51039\AppData\Roaming\Typora\typora-user-images\image-20220609002245162.png)

   - Geometry Shader：输入一个图元，输出多个图元

   - Stream Output:图元装配阶段之后，可以直接导出数据到内存；

   - Tessellation  曲面细分

     - Hull Shader : **指定每个图元如何被细分**，比如内部分成多少个，每条边分成多少段；
     - Tessellator ：用算法**执行细分**；
     - Domain Shader ： 根据细分的参数，计算细分之后每个顶点的信息；

   - GPGPU (General Purpose computing on GPUS、GPU通用计算)

     - Computer Shader

       - 利用GPU上的并行计算单元进行计算；
       - UAV(Unordered Access View)可以多入多出，可以任意读取，可以任意写；
       - 不需要经过固定流水线单元，提高了性能；

       <img src="C:\Users\51039\AppData\Roaming\Typora\typora-user-images\image-20220609001720784.png" alt="image-20220609001720784" style="zoom: 50%;" />

   - Amplification Shader & Mesh Shader

     - 在只有少量甚至没有输入的情况下，使用GPU生成大量复杂的数据（与Geometry Shader不同，不依赖于输入的几何数据）；Computer Shader 能胜任该种计算，但是其输出不能接入Rasterizer；
     - Amplification Shader :负责指定执行多少次Mesh Shader
     - Mesh Shader ：负责产生几何体，生成的是Meshlet

4. 光线追踪渲染管线

   - Ray Generation Shader : 负责生成光线
   - Intersection Shader ：负责判定光线与物体是否相交
   - Any Hit Shader : 光线打到物体时判断是否往前走
   - Closet Hit Shader:在光线打到物体的最近点计算颜色
   - Miss Shader : 光线没打到任何物体时计算颜色
   - Callable Shader : 进行动态调用

   <img src="C:\Users\51039\AppData\Roaming\Typora\typora-user-images\image-20220609004306600.png" alt="image-20220609004306600" style="zoom:67%;" />

5. GPU硬件架构

   - 计算机体系结构概念

     - SISD(Single Instruction Single Data Stream 单指令单数据流)：每个指令每次处理一个数据；
     - SIMD(Single Instruction Multiple Data Stream 单指令多数据流)：可以同时对多个数据做同一个指令的计算；一组GPU线程在同一时刻执行同一个指令，称为一个warp/wave;

     <img src="C:\Users\51039\AppData\Roaming\Typora\typora-user-images\image-20220609101137756.png" alt="image-20220609101137756" style="zoom:50%;" />

   - Unified Shader

     - 在硬件上不再区分vertex shader和pixel Shader,统一在Unified Shader上进行计算，具体多少个Unified Shader计算顶点多少Unified Shader计算像素，由调度器进行调度；

   - Streaming Processor(SP) 流处理器

   - Streaming Multi-Process(SM) 流式多处理器 

     - 一组流处理器+控制器+片上内存+采样器等，构成一个流式多处理器

     <img src="C:\Users\51039\AppData\Roaming\Typora\typora-user-images\image-20220609234142676.png" alt="image-20220609234142676" style="zoom:50%;" />

     - 不同型号的显卡，SM的数量是不一样的，但是SM的结构是一样的；

       

   - 

     

6. 