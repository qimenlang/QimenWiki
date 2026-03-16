1. 如何理解opengl context ，opengl context ： GPU状态机的实例+资源容器，opengl的本质是状态机，context是这套状态机的具体实例，包含：

   1. 所有状态：这些“全局状态”，实际是context内的全局状态

      - VAO、VBO、FBO
      - shader program
      - blend\depth\stencil等opengl状态
      - viewport\scissor

   2. GPU资源：由这个context创建和管理的：

      - texture
      - buffer
      - shader\program
      - framebuffer

      资源不属于进程、线程，而是属于context

   3. 当前线程的绑定关系

      - 一个contex在某一时刻，只能被一个线程current（持有？）
      - 一个线程可以切换不同context，但同一时间只能用一个；

2. 多context的场景

   1. 多个窗口，每个窗口都有自己的context，因为每个窗口都有自己的framebuffer、swapchain

      ```
      Window A → Context A
      Window B → Context B
      ```

      

   2. 多线程渲染、资源加载，渲染线程和资源加载线程有自己的context;

      - opengl不允许多个线程共享同一个context，一个context只能有一个线程current

      ```
      线程A → Context A
      线程B → Context B
      ```

      

   3. 资源共享：多个context可以**共享GPU资源**（texture\buffer\shader），但渲染状态不共享；

      ```
      Render Context
      Loader Context（共享资源）
      ```

      

   4. osg中，多个camera\viewer->多个context

3. pass与context的关系 : Pass 是“渲染步骤”，Context 是“运行环境”

   1.  正确关系是： **多个 pass 通常运行在“同一个 context 里”**

      ```
      Context（环境）
       └── Pass1（一次绘制）
       └── Pass2
       └── Pass3
      ```

   2. 一个 pass 本质是什么？

      一个 pass 只是：

      - 绑定一组状态（shader / FBO / texture）
      - 执行一批 draw call

      比如：

      ```c++
      // Pass 1：渲染到 GBuffer
      glBindFramebuffer(gbufferFBO);
      glUseProgram(gbufferShader);
      drawScene();
      
      // Pass 2：Lighting
      glBindFramebuffer(defaultFBO);
      glUseProgram(lightingShader);
      drawFullscreenQuad();
      ```

      👉 注意：

      - 没有任何 context 切换
      - 只是 **状态切换**

   3. 


