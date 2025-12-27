好的，GLSL（OpenGL Shading Language）提供了丰富的内置函数来简化着色器编程。这些函数大多针对 GPU 进行了高度优化。下面我将分类介绍一些最常用和关键的 GLSL 函数。

---

### 1. 数学函数

这些是使用最频繁的函数，用于各种计算。

| 函数                                     | 描述                                                         | 常用场景                                  |
| :--------------------------------------- | :----------------------------------------------------------- | :---------------------------------------- |
| `radians(degrees)`                       | 将角度转换为弧度                                             | 几乎所有三角函数计算前                    |
| `degrees(radians)`                       | 将弧度转换为角度                                             | 可能需要角度输出时                        |
| `sin(angle)`, `cos(angle)`, `tan(angle)` | 三角函数                                                     | 周期性运动、波动、圆                      |
| `asin(x)`, `acos(x)`, `atan(y, x)`       | 反三角函数                                                   | 计算角度                                  |
| `pow(x, y)`                              | 返回 x 的 y 次幂                                             | 光泽度、衰减、非线性调整                  |
| `exp(x)`                                 | 返回 e 的 x 次幂                                             | 指数计算                                  |
| `log(x)`                                 | 返回 x 的自然对数                                            |                                           |
| `exp2(x)`, `log2(x)`                     | 以 2 为底的指数/对数                                         | 亮度、HDR 处理                            |
| `sqrt(x)`                                | 返回 x 的平方根                                              | 向量长度归一化、距离计算                  |
| `inversesqrt(x)`                         | 返回 x 平方根的倒数                                          | **计算归一化向量时比 `1.0/sqrt(x)` 更快** |
| `abs(x)`                                 | 返回 x 的绝对值                                              | 距离、符号处理                            |
| `sign(x)`                                | 返回 x 的符号                                                | 判断正负、翻转方向                        |
| `floor(x)`                               | 向下取整                                                     | 数值离散化（如纹理数组索引）              |
| `ceil(x)`                                | 向上取整                                                     |                                           |
| `fract(x)`                               | 返回 x 的小数部分                                            | 重复图案、噪声、伪随机数                  |
| `mod(x, y)`                              | 返回 x 除以 y 的余数                                         | 平铺纹理、创建网格                        |
| `min(x, y)`                              | 返回 x 和 y 中的最小值                                       | 限制值、相交测试                          |
| `max(x, y)`                              | 返回 x 和 y 中的最大值                                       | 限制值、相交测试                          |
| `clamp(x, minVal, maxVal)`               | 将 x 限制在 [minVal, maxVal] 范围内                          | **确保颜色值在 [0,1] 等范围内**           |
| `mix(x, y, a)`                           | 返回 x 和 y 的线性插值                                       | **lerp，用于颜色混合、动画过渡**          |
| `step(edge, x)`                          | 如果 x < edge 返回 0.0，否则返回 1.0                         | 创建硬边过渡、二值化                      |
| `smoothstep(edge0, edge1, x)`            | 如果 x <= edge0 返回 0.0，如果 x >= edge1 返回 1.0，否则在 0 和 1 之间进行 Hermite 插值 | **创建平滑的过渡、抗锯齿**                |

---

### 2. 几何函数

用于向量和矩阵操作。

| 函数                      | 描述                                                 | 常用场景                         |
| :------------------------ | :--------------------------------------------------- | :------------------------------- |
| `length(x)`               | 返回向量 x 的长度                                    | 计算距离、幅度                   |
| `distance(p0, p1)`        | 返回点 p0 和 p1 之间的距离                           | 计算两点间的距离                 |
| `dot(x, y)`               | 返回向量 x 和 y 的点积                               | **计算夹角、光照（Lambert）**    |
| `cross(x, y)`             | 返回向量 x 和 y 的叉积                               | 计算法线、切线、副切线           |
| `normalize(x)`            | 返回与 x 方向相同但长度为 1 的向量                   | **标准化向量（方向向量、法线）** |
| `faceforward(N, I, Nref)` | 如果 dot(Nref, I) < 0 返回 N，否则返回 -N            | 确保法线朝向观察者               |
| `reflect(I, N)`           | 根据入射向量 I 和法线 N 返回反射向量                 | 镜面反射、环境映射               |
| `refract(I, N, eta)`      | 根据入射向量 I、法线 N 和折射率比值 eta 返回折射向量 | 透明材质（水、玻璃）             |

