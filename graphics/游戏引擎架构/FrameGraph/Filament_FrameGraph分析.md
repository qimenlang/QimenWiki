### 相关概念

1. FrameGraph
2. DependencyGraph
   - Node
     - PassNode
     - RenderPassNode
     - PresentPassNode
     - ResourceNode
   - Edge
   - VirtualResource
   - Resource
3. FrameGraphPass
4. FrameGraphTexture



## Filament中定义的各Pass

| 阶段分类                     | 核心Pass示例                                      | 阶段目标                                               |
| :--------------------------- | :------------------------------------------------ | :----------------------------------------------------- |
| **🔧 前期准备与几何处理**     | `Depth Blit`, `Structure Pass`, `Mipmap Pass`     | 准备深度、几何结构等基础数据，为后续屏幕空间效果服务。 |
| **✨ 核心渲染与屏幕空间效果** | `SSAO`, `SSR`, `Separable Blur`, `ShadowCascades` | 计算环境光遮蔽、屏幕空间反射、阴影等，增强场景真实感。 |
| **🎨 后处理与图像增强**       | `Bloom`, `DoF`系列, `TAA`, `FXAA`, `colorGrading` | 处理景深、泛光、抗锯齿和颜色分级，塑造最终视觉风格。   |
| **🖥️ 最终合成与输出**         | `compositing`, `resolve`, `blitting`, `upscaling` | 将各种处理结果合并，并最终输出到屏幕。                 |

### 🔧 一、前期准备与几何处理

这个阶段主要为后续各种效果准备所需的数据和资源。

- **`Depth Blit`**：将**几何渲染阶段产生的深度缓冲区**复制到另一张纹理。这份副本是许多屏幕空间效果（如SSAO、SSR、DoF）的**基础数据源**。
- **`Structure Pass` / `StructureMipmap`**：生成并处理场景的几何结构信息（如法线），并为其创建Mipmap链。这对于需要粗糙度信息的**屏幕空间反射（SSR）** 至关重要，高级别的Mipmap用于模拟粗糙表面的模糊反射。
- **`Mipmap Pass`** / **`VSM Generate Mipmap Pass`**：为特定纹理（如阴影贴图）生成Mipmap。**VSM（Variance Shadow Maps）** 需要Mipmap来进行高效的阴影过滤。

### ✨ 二、核心渲染与屏幕空间效果

这个阶段利用第一步准备的数据，计算一系列增强画面真实感的复杂效果。

- **`SSAO Pass`**：利用**深度和法线信息**，计算场景中物体接触处的**环境光遮蔽**，增加阴影细节。
- **`SSR Pass`** & **`Prepare MipmapSSR Pass`**：`SSR Pass` 利用颜色、深度和法线信息，计算**屏幕空间反射**。`Prepare MipmapSSR Pass` 会为反射所需的资源（如颜色缓冲区）准备Mipmap链，以优化性能和质量。
- **`Separable Blur Pass`** /  **`Separable Gaussian Blur Pass`**：**可分离的高斯模糊**是一种优化技术，将二维模糊拆分为两个一维模糊。它常被用于**平滑SSAO图**、**Bloom效果**等。
- **`ShadowCascades`**：负责管理和渲染**CSM（级联阴影映射）**，解决远距离阴影的精度问题。
- **`combining array tex`** & **`shadowmap debug pass`**：前者可能用于合并阴影贴图数组，后者则是一个**调试工具**，用于将阴影贴图可视化到屏幕上，方便开发者检查。

### 🎨 三、后处理与图像增强

这是后处理的核心阶段，负责处理画面的艺术风格和视觉质量。

#### **1. 景深 (DoF)**

这是一个复杂的多Pass效果，模拟相机焦点外的模糊效果。

- `DoF Downsample` / `DoF Mipmap`：**准备阶段**，对颜色和深度缓冲区进行降采样，生成适合计算CoC的尺寸（COC ： Circle of Confusion，“弥散圆”\“模糊圈”）。
- `DoF Tiling`：将屏幕分割成小块（Tile），并计算每个Tile内的最大CoC，用于优化模糊计算范围。
- `DoF Dilate`：扩张CoC区域，避免在模糊与非模糊区域边界出现硬边。
- `DoF` / `DoF Median`：**核心计算阶段**，执行景深模糊。`Median`（中值滤波）可能用于消除模糊过程中产生的噪声或光斑瑕疵。
- `DoF combine`：**合成阶段**，将模糊后的前景/背景与焦点内的清晰图像按CoC权重混合。

#### **2. 泛光 (Bloom)**

模拟明亮光源在相机镜头中产生的光晕效果。

- `Bloom Downsample`：从图像中**提取高亮部分**，并进行多次降采样，同时通常会在每次降采样时进行模糊。
- `Bloom Upsample`：将降采样并模糊后的各层图像**逐级上采样并混合**，形成平滑的泛光效果。

#### **3. 抗锯齿与颜色分级**

- **`TAA`** & **`Export TAA history`**：`TAA` 通过混合当前帧与**历史帧**来平滑锯齿。`Export TAA history` 很可能负责将当前帧的颜色等信息存储下来，作为下一帧的"历史帧"。
- **`fxaa`**：一种快速的屏幕后处理抗锯齿技术，通常作为备用或在TAA之后进行补充处理。
- **`FidelityFX FSR1 Rcas`**：AMD的**对比度自适应锐化**技术，用于在图像被放大或处理后恢复细节和清晰度。
- **`colorGrading`**：**颜色分级**，应用查找表（LUT）或一系列色彩变换，为最终画面定调。它通常在所有效果之后、色调映射之前或同时进行。
- **`Flare`**：模拟**镜头耀斑**效果，通常需要识别画面中的极亮区域。

### 🖥️ 四、最终合成与输出

这是渲染管线的最后一步，负责将所有处理结果拼合成最终像素并显示。

- **`compositing`**：一个**广义的合成Pass**，可能将多个渲染层（例如主场景、UI、后处理效果）合成为最终图像。
- **`resolve`** / **`resolveDepth`**：在MSAA（多重采样抗锯齿）中，`resolve` 负责将多个样本**解析（平均）为每个像素一个颜色值**。`resolveDepth` 可能对深度缓冲区进行类似操作。
- **`blitting`**：一个**通用的复制操作**，可能用于在不同纹理间复制图像数据，或者将最终图像传递到显示缓冲区。
- **`upscaling`**：**图像放大**，如果渲染分辨率低于显示分辨率，此Pass（可能集成FSR、DLSS等）负责高质量地放大图像。
- **`Uncompress Pass`**：移动端或特定API下，纹理可能采用压缩格式。此Pass在读取前将其**解压为常规格式**。



- Structure Pass
- StructureMipmap
- Picking Render Pass
- SSR Pass
- SSAO Pass
- Separable Blur Pass
- Mipmap Pass
- Gaussian Blur Pass (separable)
- Prepare MipmapSSR Pass
- DoF Downsample
- DoF Mipmap
- DoF Tiling
- DoF Dilate
- DoF
- DoF Median
- DoF combine
- Downsample
- Bloom Downsample
- Bloom Upsample
- Flare
- Uncompress Pass
- colorGrading
- fxaa
- TAA
- Export TAA history
- FidelityFX FSR1 Rcas
- upscaling
- compositing
- blitting
- Depth Blit
- resolve
- resolveDepth
- VSM Generate Mipmap Pass
- ShadowCascades
- combining array tex



