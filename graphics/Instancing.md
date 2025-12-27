### Instancing

1. 传统方法绘制大量实例时，会因大量调用draw call(glDrawArrays、glDrawElements等)，而达到性能瓶颈；draw call本身开销不算大，主要是draw call 之前需要再cpu端对GPU进行大量的状态设置，如绑定缓冲器 、激活顶点属性等；因此通常降低draw call的收益，在于减少CPU到GPU的状态设置工作；
2. instancing
   - 原理：够将数据一次性发送给GPU，然后使用一个绘制函数让GPU利用这些数据绘制多个物体
   - Draw指令：Instanced指令，需要多加一个数量参数
     - glDrawArrays  --> glDrawArraysInstanced
     - glDrawElements -->  glDrawElementsInstanced
   - 
3. 

