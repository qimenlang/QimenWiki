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
  - 动画平滑过渡
- 动画资源管理
  - 使用统一骨骼资源  
  - 在ozz sample中转换骨骼逆绑定矩阵
- 模型
  - unity quest2 demo中手势动作导出
- 动画系统测试
  - 各种FBX模型文件导入测试












