### Modern OpenGL

#### BASICS

1. opengl模式
   - 即时模式（immediate mode）：即固定管线模式，有一套固定的执行流程，Opengl3.2版本及之前，比较简单、易理解、灵活性、性能较差（cpu gpu通信频繁）
   - 核心模式（core-profile）：即着色器渲染模式，可以通过编写 shader来实现图形渲染，所谓的modern Opengl；
2. opengl状态机
   - conotext:切换一个状态，便会更换对应的上下文
   - state
3. opengl支持扩展
   - 新的技术或者优化被提出来之后，都是先放在显卡的驱动的扩展里面实现；只要显卡支持该扩展，便可以升级；之后新的技术会被放到opengl的下一个版本里；
4. object：C 结构体，用于保存一个状态合集，配合状态机；
   - 创建一个object,并保存id   //用于context中对象的保存状态
   - 通过id绑定object到context的目标位置
   - 设置context中对象的选项
   - 解绑object

#### 创建窗口

1. GLFW创建窗口
   - glfw库可以创建窗口，配合opengl使用；
     - 创建opengl context
     - 定义窗口参数
     - 处理用户输入
2. GLAD
   - 由于opengl只是一个标准，具体由显卡厂家去实现，由于OpenGL驱动版本众多，它大多数函数的位置都无法在编译时确定下来，需要在运行时查询；
   - glad是一个开源库，本质上是一个网络服务，告诉glad opengl的版本，glad返回该版本opengl的所有函数；
   - 可以理解为glad管理opengl的函数指针；
3. 使用imgui搭配glfw

#### 三角形

1. 光栅化流程

   - 顶点着色器
     - 从一个三维坐标系转变为另外一个三维坐标系：模型空间 * MVP->标准设备坐标（NDC）,只有处在NDC中才可见；
     - 顶点其他属性的计算处理，uv,法线等；
   
   
      - 图元装配：装配图元为：点、线、三角形；
   
      - 几何着色器：以装配好的图元作为输入，可以生成新的顶点，以组合成新的形状；
   
      - 光栅化：将图元拆分成一个个的片段/像素；（用到重心坐标）
   
      - 片段着色器：**[片段（fragment）是需要渲染一个像素的所有数据的集合]**
        - 片段着色器运行之前，先进行clipping，裁剪掉相机视线之外的所有片段，以提升性能；
        - 计算得到最后的像素结果，会使用到一些3D场景里的信息，例如光照、阴影等；
   
      - 测试和混合：
        - 深度/stenciel测试片段着色器运行之后，进行深度测试，片段着色器的很多运算白做了
        - alpha测试和混合：物体的透明度，混合颜色；从远到近；
   
2. Vertex Buffer Object(VBO): VBO是GPU存储的数据

   - 在GPU的内存中保存顶点数据，顶点着色器可以**直接**访问（instant access）GPU内存中的顶点数据；
   - CPU向GPU传数据是性能瓶颈，因此每次尽量批量地向GPU传数据；

3. opengl shader使用流程：shader是GPU处理数据的规则

   - 创建shader : glCreateShader
   - 绑定shader字符串 : glShaderSource
   - 编译shader : glCompileShader
   - 链接shader到program :
     - 创建shader program ： glCreateProgram
     - 绑定shader object : glAttachShader
     - 链接shader object 到program: glLinkProgram   
   - 激活shader program ：glUseProgram

4. GPU如何解读VBO缓冲中的数据，使用glVertexAttribPointer函数，将VBO的数据与顶点着色器中的vertex Attributes（layout (location = xxx)）链接起来,须计算步长、偏移等信息；

5. Vertex Array Object (VAO) ： 事实上存储了VBO的结构信息，用于链接VBO与顶点着色器中的vertex Attributes;**而且还存储了EBO信息；**

