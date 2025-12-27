## ECS总结

#### 一、ECS架构

1. Entity 实体
   - 本身并不保存数据，只有ID数据；
   - 作为容器，起到组合（关联）Component的作用；
2. Component
   - 保存数据
   - 分类：
     - Transform:保存pos、rotation、scale，关联Model矩阵；
     - Renderable：保存mesh顶点、索引、材质（shader、纹理）、以及渲染状态信息；
     - Animator：保存骨骼树、顶点骨骼权重等数据；
     - Collider、RigidBody：物理引擎各种geometry的碰撞体，质量、速度、重力、摩擦力等；
     - Controller：物体角色的参数；
   - ComponentManager管理所有类型的组件的数组；
3. System
   - 真正的业务逻辑，处理特定的组件数据
   - 分类：
     - TransformSystem:使用TransformComponent数据，更新世界变换矩阵；
     - RenderingSystem：使用TransformComponent、Renderable，渲染模型;
     - AnimationSystem：计算各骨骼节点Transform，写入到transform组件；
     - PhysicsSystem：处理碰撞检测、物理模拟；
     - InputSystem：处理硬件输入数据，写入数据到Controller、Script等组件；
     - ScriptSystem：游戏业务逻辑；
   - 执行顺序：输入系统->脚本系统->物理系统->动画系统->transform系统->渲染系统

二、ECS优势

1. 组合优于继承
   - 可以通过添加组件实现新功能，避免复杂的继承关系；
2. 性能优化：
   - 缓存友好：SOA(数据可以被连续存储在数组中)，系统可以高效便利，极大利用CPU缓存；
   - 天然支持多线程；