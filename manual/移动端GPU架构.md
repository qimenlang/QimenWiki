1. 相关名词
   - IMR (Immediate-Rendering) Primitive提交之后直接进行绘制
   - SRAM (Static Random Access Memory) 静态随机存取存储器，用的是晶体管，电流是持续的，片上存储器，用于高速缓存，一级二级Cache；
   - DRAM (Dynamic Random Access Memory)  动态随机存取存储器，用的是电容，需要刷新，用于内存条、显存；
2. 在GPU渲染中，对功耗影响最大的是带宽(bandwidth)，为什么是带宽？？？因为带宽小，需要不断到显存读取存储FrameBuffer，所以耗电大？
3. TBR(Tile based Rendering) 基于瓦片的渲染
   - 原理：为了避免直接到显存中存取FrameBuffer，DRAM距离GPU较远，**把FrameBuffer分成很多小块，每一块刚好可以被SRAM容纳，块的多少取决于SRAM容量的大小；**因为渲染的时候，多个计算流程一次性在SRAM上计算完成，最后只需要将计算的结果搬运到DRAM上，所以大大的减小了带宽的使用；
4. TBDR(Tile-Base-Deffered-Rendering) 基于瓦片的延迟渲染
   - 每次渲染一个Tile的时候，将当前Tile中的图元取出，进行三角形变换、着色等计算；
5. 