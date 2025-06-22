存在三个交互对象：board1(collider尺寸{0.001,0,001})、volume、board2(尺寸{0.648,0.54});

- 近场检测结果：volume、board2;{board1因尺寸太小，未被加入检测结果列表，volume是最佳检测结果，导致事件最终未在board1,board2上触发，取消按钮无响应；}
- 射线检测结果：borad1、volume、board2;
- 眼动检测结果：board1、volume、board2;



1. 问题1：borad1的尺寸非常小，为什么射线能稳定检测到？麻烦 @ZhenXie 看一下； @searingarrows 

2. 问题2: board1的作用是什么，为什么尺寸设置这么小；麻烦 @zhangming 与vivo沟通一下；


该issue与volume组件增加了pokeable有关：https://git.iris-view.com/project/vivo-2401-bug/-/issues/3435#note_489929；在volume组件增加pokeable之前，近场只能检测到board2,可以正常触发取消事件; 


解决方案：由应用侧设置各fusionUI组件的BlendOrder，保证board优先于volume, 优先级：board2>borad1>Volume;  麻烦 @fangqiang @ludengxian 看下该方案是否可行； @ytyue FYI


```c++
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: Pokeable m_quadSurface: {1.000000,1.000000} , localQuadSurface: {1.000000,1.000000}
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: Pokeable localPosition: vec3(-0.141477, -0.127604, -43.504150) , projectPosition: vec3(-0.141477, -0.127604, 0.500000)
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: PokeDetector::detect result:{VolumeRoot,0x6fc3614350}
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: PokeDetector::detect result f:0,o:-0.124041,d:-0.002714, pokeResults:0, preResults:0, device : RightGestureDevice
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: PokeDetector::detect Enter
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: Pokeable m_quadSurface: {0.001000,0.001000} , localQuadSurface: {0.001000,0.001000}
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: Pokeable localPosition: vec3(-0.091677, -0.068906, -0.005350) , projectPosition: vec3(-0.091677, -0.068906, 0.000000)
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: PokeDetector::detect result:{Board,0x6fc3428cd0}
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: PokeDetector::detect result f:0,o:0.056241,d:-0.003300, pokeResults:1, preResults:0, device : RightGestureDevice
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: PokeDetector::detect Exit
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: Pokeable m_quadSurface: {0.648000,0.540000} , localQuadSurface: {0.648000,0.540000}
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: Pokeable localPosition: vec3(-0.091677, -0.068906, 0.034650) , projectPosition: vec3(-0.091677, -0.068906, 0.000000)
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: PokeDetector::detect result:{Board,0x6fc3611790}
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: PokeDetector::detect result f:1,o:-0.124041,d:0.021373, pokeResults:1, preResults:0, device : RightGestureDevice
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: PokeDetector::detect Enter
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: PokeDetector::detect pokeResults : 2
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: PokeDetector::detect result VolumeRoot, isfront : 0, depth  -0.002714
05-13 11:56:36.256  9326 10224 I [IrisXR][Internal][UI]: PokeDetector::detect result Board, isfront : 1, depth  0.021373
```