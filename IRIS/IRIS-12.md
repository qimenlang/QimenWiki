1. Avatar Animation DONE
   - 动画无法播放
     - 骨骼结构可能不一致  DONE
   - 武器 Attach DONE
   - Avatar 及武器材质渲染不正确
   - 表情
   - 动画播放控制
   - 手机demo



### week 4

1. BUG
   - Object Attach Transform 设置
   - VR设备模型被切面 DONE
   - 手柄模型切换动画部分mesh消失 DONE
     - 原因：动画切换时，某一个node 在第一个clip中是动的，在第二个clip中是静止的，node在第二个clip中就会静止在切换时的位置；
     - 解决：给静止node填充骨骼rest pose数据； 
   - 材质默认透明问题
2. 搭建动画测试场景，包含多个动画示例，展示所有动画效果；
3. 动画系统代码移植
4. MorphTarget 表情动画