---

### 3. 纹理查找函数

用于从纹理中采样颜色。

| 函数                              | 描述                                                      | 常用场景                       |
| :-------------------------------- | :-------------------------------------------------------- | :----------------------------- |
| `texture(sampler, coord)`         | 从纹理采样器中使用坐标 coord 进行采样                     | **最常用的 2D 纹理采样**       |
| `texture(sampler, coord, bias)`   | 使用指定的 LOD bias 进行采样（主要在 Fragment Shader 中） | 手动控制细节级别               |
| `textureLod(sampler, coord, lod)` | 在指定的细节级别 lod 上进行采样                           | 计算着色、手动 Mipmap 控制     |
| `texelFetch(sampler, ivec2, lod)` | 使用整数纹理坐标直接获取纹素，不进行过滤                  | 精确像素操作、纹理作为数据数组 |
| `textureSize(sampler, lod)`       | 返回指定 LOD 的纹理尺寸                                   | 计算像素大小、屏幕后处理       |

---

### 4. 向量与分量操作

这些不是函数，而是语言特性，但极其重要。

| 操作          | 描述                                          | 示例                                                         |
| :------------ | :-------------------------------------------- | :----------------------------------------------------------- |
| **Swizzling** | 通过 `.rgba`、`.xyzw` 或 `.stpq` 重新排列分量 | `vec3 pos = vertex.xyz;` <br> `vec2 texCoord = uv.st;` <br> `float height = color.r;` <br> `vec4 myVec = otherVec.abgr; // 反转顺序` |
| **构造函数**  | 通过分量构造向量                              | `vec3 color = vec3(1.0, 0.0, 0.0); // 红色` <br> `vec4 transparentRed = vec4(color, 0.5); // 带透明度的红色` |

---

### 常用代码模式与技巧

1.  **计算漫反射光照 (Lambert)**
    ```glsl
    vec3 norm = normalize(Normal);
    vec3 lightDir = normalize(lightPos - FragPos);
    float diff = max(dot(norm, lightDir), 0.0);
    vec3 diffuse = diff * lightColor;
    ```

2.  **计算镜面反射光照 (Phong/Blinn-Phong)**
    ```glsl
    // Blinn-Phong (更高效)
    vec3 viewDir = normalize(viewPos - FragPos);
    vec3 halfwayDir = normalize(lightDir + viewDir);
    float spec = pow(max(dot(norm, halfwayDir), 0.0), shininess);
    vec3 specular = spec * lightColor;
    ```

3.  **使用 `smoothstep` 创建平滑过渡**
    ```glsl
    // 在 edge0 和 edge1 之间创建平滑的过渡带
    float edge0 = 0.1;
    float edge1 = 0.2;
    float alpha = smoothstep(edge0, edge1, intensity);
    // alpha 在 intensity < 0.1 时为 0，在 intensity > 0.2 时为 1，在中间平滑过渡。
    ```

4.  **使用 `fract` 和 `sin` 生成简单的伪随机数**
    ```glsl
    float rand(vec2 co) {
        return fract(sin(dot(co.xy, vec2(12.9898, 78.233))) * 43758.5453);
    }
    ```

5.  **使用 `mix` 进行线性插值**
    ```glsl
    // 根据一个因子 a 在颜色 A 和 B 之间混合
    vec3 colorA = vec3(1.0, 0.0, 0.0);
    vec3 colorB = vec3(0.0, 0.0, 1.0);
    float blendFactor = 0.3; // 30% A, 70% B
    vec3 finalColor = mix(colorA, colorB, blendFactor);
    ```

### 总结

- **数学函数**是着色器的基石，用于所有形式的计算。
- **几何函数**是 3D 图形光照和视觉效果的灵魂。
- **纹理函数**是将图像数据融入场景的主要手段。
- **Swizzling** 和向量操作能极大简化代码并提高可读性。

掌握这些核心函数是编写高效、强大着色器的第一步。建议在实践中多多使用它们来加深理解。