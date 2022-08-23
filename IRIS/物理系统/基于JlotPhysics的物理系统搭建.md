1. 调研
   - Physx支持多个CCD Pass，Bullet和Jolt只支持一个pass;[CCD Continuous Collision Detect连续碰撞检测]
   - Bullet使用简化了的球体做碰撞检测，而不是真实的物体形状；
   - [JoltPhysics 引擎架构](https://jrouwe.github.io/JoltPhysics/)
   - Bullet功能更全、Samples更多，Jolt相对较新，可能踩坑
2. 物理引擎基础概念
   1. 物理引擎的主要任务是检测碰撞、用物理规则解算碰撞及约束、更新物体的transform信息；
   2. 碰撞检测
      - CCD Continuous Collision Detect连续碰撞检测
      - CCD Pass
      - 碰撞盒的绑定一般都是在DCC工具或者引擎的编辑器里完成的
   3. 求解迭代器(solver iteration)
3. iris搭建物理引擎一期功能
   1. 碰撞检测系统
      - 碰撞形状
        - 胶囊、球体等

      - 碰撞解算
   2. 运动学
      - 刚体运动学：根据牛顿三定律计算物体运动和位置的变化；推算几何体下一帧的位置；
   3. 场景管理
   4. 扫描
      - RayCast
      - Sweep
   5. 弹簧质点系统
      - 布料模拟
      - 流体模拟
   6. 破坏 Destruction
   7. RagDoll
   8. 载具
   9. PBD/XPBD (Position Based Dynamics)  
      - 流体模拟
   10. 
4. 

