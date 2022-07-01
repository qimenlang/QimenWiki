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