6. Element Buffer Object（EBO）: 存储顶点的索引 index；

   ![Image of VAO's structure / what it stores now also with EBO bindings.](https://learnopengl.com/img/getting-started/vertex_array_objects_ebo.png)

#### shaders

1. 结构
   - \#version version_number    opengl版本号
   - 输入 input :  in type in_variable_name; 
     - also known as a **vertex attribute**.  
     - vertex attributes 的数量是有限制的，最少16 个vec4；每种硬件并不相同，可以通过GL_MAX_VERTEX_ATTRIBS查询；
   - 输出 output
   - uniforms
   - main func
2. vec4
   - rgba=xyzw=stpq
   - `vecn`: the default vector of `n` floats.
   - `bvecn`: a vector of `n` booleans.
   - `ivecn`: a vector of `n` integers.
   - `uvecn`: a vector of `n` unsigned integers.
   - `dvecn`: a vector of `n` double components.
3. 两个shader之间传输数据
   - 发送数据的shader定义一个out,接受数据的shader定义一个in
   - 两边定义的数据的类型和名称必须保持一致
4. Uniforms 用于从程序向着色器传输数据
5. Fragment Shader ： Fragment interpolation is applied to all the fragment shader's input attributes.

#### Textures

1. 纹理采样:纹理坐标的范围是(0,1),只需要给顶点着色器传入每个顶点的纹理坐标，纹理坐标的插值在光栅化阶段完成；

2. texture wrapping 方式：纹理坐标超出（0，1）范围之后的处理方式

   - GL_REPEAT

   - GL_MIRRORED_REPEAT

   - GL_CLAMP_TO_EDGE

   - GL_CLAMP_TO_BORDER

     <img src="https://learnopengl.com/img/getting-started/texture_wrapping.png" alt="img" style="zoom: 80%;" />

     

3. Texture Flitering 纹理过滤 : 从浮点数UV值，根据分辨率，转换到具体的像素值

   - GL_NEAREST : 选择中心距离UV坐标最近的纹素，OPENGL 的默认选项；

     ![img](https://learnopengl.com/img/getting-started/filter_nearest.png)

   - GL_LINEAR ：取相邻的几个像素的插值，按照相邻像素中心到uv坐标的距离计算；

     ![img](https://learnopengl.com/img/getting-started/filter_linear.png)

4. MipMaps

   - Opengl 提供函数 glGenerateMipmaps，可以生成mipmap
   - 四种过滤方式
     - GL_NEAREST_MIPMAP_NEAREST：选择最近的mipmap纹理，纹理采样时使用最近点方式；
     - GL_LINEAR_MIPMAP_NEAREST：选择最近的mipmap纹理，纹理采样时使用临近像素插值的方式；
     - GL_NEAREST_MIPMAP_LINEAR：在两个minmap之间插值得到纹理，纹理采样时使用最近点方式；
     - GL_LINEAR_MIPMAP_LINEAR：在两个mipmap之间插值得到纹理，纹理采样时也是使用临近像素插值的方式；
   - 放大/缩小
     - GL_TEXTURE_MIN_FILTER ： 纹理缩小是，可以使用mipmap的纹理过滤方式；
     - GL_TEXTURE_MAG_FILTER ： 纹理放大时，不能使用mipmap的纹理过滤方式，只能用普通的过滤方式：GL_LINEAR和GL_NEAREST

5. 加载和创建纹理

#### Transformation

1. 矩阵的乘法
   - 多个矩阵相乘时，顺序是从右向左的
   - 先做缩放，再做旋转，最后平移，从左向右的顺序是：平移、旋转、缩放；

#### 坐标系

1. 坐标空间

   - Local space (or Object space)

   - World space

   - View space (or Eye space)

   - Clip space  & NDC

     Clip Space是一个顶点乘以MVP矩阵之后所在的空间，**Vertex Shader的输出就是在Clip Space上**（划重点），接着，GPU会做剪裁，剔除在Clip Space范围之外的顶点，然后GPU再做**透视除法**将顶点转到NDC。

     透视除法将Clip Space顶点的4个分量都除以w分量，就从Clip Space转换到了NDC了。

   - Screen space

     vertex shader的输出是裁剪空间，fragment shader的输入是屏幕空间；

     **(Vertex Shader) => Clip Space => (透视除法) => NDC => (视口变换) => Screen Space => (Fragment Shader)**

     ![img](https://learnopengl.com/img/getting-started/coordinate_systems.png)

   - 深度缓冲

     - glfw会自动创建深度缓冲区、也自动创建了颜色缓冲区；
     - 片段着色器输出颜色时，会比较当前片段的深度和深度缓冲区的深度，大于，则丢弃计算结果，小于，则覆盖到framebuffer，同时更新深度缓冲区z值；
     - 深度测试默认是关闭的，打开深度测试：glEnable(GL_DEPTH_TEST); 

   #### 相机

   1. 相机的定义

      - 相机的空间对应了view space 

      - To define a camera we need its **position** in world space, the direction it's looking at, a vector pointing to the right and a vector pointing upwards from the camera. [**look-at \ right \ up** ]

        ![img](https://learnopengl.com/img/getting-started/camera_axes.png)

      - camera direction : 在opengl的相机坐标系中方，指向Z轴的负方向；[为什么要是负的]
   
      - Right axis : 在相机坐标系中，指向X轴的正方向；
   
        - 使用y-up方向的向量，vector3f(0,1,0)，与camera direction 向量叉乘，得到right axis方向
   
      - Up axis
   
        - 使用 camera direction与 right axis向量叉乘，得到相机的Up axis
   
      - Look-at ：使用 right 、up 、 direction 、position
      
        ![image-20220505190447238](C:\Users\51039\AppData\Roaming\Typora\typora-user-images\image-20220505190447238.png)
      
      - tick中的deltatime ：是渲染上一帧的时间；相机移动的速度乘以deltatime，以保证在不同计算能力的设备上得到相同效果
      
      - 欧拉角
      
        <img src="https://learnopengl.com/img/getting-started/camera_pitch_yaw_roll.png" alt="Euler angles yaw pitch and roll" style="zoom:67%;" />

### 光照

1. 光源的颜色与物体的颜色相乘，得到物体反射的颜色；

   ```glsl
   glm::vec3 lightColor(0.33f, 0.42f, 0.18f);
   glm::vec3 toyColor(1.0f, 0.5f, 0.31f);
   glm::vec3 result = lightColor * toyColor; // = (0.33f, 0.21f, 0.06f);
   ```

2. Phong模型

   - ambient : 环境光，使用光源的颜色乘以一个系数模拟就可以了；也可以指定一个环境光颜色；
   - diffuse ： 漫反射
   - specular ： 高光

3. 材质

   - 材质，实际上是光照模型的参数配置，定义了环境光、漫反射、高光等，这三个都是颜色；

     ```glsl
     struct Material {
         vec3 ambient;
         vec3 diffuse;
         vec3 specular;
         float shininess;
     }; 
     ```

     - ambient 定义了在环境光下，表面反射的颜色，一般与物体表面颜色相同
     - diffuse 定义了在漫反射下，表面反射的颜色，一般也和物体表面颜色相同
     - specular定义了高光颜色
     - shininess 影响高光散射的半径

   - 光源属性

     ```glsl
     struct Light {
         vec3 position;
       
         vec3 ambient;
         vec3 diffuse;
         vec3 specular;
     };
     
     uniform Light light;  
     ```

     

     - position 光源位置
     - ambient : 设置为较小值
     - diffuse : 通常认为是光源本身的颜色
     - specular: 直接设置为vec3(1.0);

4. 光源

   - 方向光
     - light.w == 0.0; 用light.xyz定义方向
     - light.w == 1.0; 是点光源，用light.xyz定义光的位置，每个片段计算一个方向
   - 点光源
     - 光源带有位置，并且朝所有的方向进行散射，光照强度随着半径增大而衰减
   - 聚光灯
   - 多光源的计算：
     - 每个片段上，叠加计算所有光源对该片段的影响；
     - 



### 模型导入

1. Assimp库
   - 支持导入导出数十种格式的模型
   - Assimp导入数据到 其自定义的数据结构中，用户可以从该结构中获取数据，传给opengl
2. c++的struct
   - c++的struct的成员属性的内存布局是顺序的；
   - int offsetof(struct , property);第一个参数是结构体，第二个参数是属性，返回偏移量；



### 深度测试

1. 深度缓存使用的float精度有16、24、32bit,一般使用24bit；

2. 深度测试，就是拿当前计算的片段的深度和深度缓冲的深度进行比较，小于则深度测试通过，更新framebuffer和深度缓冲，大于则深度测试失败，丢弃当前片段；

3. 深度测试发生在屏幕空间，在片段着色器之后，gl_FragCoord是屏幕空间坐标，gl_FragCoord .xy是二维屏幕空间，**gl_FragCoord .z**是深度（非线性）； 

4. early-z 提前深度测试
   - **(Vertex Shader) => Clip Space => (透视除法) => NDC => (视口变换) => Screen Space => (Fragment Shader)**
   - 深度测试是在Fragment Shader、模板测试之后，early z将深度测试提前到Fragment之前，在视口变换得到屏幕空间坐标之后，进行深度测试；
   - 提前深度测试的限制是，Fragment shader不能再更新深度缓存；

5. 深度值并不是线性的，而是正比于深度值的倒数；z值在观察空间中还是线性的，乘以**投影矩阵**到达裁剪空间后，就变成了下图所示；
   $$
   F_{depth} = \frac{1/z-1/near}{1/far - 1/near}
   $$
   ![Graph of depth values in OpenGL as a non-linear function](https://learnopengl.com/img/advanced/depth_non_linear_graph.png)

6. 非线性深度转换为线性深度

   - 先转换到NDC空间

   - 再乘以投影矩阵中的z值变换的逆变换

     ```glsl
     float LinearizeDepth(float depth) 
     {
         float z = depth * 2.0 - 1.0; // back to NDC 
         return (2.0 * near * far) / (far + near - z * (far - near));	
     }
     ```

7. prevent z-fighting

   - 加一个小的offset
   - 尽可能将near平面设置远一点，但要避免裁剪近处物体，以防止在近处占用太多的深度精度，这样整个frustum有更好的深度精度；
   - 使用更高的深度精度


### 模板测试

1. 模板测试在片段着色器之后，深度测试之前，也会抛弃掉一部分片段计算结果
2. 模板缓冲的精度使用8 bit，取值范围0-255；

### 混合

1. 





















