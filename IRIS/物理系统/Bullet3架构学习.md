### Bullet3特性

1. 离散和连续碰撞检测、射线和凸包扫描、凹凸Mesh的碰撞形状
2. 刚体约束解算、载具、泛化6DOF、 ragdolld的椎体扭转约束
3. 软体动力模拟:衣料、绳索；两路交叉的可变形形体；

### 系统架构

1. bullet3的架构 高度可定制化和模块化，可以扩展；

### 刚体物理管线

1. 计算过程：计算重力、预测位置、宽相碰撞检测、窄相碰撞检测、解算约束、位置整合
2. 刚体物理管线的计算过程和所需要的数据全部打包在dynamic world中（btDiscreteDynamicsWorld）

### 碰撞检测

1. 最近点查询的算法和加速数据结构
   - btCollisionObject：碰撞物体,是有世界transform信息和形状的object
   - btCollisionShape : 碰撞物体的形状
   - btGhostObject : 特殊的碰撞物体，在本地碰撞查询中有用；
   - btCollisionWorld ：碰撞世界，保存了所有碰撞物体，提供查询接口；
2. 宽相碰撞检测相关的加速数据结构：
   - btDbvtBroadphase : 基于AABB的BVH树，两个，一个管理静态物体，一个管理动态物体,物体可以在两棵树之间移动；
   - btAxisSweep3 / bt32BitAxisSweep3 :实现3D扫描和修剪
   - btSimpleBroadphase :
3. 碰撞形状
   - 基础形状：box,sphere、capsule、cylinder、cone、multi sphere
   - 组合形状：多个基础形状组合，可以形成concave
   - 凸包形状：通过传入一些一个指定的顶点，形成凸包形状
   - 凹三角形网格：使用BVH树组织所有静态三角形网格物体
4. 碰撞边距 
   - 碰撞边距可以提升性能和碰撞检测的稳定性
   - 默认 0.04，相当于是对碰撞形状的拉伸
   - 对一些碰撞形状会产生gap问题
5. 碰撞算法矩阵 : 对于两个碰撞形状的不同组合，都会有对应的单独的算法
6. GJK ： the convex distance calculation algorithm，用于计算凸多面体、圆柱、圆锥、胶囊体等与其他碰撞形状的碰撞；

### 碰撞过滤

1. 三种方式指定物体是否可以碰撞
   - masks
   - broadphase filter callbacks
   - nearcallbacks （registered in narrow phase）

### 刚体运动学

1. 在碰撞检测的基础上，实现刚体运动学，包括：力、质量、惯性、速度、约束

   - btRigidBody用于模拟6自由度物体
   - 约束包括：合页约束、两点约束、锥形扭转约束、滑块约束、泛化6DOF约束
   - btDiscreteDynamicsWorld是碰撞体和约束的容器，提供分步模拟函数进行模拟解算；

2. 三种不同类型的刚体

   - 动态刚体：质量为正数，每帧物理模拟之后，动态刚体都更新transform
   - 静态：质量为0，不移动不碰撞
   - 运动学刚体：质量为0，可以被动画驱动，与动态刚体交互时，是单向的，动态刚体会被运动学刚体推动，反过来，动态刚体不会对运动学刚体有任何影响；

   以上所有的刚体都会被加入btDiscreteDynamicsWorld，并被指定碰撞形状；碰撞形状可以被用来计算质量分布（也叫惯性张量）；

3. 刚体的transform就是其质心的transform，该transform不能scale\shear；

4. MotionState

   - 管理物体的位置信息
   - 插值：bullet自动对物体的运动进行插值

5. 物体被用来做动画时，要取消其物理模拟；

6. 物理模拟系统以60fps的固定帧率运行，渲染系统的帧率大于60，则去物理模拟结果时需要插值，小于60,则每渲染一帧，会运行多于一次模拟；























