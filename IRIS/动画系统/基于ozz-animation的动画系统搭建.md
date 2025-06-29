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
4. 动画节奏控制
   - 缓入缓出
   - 贝塞尔曲线控制

5. 动画事件触发
   - completed\Looped\Terminated

6. 内置手势动画

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

3. 顶点动画

4. 动画混合
   - 线性插值混合  LERP
     - 求两个骨骼姿态的中间姿态：对骨骼的每个关节的局部姿势（SQT）进行线性插值，局部姿态是指父关节的局部空间；
     - 应用：用于实现C0连续，也被称为淡入淡出，会产生“滑脚“瑕疵；
       - 在时间轴上，求两个关键帧的中间插值帧 ，C0连续；
       - 淡入淡出：两个动画clip在时间轴上适当地重合，流畅地从A动画过渡到B动画
         - 平滑过渡:
         - 冻结过渡:
         - 淡入淡出权重的控制
           - linear
           - 缓入\缓出曲线(ease in、ease out )
           - 可以使用贝塞尔计算缓入缓出曲线
       - 核心姿势：不用混合，A动作的最后姿势能匹配后续片段的首个姿势，该姿势为核心姿势；
     
   - 二维混合
     - 简单的二维混合是三个一维混合，用到4个clip
     - 三角剖分+三角中心坐标得到混合因子的二维混合
     
   - Masked Blending
     - 把某些关节的混合因子设为0，来掩盖掉
     - 会造成不自然的动作
       - 相连关节的混合因子突兀地改变，会导致身体一部分动作与另一部分动作分离，不协调；可以在几个临近关节上逐渐改变混合因子；
     
   - Additive Blending
     - 区别动画：两段正常动画的区别，**存储了一个姿势变化至另一个姿势所需的改变**，区别动画可以被加进普通的动画片段，以产生一些有趣的姿势和动作变化；
     
     - 两个正常动画相减，得到区别动画；或者说，区别姿势，只需要一个姿势；
     
     - 加法混合是一个正常动画和区别动画*权重相加；权重 0-1；
     
       
   
5. 动画状态机
   - 从当前状态进入下一个状态的选项称为状态过渡条件
   - 状态集合+状态过渡条件+当前状态+事件=状态机；
   - 每一个状态有一个与之关联的clip或子状态或混合树，处于该状态时就会播放；
   - 状态机行为：是一类特殊的脚本，可以将状态机行为附加到状态机中的单个状态，用于：检测地面、激活控制相关特效等；
   - 子状态机：角色通常具有包含若干阶段的复杂动作，合理的做法是每个阶段用一个子状态机表征，而不是用单个状态来处理整个动作；
   - 动画层：Unity中使用动画层来管理不同身体部位的复杂状态机；

6. 状态层 (state layer)   **[状态层是否是分层状态机？？？？]**

   - 状态层用于独立的操控身体的不同部位；

   - 对n个层各自的混合树取值，产生n个骨骼姿态，再把这些姿态混合在一起；

   - 顽皮狗的分层状态架构：
      - 底层（base layer）产生全身的骨骼姿势，其上的层可以产生全身、分部骨骼或加法姿势；

      - 加法层 ：假设其输出的混合是一个区别姿势，使用加法混合和下层的输出合并；

      - LERP层 （线性插值）： 把下层的姿势进行LERP混合；

   - 分层状态机把多个时间上独立的混合树（每层一个）转换为单个统一的混合树；

7. 扁平加权平均混合：在某一指定时间内，多个动画对骨骼最终姿态产生影响；动画片段的混合使用加权平均；

8. 动画混合树
   - 动画对齐：两个动画在标准化时间(1s)的相同时间点上对齐；
   - 4种原子混合：
     - 片段
     - 二元lerp混合
     - 二元加法混合：只使用一帧的区别姿势，并用权重控制加法混合
     - 三元lerp混合
   - 定义：根据浮点动画参数在相似的动画clip之间进行连续混合。例如根据速度混合走跑；
   - 区分过渡（transtion）和混合树，二者都用于创建平滑的动画；
     - 过渡：在给定的时间内，从一个动画状态平滑过渡到另一个动画状态；在动画状态机中有使用；过渡针对两个动画；
     - 混合树：通过不同程度的合并多个动画来使动画平滑混合，由Animator Controller的一个混合参数控制混合程度；混合的动作要具有相似的性质和时机（即在标准化时间的时间点上要对齐）；混合树针对多个动画;

9. IK

10. 对标Apple
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
     
   - 数学库优势：硬件加速的SIMD运算

3. 整理搭建思路
   - 蒙皮模块放在filament，ozz提供数据驱动
   - ECS架构，Animation Component
   - 辅助效果绘制
   - UI界面及效果开关

4. 动画系统架构

   1. 动画管道 (Animation Pipeline)

      - 对包含动画的物体，动画管道为其取得一个或多个动画片段及对应的混合因子作为输入，混合后计算得到的骨骼姿态作为输出；
      - 后处理钩子：留给IK及物理动画对骨骼动画进行修正；

   2. 动画状态机（Action State Machine）

      - 提供状态驱动的动画接口
      - 状态机确保角色能从一个状态平滑地过渡到另一个状态
      - 如果身体的不同部分需要做不同、独立的事情，例如边跑边瞄准边开火，可以通过状态层使用多个独立的状态机控制角色；

   3. 动画控制器  (Animation Controller)

      - 管理角色行为模式、封装动画相关代码

   4. 总结：

      动画管道提供基础的动画姿势设置及混合功能；动画状态机可以使用复杂的混合树和数据驱动，提供更方便、容易理解的动画驱动接口，也可提供分层机制，并行运行多个状态机；动画控制器趋向于管理相对更长更泛化的角色行为，例如：掩护、驾驶等；

5. 其他

   - 蒙皮矩阵调色板？？

6. 



### 动画系统进展

1. 集成ozz-animation,打通动画pipeline  DONE
2. 动画状态机 （预期7.31）
   - 接受手柄输入，切换不同状态对应的动画
   - 动画切换时实现平滑过渡
   - 使用配置文件的形式，配置动画状态、clip、混合参数等

## 动画控制：AnimationPlaybackController

1. 控制播放、暂停、重播

## 动画资源管理：AnimationResource  [需要json序列化、反序列化？？？]

1. 实体的[`availableAnimations`](https://developer.apple.com/documentation/realitykit/entity/availableanimations) 数组存放其可用的动画资源，从文件中读取实体时，也读取其绑定的动画资源；
2. 调用实体的 playAnimation播放指定的动画，并返回动画控制器AnimationPlaybackController
3. 可以是一个clip也可以是一个混合？？

## 动画定义AnimationDefinition

1. 描述动画的时间信息、bind target 、BlendLayer 、视觉效果
2. 配置动画、控制动画时间

## 填充模式AnimationFillMode

1. 确定哪些动画帧在正常持续时间之外显示
2. none/forwards/backwards/both

## 动画计时函数： AnimationTimingFunction

1. 控制动画过渡的节奏
2. 淡入、淡出、贝塞尔曲线、直接线性插值等

## 刚体动画和骨骼动画

1. 刚体动画，需要考虑一部分node 动另外一部分node不动的情况
2. 骨骼动画认为全部的node都是动的，全部都有AnimationTrack





























