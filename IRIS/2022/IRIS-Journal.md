6/24

- 熟悉filament代码  
  - visual studio 配置运行filament，断点调试  DONE

- 为什么要封装一层，为什么不能直接用filament？  只使用了filament 的材质、渲染部分； DONE
- 桥接模式：分离抽象与实现，可分别单独变化，沿两个方向变化互不影响； DONE

6/25

- 装饰模式decorator\包装器wrapper DONE
- repo git 的区别
  - 在 repo 里，所有 module 都是平级关系，每个 module 的版本管理完全独立于任何其他 module，不会像 submodule 那样，提交了子 module 代码，也会对主 module 造成影响。

6/27

- filament 动画代码走读  DONE
- piccolo 动画代码走读  

6/28

- 调试IRISEngine
  - 场景如何管理的;没有场景管理
  - 如何查看log ; logcat

6/29

- 加载FBX 模型文件
  - 加载骨骼数据
  - 加载动画数据

- 梳理Piccolo动画系统

6/30

- 实现骨骼动画，推演过程；   
- 了解协程的概念  
- https://godbolt.org/



7/1

- 调研ozz-animation,基本满足业务要求
  - 支持骨骼蒙皮动画
  - 支持动画混合
    - 二维混合
    - Additive Blending
    - Partial Blending
  - 支持IK 
  - 支持Attach
  - 动画数据压缩、优化
  - 简单的动画控制：播放、暂停、调整时间、调整速度
  - 线程安全
- ozz-animation作为第三方库引入

7/4

- 完成ozz-animation 引入
  - android studio gradle换成cmake 18.1 ndk升级到24

- 引擎中实现骨骼动画效果

- 对比filament 的动画合ozz动画库

7/5

- ozz-animation引入  DONE

7/6

- FBX数据导入
- iris中驱动一个骨骼，实现蒙皮动画效果

7/7-9

- 参照gltf数据填充renderable过程，完成fbx数据填充renderable过程

7/10 -12

- filament库拉一个分支，集成assimp库，从assimp导入fbx文件，完成数据填充，实现正确骨骼动画；
- 在filament分支上，继续集成ozz-animation库，替换骨骼动画解算过程；
- ozz-animation提供的工具fbx2ozz在linux环境上不能用，在windows环境上转换可能是

7/13

- assimp 导入fbx数据到ozz-animation DONE
- 经fbs2ozz工具转换的ozz格式数据，在ozz-animation中解算错误的问题  DONE

7/18

- 在ozz sample中实现assimp导入fbx的全部蒙皮骨骼动画 DONE
  - animation的track如何与骨骼joint对应？  
  - Mesh 渲染 
- iris中蒙皮动画无法通过setbones接口驱动问题 DONE

7/22

- 动画系统搭建
  - 骨骼动画&Blend Shape动画&物理模拟动画
  - 混合：一维、二维、masked、加法等混合
  - Attachment & User channel
  - 后处理：Two Bone IK、Aim IK
  - 状态机&混合树
    - 状态数据采用配置文件的方式

  - 动画控制

7/25

- 实现动画状态机
  - 切换动画clip
  - 动画平滑过渡 DONE
- 动画资源管理
  - 使用统一骨骼资源  
  - 在ozz sample中转换骨骼逆绑定矩阵
- 模型
  - unity quest2 demo中手势动作导出
- 动画系统测试
  - 各种FBX模型文件导入测试

8/1

- 状态机
  - Switch Case 状态机
  - table driven 状态机
- 动画混合
  - 一维混合  DONE
  - 二维混合
  - 加法混合
  - mask混合
  - 混合树
- 动画控制  DONE
  - 开始、暂停、循环
- 模型加载测试

  - **导出的手部模型骨骼、动画无法正确加载**
- 动画系统接口输出

  - 问题：单纯看reality kit接口，还是不知道该我们的动画系统该先输出哪些接口，需要结合具体的需求；
  - 需要多参考几个开源引擎的动画系统进行设计；OGRE

8/8

- 完成所有混合
  - 一维混合 DONE
    - 一维混合无级变速还有bug DONE
    - 是否标准化时间 可选
  - mask 混合 DONE
    - 只提供上下半身混合，或者指定一个upper_body_root
  - 加法混合 DONE
  - 二维混合  
- 完成所有混合的泛化  DONE
  - mask混合暂时只支持上下半身，暂时不做泛化
