# Spark粒子

### 功能

1. 粒子逻辑 + 数据结构 + 更新机制
2. 渲染部分需要自己对接

## 核心架构

1. #### System（系统）：类似一个“粒子场景”

   - 粒子系统的顶层容器
   - 管理多个 Group

2. #### **Group（粒子组）**

   - 一组具有相同属性的粒子
   - 每个 Group 有：
     - 生命周期
     - 最大粒子数
     - 物理参数

   比如：火焰组、烟雾组

3. #### **Emitter（发射器）**：控制粒子“从哪里来”

   常见类型：

   - 点发射（Point）
   - 线发射（Line）
   - 面发射（Plane）
   - 球体发射（Sphere）

   控制参数：

   - 发射速率（flow）
   - 初始速度
   - 初始方向

   

4. #### **Modifier（修改器 ）：控制粒子“怎么动”，类似物理力系统**

   **每个 Modifier 只访问和修改自己关心的粒子属性**，且修改是基于**上一个 Modifier 处理后的结果**进行的累积叠加，因此不会冲突；

   `Modifiers` 是每帧更新粒子状态的“力/约束/事件”模块，常见用于：

   - 改速度：重力、摩擦、点质量场
   - 做碰撞：粒子-粒子、粒子-区域
   - 做生命周期事件：进区即销毁、附着发射器联动生成

   其中 `Destroyer`、`Obstacle` 继承 `ZonedModifier`，支持 zone test（inside/outside/intersect/enter/leave）。

   ------

   ##### 各 Modifier 速查

   - `Gravity`（`SPK_BasicModifiers.h`）
     - 作用：给粒子施加恒定加速度向量（可随节点变换得到 transformed value）。
     - 场景：雨滴下落、烟雾上升、风场基础偏移。
     - 效果：速度线性累积，轨迹呈抛物/偏移趋势。
   - `Friction`（`SPK_BasicModifiers.h`）
     - 作用：速度阻尼（按系数衰减）。
     - 场景：让粒子逐渐停下、减少“无限滑行”。
     - 效果：运动更“粘滞”，速度随时间衰减。
   - `PointMass`（`SPK_PointMass.h`）
     - 作用：点质量场，按距离平方影响粒子（带 offset 防止奇点）。
     - 场景：黑洞吸引、爆炸后斥力、轨道扰动。
     - 效果：向心/离心弯曲轨迹；`mass>0` 吸引，`mass<0` 排斥。
   - `Collider`（`SPK_Collider.h`）
     - 作用：粒子与粒子之间碰撞，考虑粒子尺寸和质量比，带弹性系数。
     - 场景：球团互撞、颗粒堆积、碰撞演示。
     - 效果：速度交换/反弹；`elasticity` 控制“弹”还是“粘”。
     - 代价：计算重，粒子数大时开销显著（文档明确提醒）。
   - `Obstacle`（`SPK_Obstacle.h`，继承 `ZonedModifier`）
     - 作用：粒子与 zone 几何边界碰撞反弹。
     - 场景：盒子/平面/球壳内反弹、地面碰撞。
     - 效果：按法线反射并施加切向摩擦；`bouncingRatio` 控制反弹强度，`friction` 控制切向耗散。
     - zone test：常用 `ZONE_TEST_INTERSECT` 做碰撞触发。
   - `Destroyer`（`SPK_Destroyer.h`，继承 `ZonedModifier`）
     - 作用：满足 zone 条件即 kill 粒子（初始化和每帧都会检查）。
     - 场景：出界清理、进入黑洞即消失、裁剪体积。
     - 效果：硬删除粒子，快速控制数量与边界。
   - `EmitterAttacher`（`SPK_EmitterAttacher.h`）
     - 作用：给每个粒子附一个 emitter，向目标 group 发射新粒子；可选跟随朝向/旋转。
     - 场景：拖尾、火花尾迹、子弹尾烟、母粒子派生子粒子。
     - 效果：粒子“带着发射器移动”，形成层级粒子效果（非常常用的二级特效构建器）。
   - `Rotator`（`SPK_Rotator.h`）
     - 作用：根据 `PARAM_ROTATION_SPEED` 积分更新 `PARAM_ANGLE`。
     - 场景：贴图粒子自旋（火花、碎片、叶片）。
     - 效果：角度连续变化；要求模型启用角度/旋转速度参数。

   ------

   ##### ZonedModifier 的关键点（影响 `Obstacle/Destroyer`）

   在 `SPK_ZonedModifier.h` 里，zone test 有：

   - `INSIDE` / `OUTSIDE` / `INTERSECT` / `ENTER` / `LEAVE` / `ALWAYS`

   可理解为“触发条件选择器”：

   - 想做“进入区域触发一次”用 `ENTER`
   - 想做“相交就碰撞”用 `INTERSECT`
   - 想做“在区域内持续销毁”用 `INSIDE`

   ------

   ##### 组合建议（常见配方）

   - 基础自然运动：`Gravity + Friction`
   - 容器碰撞：`Obstacle (+ Friction)`
   - 颗粒互撞：`Collider`（注意粒子规模）
   - 边界回收：`Destroyer`
   - 尾迹/子系统：`EmitterAttacher`
   - 贴图旋转感：`Rotator`

5. #### 粒子参数Para: 有5个参数（Group中），在ParaInterpolator控制其数值变化，在modifier中最终使用；

   - Scale
   - Mass
   - Angle
   - TextureIndex
   - RotationSpeed

   ```c++
     // Param
   #define SPK_ENUM_PARAM(XX)     \         
   XX(PARAM_SCALE,=0)             \    
   XX(PARAM_MASS,=1)              \  
   XX(PARAM_ANGLE,=2)             \  
   XX(PARAM_TEXTURE_INDEX,=3)     \     
   XX(PARAM_ROTATION_SPEED,=4)	   \
   ```

   

