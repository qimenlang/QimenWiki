

**2023 8/9双月OKR**

- O1 : 在高通 AR 眼镜设备上，完成系统基础手势交互的实现。目标用于8月高通演示 Demo  [O1-KR1]
  - KR1：直接交互相关bug跟进，交互成功率95%以上；
  - KR2 : 间接交互测试、合入 ；
  - KR3 : 手势模型材质达到美术要求； 
- O2 : 支持多人场景使用手交互效果，保证关节点的显示。目标用于8月高通演示 Demo  [O1-KR2]
  - KR1 : 多人场景手势直接交互、间接交互
  - KR2 : 多人场景手势关节点显示
- O3 : 动画系统功能迭代，对标RealityKit，优先满足vivo需求 [O1-KR6]



手势BUG

1. 更换透明材质
   - 半透明材质的自交叠问题

   - 描边效果

2. 去掉交互drag延迟，使用hold事件

   - 棋子不能复位问题 ：hold事件处理本身存在问题：会收到两次轴事件更新，第一次时，检测不到射线结果，会再第二次收到时检测到射线结果，最终真正invoke hold事件；有的时候，只收到一次轴事件，就不会invoke事件，导致棋子粘在手上；正确的过程应该是只收到一次轴事件更新，并且直接invoke事件；**DONE**
3. 手势识别不稳导致的体验问题

   - 手戳姿势识别不稳，手抖动幅度大
   - 拿高棋子，识别到手另一面
   - 三指捏合时，pinch交互成功率不高 
4. 重置座标系之后，无法手势直接交互  **DONE** 
5. interactor架构代码重构：手柄模拟手、识别手通用各个interactor 
6. 远程交互测试合并 **DONE** 
   - pinch成功率低
   - 先触发hold事件，再移动设备pose，导致棋子位置不对。

7. 对现有应用进行测试
   - 输入法

8. 
