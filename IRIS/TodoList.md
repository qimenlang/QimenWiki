## 试用期OKR

1. IRIS基础建设

   - vscode+cmake 编译、debug irisengine
   - IRIS编辑器视口:用于展示成果
   - 搭建Cache2自动化单元测试框架

2. 场景序列化

   - 场景管理

3. 搭建动画系统
   - 骨骼动画
   - 动画控制
   - 混合树
   - 动画状态机
   - 动画后处理
   - BlendShape动画
   - 基于物理的动画

4. 粒子系统搭建

5. 物理系统搭建

   

## 7-8月OKR 

#### O1：搭建动画系统（待讨论）

1. KR1：支持骨骼动画、动画混合；
   - 集成ozz,驱动filament renderable DONE
2. KR2 ：支持动画播放控制，包括开始、暂停、播放速度调节；
3. KR3： 支持手部动画，手柄输入控制手部模型动作；
   - 状态机、数据驱动
   - 物理检测 + IK后处理
   - Attachment
4. 输出动画接口
5. 学习unity 动画系统
   1. https://docs.unity3d.com/462/Documentation/Manual/MecanimAnimationSystem.html

   2. https://docs.unity3d.com/cn/current/Manual/AnimationOverview.html

   3. https://zhuanlan.zhihu.com/p/37995835

6. 粒子系统

动画系统目前进展

1. 动画控制：实现了暂停、恢复、循环模式设置等功能 DONE
2. 动画混合：
   - 一维混合、二维混合、加法混合、Mask混合 DONE
   - *混合树架构  需要重新设计实现*
3. 动画状态机
   - 表格驱动状态机 ： 已实现，用户可通过定义二维状态转换表，设定状态机转换关系 
4. 动画过渡：
   - 冻结过渡  ：已实现
   - *平滑过渡 ：依赖于混合树架构，待实现*
   - *EASE IN、EASE OUT ：待实现*
5. 动画资源管理：已实现

以上未实现内容，后续新开Issue再重新实现；



动画系统TODO :

1. 动画混合：混合树架构需要重新设计实现
2. 动画过渡：

8.22-31

#### 搭建物理系统

1. Bullet3 MultiBody example复刻到irisengine

## 9-10月OKR

1. 升级完善动画系统
   - 混合空间优化：
     - 二维混合优化：支持任意数量动画node
     - Mask 混合优化：支持任意数量动画层及各层根骨骼配置
     - 完善混合树架构，同时支持混合动画clip和其他混合空间
   - 完善动画状态机，支持动画参数设置、状态转换条件设置
2. irisengine中复刻Oculus 手势demo
3. irisengine基础建设

   - vscode+cmake 编译、debug irisengine
   - IRIS编辑器视口:用于展示成果
   - 搭建Cache2单元测试框架
4. irisengine引入bullet
   - 碰撞检测
   - 刚体运动模拟



#### 动画系统优化进展：

1. 动画混合树







