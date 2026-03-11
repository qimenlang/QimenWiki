------

 **GLSL shader 在 OSG 或 OpenGL 环境下的“保留字段、内建变量、内建函数”全面总结”**，包括 `gl_Color` 等老旧和现代的变量，方便查阅和工程使用。整理如下，按类别系统总结。

---

# 1️⃣ 顶点/片元内建变量（保留字段）

### **顶点着色器相关**

| 变量                  | 类型  | 含义                     | 用途 / 备注                                                  |
| --------------------- | ----- | ------------------------ | ------------------------------------------------------------ |
| `gl_Position`         | vec4  | 顶点裁剪空间坐标         | 必须输出给 GPU，顶点着色器必写                               |
| `gl_PointSize`        | float | 点精灵大小               | 在渲染点云时控制点大小                                       |
| `gl_VertexID`         | int   | 顶点索引                 | OpenGL 3.3+ 可用于数组索引                                   |
| `gl_InstanceID`       | int   | 实例化绘制编号           | instanced rendering 时使用                                   |
| `gl_Normal`           | vec3  | 顶点法线（固定管线遗留） | 老 OpenGL，可用 `in vec3 normal` 替代                        |
| `gl_Color`            | vec4  | 顶点颜色（固定管线遗留） | 老 OpenGL 可直接用在 `gl_FrontColor`，现代用 `in vec4 color` |
| `gl_MultiTexCoord0…7` | vec4  | 多纹理坐标（固定管线）   | 现代用 `in vec2 texCoord0` 等                                |

### **片元着色器相关**

| 变量                     | 类型  | 含义                                | 用途 / 备注                             |
| ------------------------ | ----- | ----------------------------------- | --------------------------------------- |
| `gl_FragCoord`           | vec4  | 当前片元在屏幕空间 `(x, y, z, 1/w)` | SSAO、屏空间计算、深度采样              |
| `gl_FrontColor`          | vec4  | 顶点传递的颜色                      | 老管线输出给光栅化颜色                  |
| `gl_FrontSecondaryColor` | vec4  | 二级顶点颜色                        | 用于光照混合                            |
| `gl_FragColor`           | vec4  | 片元输出颜色                        | 现代 GLSL 用 `out vec4 fragColor;` 替代 |
| `gl_FragData[i]`         | vec4  | 多渲染目标输出                      | MRT (Multiple Render Target) 输出       |
| `gl_FragDepth`           | float | 片元深度值                          | 可修改深度缓冲                          |
| `gl_SampleID`            | int   | MSAA 采样编号                       | 多重采样时使用                          |
| `gl_SamplePosition`      | vec2  | MSAA 采样位置                       | 多重采样时使用                          |

---

# 2️⃣ OSG 内建 Uniform（保留字段）

OSG 在渲染时会自动填充这些 Uniform，常用矩阵和时间：

| Uniform 名称                    | 类型  | 含义         | 用途                                           |
| ------------------------------- | ----- | ------------ | ---------------------------------------------- |
| `osg_ModelViewMatrix`           | mat4  | Model × View | 坐标变换到相机空间                             |
| `osg_ProjectionMatrix`          | mat4  | 投影矩阵     | 坐标变换到裁剪空间                             |
| `osg_ModelViewProjectionMatrix` | mat4  | MVP          | 顶点直接输出 `gl_Position = MVP * vec4(pos,1)` |
| `osg_NormalMatrix`              | mat3  | 法线矩阵     | 用于法线变换到 view space                      |
| `osg_ViewMatrix`                | mat4  | 相机视图矩阵 | 世界→相机空间                                  |
| `osg_ViewMatrixInverse`         | mat4  | 相机逆矩阵   | 相机世界位置、屏幕→世界坐标                    |
| `osg_ProjectionMatrixInverse`   | mat4  | 投影矩阵逆   | 裁剪→视图空间                                  |
| `osg_FrameTime`                 | float | 当前帧时间   | 动画、特效                                     |
| `osg_SimulationTime`            | float | 模拟时间     | 物理/动画同步                                  |

