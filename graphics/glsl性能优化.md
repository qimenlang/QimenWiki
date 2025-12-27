1. 减少分支:并行计算，一个warp内所有线程执行同样的指令

   ```glsl
   // 差的模式 - 可能导致分支分歧
   // 如果一个warp内，都走if，此时其实不会有性能损失
   // 如果一个warp内，一部分走if,一部分走else,则整体耗时是if + else;
   // 先执行所有走分支A的线程，其他线程等待
   // 再执行所有走分支B的线程，之前执行的线程等待
   // 
   if (threadId % 2 == 0) {
       processEven();
   } else {
       processOdd();
   }
   
   // 好的模式 - 减少分歧
   bool isEven = (threadId % 2 == 0);
   float result = mix(processOdd(), processEven(), float(isEven));
   ```

   

2. 减少分支

1. 