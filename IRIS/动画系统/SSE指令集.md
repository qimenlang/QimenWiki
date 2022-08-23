1. 相关概念

   - SIMD：单指令多数据
   - SSE : Streaming SIMD Extensions, 使用128位 寄存器 的指令集（__m128）
   - AVX : Advanced Vector Extensions，使用256位寄存器的指令集
   - Neon : ARM上使用128位寄存器的指令集

   目前128位指令集最为通用

2. 相关的头文件

   - <mmintrin.h>   MMX
   - <xmmintrin.h>  SSE
   - <emmintrin.h>  SSE2
   - <pmmintrin.h>  SSE3
   - <tmmintrin.h>   SSSE3
   - <smmintrin.h>  SSE4.1
   - <nmmintrin.h>  SSE4.2   
   - <ammintrin.h>  SSE4A
   - <wmmintrin.h>  AES
   - **<immintrin.h>**   AVX,AVX2,FMA

   只需要包含  <immintrin.h>就相当于包含了上述全部头文件 

3. 添加编译选项

   - g++:  加入 -msse4.2 或其他版本 ： g++ -msse4.2 XXX -o main
   - cmake:  target_compile_options(main  PRIVATE  -msse4.2)

4. 内存对齐   

   - SIMD计算要求内存数据必须对齐（*16byte对齐 = 128bit*）,编译器可能会自动对齐，也可能不会，最好手动对齐；
   - std::aligned_alloc(16,N);按照16字节对齐分配内存空间；16 byte = 128 bit = __m128 ；

[reference1](https://acl.inf.ethz.ch/teaching/fastcode/2019/slides/07-simd.pdf)

[reference2](https://blog.csdn.net/mightbxg/article/details/109111335)

[并行与并发编程](https://zhuanlan.zhihu.com/p/372231438)

