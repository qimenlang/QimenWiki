

### week 1

1. vivo-demo动画相关临时解决的问题列表
   - Object Attach Transform 设置
   - 材质默认透明问题
   - 支持8骨骼权重
   
2. 搭建动画测试场景
   - 包含多个动画示例，展示所有动画效果，且可以用于回归测试 
   - Animator  UI Pannel  DONE
   - 测试：复刻oculus 手势demo，测试混合空间
   - 测试展示动画混合、动画状态机效果
   
3. 动画系统代码移植
   - 动画混合：一维混合、二维混合、Mask混合、delauney 三角刨分  **DONE**
   - delauney算法在二维混合中效果不如 unity中的二维混合算法，调研unity 二维混合算法
     - https://answers.unity.com/questions/1206428/how-weights-of-2d-blending-are-calculated.html
     - https://blog.runevision.com/search/label/article
     - https://arrowinmyknee.com/2019/05/23/2d-blend-types-in-unity/
     - https://www.shadertoy.com/view/XlKXWR
   - 动画状态机、动画过渡
   - 动画参数设置:基于事件机制？？？
   
4. MorphTarget 表情动画

5. 内存泄漏排查总结

6. RUN单元测试

7. 第三方库引入，最佳实践
   - assimp
   
   - ozz-animation
   
   - 引入到external中
   
   - 在外部编译成功
   
   - 编译好的库，放在assimp/build/debug、release /android、linux/目录下
   
   - full build的时候才重新编译库文件，其他时候直接使用库文件
   
   - 动画效果错误排查 DONE
   
   - 链接 CurrentDirectory（）未定义 DONE
   
     
   
     
   
     

### Week2

1. Assimp 内存泄漏排查
   - android内存管理机制，只在堆的末尾的内存不用时，才能释放；
   - 堆上，大量分配了小块的内存
   - 使用长链接内存池解决？在调用assimp的时候，创建一个内存池，assimp处理模型的过程中，所有的内存从内存池获取，处理完模型，销毁内存池；
     - 问题1：内存池的创建销毁，时间空间的占用；
     - 问题2 :  内存池中如果也以链表结构开辟内存，是否也会导致android native heap上内存碎片的产生？所以内存池只能分配额大块连续内存？
     - 问题3 : 应该设计一个所有模块公用的内存池；
     - 答案：https://zhuanlan.zhihu.com/p/589406667  是产生的内存碎片，不用管；
   - 内存碎片问题总结
     - Assimp解析FBX文件过程的内存碎片问题：
       - TokenizeBinary过程，可以通过使用std::vector<token>直接存储对象，避免了在堆上多次动态分配内存, 从而避免了内存碎片；
       - Parser过程，该过程将1过程中的一维token数组处理成树状结构，每个节点都会包含数量不等的子节点，使用了std::multi_map，map在insert数据时会不可避免地在堆上new 小对象；
       - ConvertToAssimpScene过程，该过程将树状结构数据转换到aiScene，用到的所有相关数据结构都是通过new 创建对象，且过程相对复杂；
     - irisengine本身也存在内存碎片问题，测试创建10000个SceneObject后再释放，Pss增长了20M；
   - 解决方案：
     - 只解决模型加载过程产生的内存碎片问题
       - 调研其他无内存碎片问题的模型加载库，可以同时支持fbx/gltf，或者可以转换fbx到gltf，之后加载gltf到irisengine；
       - 重写assimp解析FBX文件源码，尽量避免动态内存分配；
     - 解决引擎本身的内存碎片问题及调用第三方库产生的内存碎片
       - 内存碎片整理及指针重定位，原理：将引擎中创建的所有智能指针加到一个链表里，通过冒泡的方式将内存碎片上浮到堆的高位地址，遍历智能指针链表并且更新对应的智能指针；该方式不能处理第三方库产生的内存碎片；
       - 使用内存池，在使用assimp读取文件时创建内存池，assimp处理fbx文件过程中在内存池上分配内存，处理fbx文件完毕，释放内存池；
         - 如何在不修改第三方库代码的情况下，让第三方库在创建好的内存池上分配内存？？
         - 内存池的线程安全问题
           - 给内存池加锁
           - 利用线程局部存储，可以让每个线程有自己的内存池
       - 现有的内存分配器：ptmalloc\tcmalloc\jemalloc
       - 操作符重载之后，对全局所有代码都产生影响？？

### Week3-Week4

1. 解决内存碎片问题
   - scudo实验
   - mimalloc调研
2. 动画系统原型设计
   - 动画事件
   - 状态机设计
   - IK手部测试
   - 混和树完善
3. 





 
