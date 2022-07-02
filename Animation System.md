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
     - 
   - 
2. 顶点动画
3. 动画混合
   - 一维混合
   - 二维混合
   - Masked Blending
   - Additive Blending
4. 动画状态机
5. 动画混合树
   - 动画对齐：两个动画在标准化时间(1s)的相同时间点上对齐；
6. IK
7. 对标Apple
   - 动画控制
     - 动画播放控制：[AnimationPlaybackController]，开始，暂停，继续，停止
     - 动画事件
     - 动画切换
   - 动画资源管理
   - 混合：动画树