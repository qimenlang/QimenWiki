# Spark粒子

### 功能

1. 粒子逻辑 + 数据结构 + 更新机制
2. 渲染部分需要自己对接

## 核心架构

1. ##### System（系统）：类似一个“粒子场景”

   - 粒子系统的顶层容器
   - 管理多个 Group

2. **Group（粒子组）**

   - 一组具有相同属性的粒子
   - 每个 Group 有：
     - 生命周期
     - 最大粒子数
     - 物理参数

   比如：火焰组、烟雾组

3. ##### **Emitter（发射器）**：控制粒子“从哪里来”

   常见类型：

   - 点发射（Point）
   - 线发射（Line）
   - 面发射（Plane）
   - 球体发射（Sphere）

   控制参数：

   - 发射速率（flow）
   - 初始速度
   - 初始方向

4. **Modifier（修改器 ）：控制粒子“怎么动”，类似物理力系统**

   例如：

   - 重力（Gravity）
   - 风（Wind）
   - 阻力（Friction）
   - 旋转

5. ##### **Renderer（渲染器）**：负责“怎么画出来”

   SPARK 本身提供一些基础实现：

   - Billboard（广告牌）
   - Point Sprite
   - Line Renderer

   但通常需要自己写 shader + 渲染路径

6. **Model（模型）：定义粒子的“属性结构”，相当于“粒子模板”**

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

3. 



### 其他：

- **Spark 粒子系统的“资产”** 通常指一个粒子效果的完整配置（发射器、修改器、渲染器的参数组合），保存为 `.spark` 或 `.spk` 文件。使用 Spark 官方自带的 **Spark Editor**（也叫 Spark Particle Editor）

spark : git@github.com:Synxis/SPARK.git

spkgen：git@github.com:fredakilla/spkgen.git