---

# 3️⃣ 常用 GLSL 内建函数

| 函数                                     | 用法                           | 作用                 |
| ---------------------------------------- | ------------------------------ | -------------------- |
| `radians(x)`                             | 转弧度                         | `deg→rad`            |
| `degrees(x)`                             | 转角度                         | `rad→deg`            |
| `sin(x), cos(x), tan(x)`                 | 三角函数                       | 动画、方向计算       |
| `asin(x), acos(x), atan(x)`              | 反三角函数                     |                      |
| `pow(x,y)`                               | x^y                            | 指数运算             |
| `exp(x), log(x)`                         | 指数 / 对数                    |                      |
| `sqrt(x)`                                | 开方                           |                      |
| `abs(x)`                                 | 绝对值                         |                      |
| `sign(x)`                                | 符号函数                       |                      |
| `floor(x), ceil(x), fract(x)`            | 向下取整 / 向上取整 / 小数部分 |                      |
| `mod(x,y)`                               | 取模                           |                      |
| `min(x,y), max(x,y)`                     | 取最小/最大                    |                      |
| `clamp(x, a, b)`                         | 限幅                           |                      |
| `mix(x, y, a)`                           | 插值                           | x*(1-a)+y*a          |
| `step(edge,x)`                           | 阶跃函数                       | x>=edge 返回1，否则0 |
| `smoothstep(edge0, edge1, x)`            | 平滑阶跃                       | 平滑插值             |
| `length(v)`                              | 向量长度                       |                      |
| `distance(p1,p2)`                        | 两点距离                       |                      |
| `dot(v1,v2)`                             | 点积                           | 光照、投影           |
| `cross(v1,v2)`                           | 叉积                           | 法线计算             |
| `normalize(v)`                           | 单位化向量                     | 法线、方向           |
| `reflect(I,N)`                           | 反射向量                       | 反射光、环境映射     |
| `refract(I,N,eta)`                       | 折射向量                       | 折射、折射光线       |
| `texture(sampler2D, uv)`                 | 纹理采样                       | 现代 shader 采样纹理 |
| `textureProj(sampler2D, vec4)`           | 投影纹理                       | 阴影贴图             |
| `textureLod(sampler2D, uv, lod)`         | 指定 mipmap 层                 | 延迟渲染 / 高级纹理  |
| `textureGrad(sampler2D, uv, dPdx, dPdy)` | 指定导数                       | 高级采样             |

---

# 4️⃣ 固定管线遗留变量

> 现代 GLSL 不建议使用，但 OSG 兼容旧模型时可能用到：

| 变量                  | 类型  | 含义                   |
| --------------------- | ----- | ---------------------- |
| `gl_Color`            | vec4  | 顶点颜色               |
| `gl_SecondaryColor`   | vec4  | 第二顶点颜色           |
| `gl_FogCoord`         | float | 雾坐标                 |
| `gl_Vertex`           | vec4  | 顶点位置（旧固定管线） |
| `gl_MultiTexCoord0…7` | vec4  | 多纹理坐标             |

---

# 5️⃣ 使用建议（OSG + 延迟渲染 / 多 Pass）

1. **OSG 保留 uniform**

   * MVP, ViewMatrix, ViewMatrixInverse, NormalMatrix 统一用内建变量
   * 多 Pass 或 RTT 时最好手动传 uniform

2. **旧固定管线变量**

   * `gl_Color`, `gl_Vertex` 等仅兼容老模型
   * 新 shader 用 `in vec3 pos; in vec3 normal; in vec4 color;` 替代

3. **常用函数**

   * `reflect/refract/mix/clamp` 是延迟渲染、透明、光照计算最常用
   * `texture` 系列采样纹理

4. **矩阵流向图**

   ```
   Model Space -> ModelView (osg_ModelViewMatrix)
                 -> View Space
                 -> Clip Space (osg_ModelViewProjectionMatrix)
                 -> NDC -> Screen (gl_FragCoord)
   ```

   * `osg_ViewMatrixInverse` 用于从 View Space 回 World Space

---