- **完成混合树架构**   #####
- **混合树的动画控制**  ####
  - 混合树的层级与动画控制器的关系

- 动画资源管理  **2**
- **冻结过渡**  **2**  DONE
- hade code 状态机，做一个demo，最好实现手势动画； DONE
- 代码重构
- 接口设计、测试、文档、注释    **1**  
  - FBX加载的通用性测试  

- 代码移植   **0**
  - 一维混合使用太多FBX动画，会产生无法显示场景问题
  - 场景无法显示 偶现
  - 一个模型使用了两套mesh，一维混合时出现 mesh分离问题,分离的程度不固定
  - IO 读取FBX模型时不稳定
  - Blend2D 崩潰BUG

8/15

1. 过渡 
   - 冻结过渡 DONE
2. 代码重构及移植
   - 状态机二维表格接口
   - 4种混合，创建及参数调整接口

3. 动画资产管理 
4. ASSIMP加载FBX通用性测试
5. 代码review\合并\提交

8/20

1. 调研物理引擎
2. 补齐动画接口使用说明 readme

8/24

1. Unity中复刻quest2手势，掌握原理
   - 打通ouclus 原工程 ： mask 权重是如何控制的？
   - 新制作的fbx 大量无关骨骼，无初始姿态

2. 混合树架构设计
   - Sampler不该继承BlendSpace
   - _dt不该作为全局时钟
   - 混合与时间无关，只与权重有关
     - Sampler：sample(ratio)
     - BlendSpace:blend(weight)
   - 二维混合的泛化
     - delaunay ？？
   - 一维混合的泛化：可以设置坐标

3. 子状态机架构设计

8/31

1. 提升效率
2. 优化assimp解析FBX到ozz数据格式模块
   - 目前临时使用全部解析所有noded的方案，解决部分fbx（手、APP 3D图标模型）不适配问题； DONE
   - 多mesh 动画不同步问题：
   - 部分FBX文件在模型加载阶段，崩；
3. 动画模块重构Skeleton数据冗余问题及解决scaleFactor影响动画效果问题；
   - 不同模型的scaleFactor不同，1，100；
4. 完成动画混合空间混合树架构 DONE
5. 二维混合泛化  DONE
   - 使用delaunay三角刨分+重心坐标计算权重；
   - OR 逆双线性插值 https://iquilezles.org/articles/ibilinear/
   - OR 暂时简单泛化+双线性插值，只支持矩形；

6. 完善动画模块状态机优化
   - 支持设置状态转换条件，替换表格驱动的状态机；
   - 支持子状态机，及状态机之间转换；
   - 支持设置动画参数  DONE

7. 在unity或unreal 100% 复刻ouculus手势；
8. irisengine中100%复刻ouculus手势；
9. 完成动画模块使用文档及example readme；
10. 参照UE4\Unity现有动画系统使用流程，完善动画系统；
11. 动画接口升级


9/19

1. irisengine动画接口及BUG修改
   - PlayAnimation接口修改 DONE
   - 多submesh模型，各submesh动画不同步问题 DONE
   - irisengine 加载FBX大量测试
2. 动画系统升级
   - 重新实现状态机
   - 支持状态转换条件设置
   - 代码整理、重构、移植
3. 动画系统demo输出
   - ouculus手势完全复刻
   - 输出一个完整展现动画系统功能的demo
4. irisengine 编译配置、debug、窗口

9/26

1. 重新修改提供动画接口
   - createAnimationController 默认静止
   - 返回Controller智能指针
   - 动画事件回调
   - 保证动画不支持时，不崩
2. irisengine 加载FBX大量测试
3. 动画播放完事件
4. BUG:加载模型崩溃的BUG
5. SceneObject、Actor管理：参照Unreal 、ogre、godot，进行优化
6. irisengine 编译配置、debug、窗口
7. OZZ预编译

9/27

1. 实现刚体层级动画
   - 
2. BUG
   - snow.fbx  加载崩

- Maskblend优化 20%
- 动画接口优化 20%
  - 效率为什么这么低，一个模块改了又改，每次设计都不对；


9/10

1. 完成动画资源管理模块
2. 加入cache2单元测试

9/11

1. 完成二维混合
2. 完成mask混合

9/12

1. 完成手部模型demo



11/26

1. 阴影问题
   - 修改shadowMap,重新抓帧
   - 启用IBL无阴影问题
   - 阴影性能问题
2. 配置editor需要的环境
3. Cat动画验证
