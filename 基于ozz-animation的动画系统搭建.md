# 动画需求拆分

1. 一期需求（预期两到三周，截止7.15）
   - 骨骼动画
   - 动画资源管理
   - 播放控制：开始、暂停等
   - 动画混合
     - 一维混合(两个关键帧数据插值得到普通帧)
     - 二维混合(走到跑两个动作切换时，中间一个时间段需要对两个动作进行插值)
     - 加法混合：Additive blending is different from normal blending because it does not interpolate from a pose to an other. Instead it combines poses, meaning the two animations can be seen at the same time. 
     - 
2. 动画控制（需参考RealityKit、Tween等工具，待继续讨论拆分）
   - 动画编辑：在时间线上对物体的transform进行曲线编辑等
   - 动画切换：状态机
3. 待定需求
   - MorphTarget (主要用于表情等对细节要求高的动画)
   - IK (在手抓握不同物体时，手的形状适应物体的大小)
   - Attach：The idea is to get the joint matrix from the model-space matrices array (for the selected "hand" joint), and use this matrix to build transformation matrix of the attached object (the "sword").
4. 

# 动画系统梳理

1. 骨骼动画
   - 骨骼层级树状结构
     - 一个关节为根，其余为根关节的子孙；
     - 每个关节存储父关节索引、逆绑定矩阵、关节名；
   - 姿势
     - 绑定姿势（bind pose）:三维网格绑定到骨骼时的姿势，一般用T-Pose 或者A-Pose;
2. 动画片段
   - 动画时间
     - 动画的时间是连续的，动画片段几乎不会在整数帧上采样
   - 循环动画
     - 若动画是非循环的，则30帧动画有31个采样点
     - 若动画是循环的，则30帧动画的31个采样点钟最后一个采样点是冗余的，与第一个采样点重复
   - 归一化时间：无论动画时间多长，归一化到0-1，0表示动画开始，1表示动画结束
     - 动画同步时，需要对两个片段进行归一化同步，以**相同的归一化速率**分别推进两个动画；
   - 全局时间线&局部时间线
   - 连续通道函数：
     - 对每个通道进行线性插值时，使用分段线性逼近，是曲线尽量连续；
   - 事件触发器：
     - 在动画的时间点上设置事件触发器，时间索引经过触发器时，事件便会送交引擎；
     - 事件触发器通常用于音效、粒子特效；
   - 定位器：
   - 
3. 顶点动画
4. 动画混合
   - 一维混合
   - 二维混合
   - Masked Blending
   - Additive Blending
5. 动画状态机
6. 动画混合树
   - 动画对齐：两个动画在标准化时间(1s)的相同时间点上对齐；
7. IK
8. 对标Apple
   - 动画控制
     - 动画播放控制：[AnimationPlaybackController]，开始，暂停，继续，停止
     - 动画事件
     - 动画切换
   - 动画资源管理
   - 混合：动画树

# 基于ozz-animation的动画系统搭建

1. 动画系统知识点梳理
   - 插值
     - translation & scale :使用线性插值 c = a（1-t）+b(t)
     - rotation :
       - 欧拉角 ： 直接对欧拉角进行线性插值，得到的结果是非线性的，还可能会处罚万向节死锁；
       - 四元数 ： 提供 球面插值 SLerp(Spherical Interpolation），可以实现线性插值；[NLerp？？？]
     
   - 逆绑定矩阵：
   
     - **This matrix describes the position of the mesh in the local space of this bone when the skeleton was bound.** Thus it can be used directly to determine a desired vertex position, given the world-space transform of the bone when animated, and the position of the vertex in mesh space.
     - **描述的是顶点在局部骨骼坐标系下的偏移，用于将顶点从模型坐标系转换到局部/骨骼坐标系**
   
     ![Mesh Space](https://learnopengl.com/img/guest/2020/skeletal_animation/mesh_space.png)
   
     ![Bone Space](https://learnopengl.com/img/guest/2020/skeletal_animation/bone_space.png)
   
2. ozz库技术要点梳理
   - Data orentied Develop
   - PlaybackController 控制动画播放时间
   - SamplingJob 对动画资产的某一帧进行采样，得到pose数据
     - Context :存储一些中间计算结果
       - 帧的一致性？？？
       - SOA ???

   - 数学库优势？
   
3. 整理搭建思路
   - 蒙皮模块放在filament，ozz提供数据驱动
   - ECS架构，Animation Component
   - 辅助效果绘制
   - UI界面及效果开关
   
4. 在知乎上直接出一篇基于ozz的动画系统搭建专栏

