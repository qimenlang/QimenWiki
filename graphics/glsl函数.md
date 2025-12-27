# GLSL 常用函数及意义详解

GLSL 提供了丰富的内置函数，用于数学运算、几何计算、纹理操作等。以下是分类整理的常用函数：

## 1. 数学函数

### 基本数学运算
```glsl
// 绝对值
float abs(float x);
vec2 abs(vec2 x);
vec3 abs(vec3 x);

// 符号函数 (返回 -1, 0, 1)
float sign(float x);

// 取整函数
float floor(float x);  // 向下取整
float ceil(float x);   // 向上取整
float round(float x);  // 四舍五入
float fract(float x);  // 获取小数部分

// 最大值最小值
float max(float a, float b);
float min(float a, float b);
float clamp(float x, float minVal, float maxVal);  // 限制在范围内
```

### 插值和混合
```glsl
// 线性插值
float mix(float x, float y, float a);  // x*(1-a) + y*a

// 平滑插值
float smoothstep(float edge0, float edge1, float x);

// 阶梯函数
float step(float edge, float x);  // x < edge ? 0.0 : 1.0
```

### 幂指对数函数
```glsl
// 幂函数
float pow(float x, float y);      // x的y次幂
float exp(float x);               // e的x次幂
float exp2(float x);              // 2的x次幂

// 对数函数  
float log(float x);               // 自然对数
float log2(float x);              // 以2为底对数

// 平方根和倒数平方根
float sqrt(float x);
float inversesqrt(float x);       // 1/sqrt(x) - 高性能
```

## 2. 三角函数

```glsl
// 基本三角函数
float sin(float angle);
float cos(float angle);
float tan(float angle);

// 反三角函数
float asin(float x);    // 反正弦
float acos(float x);    // 反余弦  
float atan(float y, float x);  // 反正切（带象限判断）
float atan(float y_over_x);    // 反正切

// 双曲函数
float sinh(float x);
float cosh(float x);
float tanh(float x);

// 角度弧度转换
float radians(float degrees);  // 角度转弧度
float degrees(float radians);  // 弧度转角度
```

## 3. 几何函数

### 向量运算
```glsl
// 向量长度
float length(vec2 x);
float length(vec3 x);

// 距离计算
float distance(vec2 p0, vec2 p1);  // 两点间距离
float distance(vec3 p0, vec3 p1);

// 点积和叉积
float dot(vec2 x, vec2 y);
float dot(vec3 x, vec3 y);
vec3 cross(vec3 x, vec3 y);        // 仅适用于3D向量

// 向量归一化
vec2 normalize(vec2 x);
vec3 normalize(vec3 x);

// 反射和折射
vec3 reflect(vec3 I, vec3 N);      // 反射向量
vec3 refract(vec3 I, vec3 N, float eta);  // 折射向量

// 面向操作
float faceforward(float N, float I, float Nref);  // 确保法线面向观察者
```

## 4. 矩阵函数

```glsl
// 矩阵乘法
mat2 matrixCompMult(mat2 x, mat2 y);  // 逐元素乘法（不是矩阵乘法）

// 外积（向量->矩阵）
mat2 outerProduct(vec2 c, vec2 r);
mat3 outerProduct(vec3 c, vec3 r);

// 转置
mat2 transpose(mat2 m);

// 行列式和逆矩阵
float determinant(mat2 m);
mat2 inverse(mat2 m);
```

## 5. 纹理采样函数

### 2D纹理采样
```glsl
// 基本采样
vec4 texture2D(sampler2D sampler, vec2 coord);
vec4 texture2D(sampler2D sampler, vec2 coord, float bias);

// LOD采样
vec4 texture2DLod(sampler2D sampler, vec2 coord, float lod);

// 投影采样
vec4 texture2DProj(sampler2D sampler, vec3 coord);
vec4 texture2DProj(sampler2D sampler, vec4 coord);

// 偏移采样
vec4 texture2DOffset(sampler2D sampler, vec2 coord, ivec2 offset);
```

### 立方体纹理采样
```glsl
vec4 textureCube(samplerCube sampler, vec3 coord);
vec4 textureCubeLod(samplerCube sampler, vec3 coord, float lod);
```

## 6. 片段处理函数

### 导数函数（片段着色器专用）
```glsl
// 屏幕空间导数
float dFdx(float p);      // x方向变化率
float dFdy(float p);      // y方向变化率
float fwidth(float p);    // abs(dFdx(p)) + abs(dFdy(p))
```

## 7. 噪声函数

```glsl
// 噪声函数（返回值范围通常为 [-1, 1] 或 [0, 1]）
float noise1(float x);
float noise1(vec2 x);
float noise1(vec3 x);
float noise1(vec4 x);
```

## 8. 整数函数

```glsl
// 位运算
int bitfieldExtract(int value, int offset, int bits);
int bitfieldInsert(int base, int insert, int offset, int bits);

// 查找函数
int findLSB(int value);   // 最低有效位
int findMSB(int value);   // 最高有效位
```

## 实际应用示例

### 颜色处理
```glsl
// 颜色饱和度调整
vec3 adjustSaturation(vec3 color, float saturation) {
    float luminance = dot(color, vec3(0.299, 0.587, 0.114));
    return mix(vec3(luminance), color, saturation);
}

// 颜色对比度调整
vec3 adjustContrast(vec3 color, float contrast) {
    return mix(vec3(0.5), color, contrast);
}
```

### 光照计算
```glsl
// Phong光照模型
vec3 phongLighting(vec3 normal, vec3 lightDir, vec3 viewDir, vec3 diffuseColor) {
    float diff = max(dot(normal, lightDir), 0.0);
    vec3 reflectDir = reflect(-lightDir, normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    
    return diffuseColor * diff + vec3(1.0) * spec;
}
```

### 屏幕空间效果
```glsl
// 简单的边缘检测
float edgeDetection(sampler2D tex, vec2 uv, vec2 pixelSize) {
    float center = texture2D(tex, uv).r;
    float left = texture2D(tex, uv - vec2(pixelSize.x, 0.0)).r;
    float right = texture2D(tex, uv + vec2(pixelSize.x, 0.0)).r;
    float top = texture2D(tex, uv - vec2(0.0, pixelSize.y)).r;
    float bottom = texture2D(tex, uv + vec2(0.0, pixelSize.y)).r;
    
    return abs(left - right) + abs(top - bottom);
}
```

### UV动画和变形
```glsl
// 流动UV效果
vec2 flowingUV(vec2 uv, float time, float speed) {
    return uv + vec2(sin(time * speed), cos(time * speed)) * 0.1;
}

// 旋转UV
vec2 rotateUV(vec2 uv, float rotation) {
    float s = sin(rotation);
    float c = cos(rotation);
    mat2 rotMat = mat2(c, -s, s, c);
    return rotMat * (uv - 0.5) + 0.5;
}
```

## 性能提示

1. **优先使用内置函数**：它们经过高度优化
2. **避免复杂运算**：在片段着色器中谨慎使用 `pow()`, `sin()`, `cos()` 等
3. **使用近似函数**：当精度要求不高时
   ```glsl
   // 快速反平方根近似（类似Quake III的方法）
   float fastInverseSqrt(float x) {
       return inversesqrt(x);
   }
   ```

这些函数构成了GLSL编程的基础，熟练掌握它们能够大大提高着色器开发的效率和质量。