### 10月份任务

1. 动画系统升级优化
   - 同时支持刚体动画+骨骼动画
   - 动画接口优化
   - 代码移植（混合空间+状态机）
   - 支持手势功能
   - 测试：支持所有现有动画资源
2. irisengine 基础建设

   - vscode+cmake 编译、debug 
   - IRIS编辑器视口:用于展示成果
   - 搭建Cache2自动化单元测试框架
3. irisengine引入物理引擎
   - 碰撞检测
   - 刚体运动模拟

10.17 -22

1. 动画接口规范
   - 同时支持骨骼动画、刚体动画 DONE
   - node节点可以设置transform,先set local transform 再计算skinning matrix DONE
   - 骨骼、动画资源管理

2. 手势动画接入
   - 代码移植：混合空间、状态机、参数设置
   - 对接inputmanager测试

3. 动画全面测试

   - 10000 node 刚体和骨骼动画测试
   - 全面测试以往所有FBX动画

   

10.13

1. 对于要架构的动画系统、物理系统、粒子系统，需要全面地借鉴Unreal、OGRE引擎；
1. 太阳底下没有新鲜事，不能自己埋头造轮子，最重要的是去借鉴外部的引擎的设计，自己造轮子，费时费力还可能做不好；
1. 本周末，完成对Unreal、Ogre引擎动画系统的拆解，输出文档
1. 下周开始参照这两个引擎，对iris的动画系统进行升级；

10-20

1. 如何确保AnimationController先于Skeleton组件更新；
2. Skeleton组件是模型的还是submesh的；submesh;
3. 
