# OSG学习总结

### 一、OSG核心概念

| OSG术语                 | 其他引擎概念             | 核心作用                                                     |
| ----------------------- | ------------------------ | ------------------------------------------------------------ |
| osg::Node（节点）       | GameObject               | 场景图的基石，所有可以放入场景图的东西都是node；子节点可继承父节点属性； |
| osg::Group（组节点）    | 父节点、容器             | 一种特殊的Node,可以拥有多个子节点。是构建场景层次的主要工具； |
| osg::Geode(几何节点)    | 带有MeshRenderer的Object | 继承自group，但只可挂载**可绘制体 Drawable**                 |
| osg::Drawable(可绘制体) | Mesh组件                 | 包含用于渲染的几何数据，类似组件，继承自node,被Geode持有；   |
| osg::stateSet(状态集)   | Material / 渲染属性      | 附着在Node或*Drawable*上，定义渲染状态，定义材质纹理着色器等； |

### 二、OSG各概念之间关系梳理

1. 场景图（Scene Graph）:由osg::node构成的树
   - 优点：
     - 从属关系：树状结构自然表达物体之间的从属关系
     - 状态继承：子节点可以继承父节点的渲染状态等；
     - 高效剔除：高效遍历树状结构，判断整颗子树是否需要剔除；
     - 细节层次：根据距离自动判断、切换物体各LOD;
2. 节点（Node）:场景图中所有元素的基类，提供遍历的入口；
   - 最重要的两个派生类：
     - osg::group : 容器节点
     - osg::geode ：可以持有osg::drawable的几何体叶子结点
3. 可绘制体（Drawbable）
   - 真正包含可绘制几何信息的对象
   - 本身不是Node，只可被附着到osg::geode

### 三、OSG核心优势

1. 适合静态场景的渲染；

2. node继承架构带来的Node自带BVH场景剔除以及LOD管理；

3. 动态分页调度（Paged LOD）：是OSG处理**超大规模场景**（如全球地形）的核心机制，解决了100GB的地形数据，在8GB内存的机器上流畅浏览。

   ```c++
   osg::ref_ptr<osg::PagedLOD> terrainTile = new osg::PagedLOD();
   terrainTile->setFileName(0, "high_detail.osgb");      // 立即加载
   terrainTile->setFileName(1, "medium_detail.ive");     // 需要时异步加载
   terrainTile->setRange(0, 0, 10000);                   // 高细节范围
   terrainTile->setRange(1, 10000, 50000);               // 中等细节范围
   // OSG的DatabasePager在后台线程：
   // 1. 预测摄像机移动
   // 2. 预加载即将可见的瓦片
   // 3. 卸载远离的瓦片
   ```


### 四、渲染机制

1. 深度测试默认关闭、深度写入默认打开、深度缓冲默认全为最远值1；
2. 
3. 