6. #### **ParaInterpolator**：参数插值器，对粒子的某些属性（如颜色、大小），根据粒子生命周期进度插值改变属性，或在“初始化时”赋值；

   1. DefaultInitializer：只做 固定初值，存活过程中 不随时间改；

   2. SimpleInterpolator：出生值、消亡值 各一个常量，整组粒子共用；粒子存活期间在这两个端点之间 随能量（energy）线性变化；

   3. RandomInitializer：诞生时在 `[min, max)` 内 随机一次，之后 不变（`interpolate` 为空）。

   4. RandomInterpolator：每个粒子在诞生时随机一对 “起点值”和“终点值”，存活期间仍按 energy 在两者之间 线性插值（和 `SimpleInterpolator` 一样是“两端线性”，但两端 按粒子随机）。

   5. GraphInterpolator：用 二维折线/分段曲线 控制参数：横轴 `x` 来自 寿命、年龄、另一参数、或速度平方；纵轴在图上的 y0 / y1 两曲线 之间再按每个粒子固定的随机比例混合，得到最终值。支持 循环图、对横轴的 随机 offset/scale（每粒子一份，存在 `DataSet`）。

      

7. #### **Renderer（渲染器）**：负责“怎么画出来”

   SPARK 本身提供一些基础实现：

   - Billboard（广告牌）
   - Point Sprite
   - Line Renderer

   但通常需要自己写 shader + 渲染路径

8. **Model（模型）：定义粒子的“属性结构”，相当于“粒子模板”**

   - 生命周期（life）
   - 大小（size）
   - 颜色（color）
   - 透明度（alpha）

## 核心功能

1. ##### 粒子生成与生命周期管理

   - 自动生成 / 销毁
   - 支持 burst（爆发）
   - 支持连续发射

2. ##### 物理模拟

   内置多种动力学：

   - 重力
   - 加速度
   - 阻尼
   - 碰撞（基础）

   但不是刚体物理 , != NVIDIA PhysX 

3. ##### 插值与曲线控制

   粒子属性可随时间变化：

   - size over life
   - color over life
   - alpha 渐变

   做烟雾/火焰很关键

4. ##### 可扩展性强

   - 自定义 Emitter
   - 自定义 Modifier
   - 自定义 Renderer
   - 自定义粒子属性

## 优劣势

1. 优点：
   - 结构清晰（System / Group / Emitter）
   - 高性能（批量更新）
   - 非常灵活（可扩展）
   - 开源（可改源码）
2. 劣势
   - 老旧、传统C++接口、不符合ECS架构
   - renderer 很弱（固定管线风格）、不支持现代 shader workflow
     - 可以只用spk的粒子数据，不用spk的渲染，自己实现？
   - CPU运算而不是GPU Compute shader,粒子数量级小
   - 生产工具链很弱：没有
     - `.spk` 是 **SPARK 自定义的二进制序列化格式**，本质上就是：把 Emitter / Group / Modifier / Renderer 等对象结构序列化进 Buffer
   - 



## 生产工具链方案

1. spkgen ：使用了数据流驱动、node graph的node editor做UI ,没必要，粒子系统是行为驱动，没有节点依赖、数据流传播；

2. osg+imgui

   - 架构：

     ```
     SPARK（模拟）
        ↓
     OSG（渲染）
        ↓
     ImGui（调参 UI）
        ↓
     JSON（存储）
     ```

     

   - IMGUI关键功能:

     - 参数面板
     - 分组结构（模拟层级）
     - 曲线编辑：实现size over lifetime、alpha over lifetime
     - 实时反馈



## 粒子设计Tip

1. ##### 分层粒子（Layered Particle System）

   ```
   控制层（Simulation Layer）
       ↓
   表现层（Render Layer）
   ```



## 粒子效果配置Tip

| 类型        | Depth Test | Depth Write | Blend     | Sort     |                                                              |
| ----------- | ---------- | ----------- | --------- | -------- | ------------------------------------------------------------ |
| 火焰 / 能量 | ON         | OFF         | ADD       | ❌ 不需要 | ADD混合，不需要排序，太亮需要tone mapping;火焰本身是发光体，混合用ADD; |
| 烟雾        | ON         | OFF         | ALPHA     | ✅ 必须   | Alpha混合，不满足交换律，需要排序;烟雾不发光，有遮挡效果，用ALPHA； |
| 爆炸碎片    | ON         | ON          | OFF       | ❌        | 不透明物体，正常深度测试写入                                 |
| UI特效      | OFF        | OFF         | ADD/ALPHA | 可选     | 永远显示在最前面                                             |

| 粒子类型  | 是否受场景光照影响 | 常见做法             |
| --------- | ------------------ | -------------------- |
| 火焰核心  | ❌ 通常不受         | 自发光 emissive      |
| 火焰烟雾  | ✅ 受光照           | 漫散射 + fog         |
| 魔法能量  | ❌ 很少受           | emissive/additive    |
| 灰尘/沙尘 | ✅ 强烈受光         | forward lit          |
| 云/雾     | ✅ 非常依赖         | 体积散射             |
| 雪花/雨滴 | ✅ 受高光           | directional/specular |
| UI粒子    | ❌ 不受             | overlay              |

## 其他：

- **Spark 粒子系统的“资产”** 通常指一个粒子效果的完整配置（发射器、修改器、渲染器的参数组合），保存为 `.spark` 或 `.spk` 文件。使用 Spark 官方自带的 **Spark Editor**（也叫 Spark Particle Editor）

spark : git@github.com:Synxis/SPARK.git

spkgen：git@github.com:fredakilla/spkgen.git

