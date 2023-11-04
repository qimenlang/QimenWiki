### 动画开发指南

核心概念

1. Animator组件：对于有动画片段的fbx模型文件，在加载时，会自动增加Animator组件，用于提供动画加载、动画混合、动画状态机等功能；
2. 动画控制器：用于控制动画片段的播放；
3. *Skeleton组件：对于骨骼蒙皮动画的模型，其在加载时会自动增加Skeleton组件，Skeleton组件负责计算蒙皮矩阵，不对外提供功能接口；

用法说明：

1. 动画片段加载

   - fbx文件需要至少有一个动画片段；fbx模型被加载之后，sceneObject默认有一个animator组件；
   - animator组件调用loadAnimationClip接口加载其他fbx文件中的动画片段
   - 获取可用动画列表：getAvailableClipNames

   ```c++
       std::string IdleClip = std::string(iriseditor::Asset::rootDirectory()) + "/AnimationTest/mixmao/Idle.fbx";
       std::string WalkClip = std::string(iriseditor::Asset::rootDirectory()) + "/AnimationTest/mixmao/Walking.fbx";
       auto m_rigid = ModelLoader::load(IdleClip.c_str());
       m_rigid->setParent(scene);
       auto animator = m_rigid->getComponent<irisengine::Animator>();
       //加载指定fbx文件中的动画片段
   	animator->loadAnimationClip(WalkClip);
   	//获取可以播放的动画片段的名称
       auto ClipNames = animator->getAvailableClipNames();
   	//播放指定的动画片段
       animator->playAnimation(ClipNames[0]);
   ```

2. 动画控制器

   - 调用playAnimation接口，播放指定动画片段，并且返回动画控制器，动画片段的名称由"fbx文件名_动画片段名“组成；
   - 开始、暂停、恢复、设置速度、设置动画播放范围、是否循环、重置;
   
   ```c++
       std::string pistoPath = std::string(iriseditor::Asset::rootDirectory()) + "/AnimationTest/gun/pistola_low.fbx";
       auto pistoAnimator = pisto->getComponent<Animator>();
       auto pistoClipNames = pistoAnimator->getAvailableClipNames();
       auto playBackController = pistoAnimator->playAnimation(pistoClipNames[0]);
       auto playBackController = pistoAnimator->playAnimation("pistola_low_Take 001");
       if (playBackController) {
           //暂停
           playBackController->pause();
           //恢复
           playBackController->resume();
           //设置播放比例到50%位置，一般需要先暂停
           playBackController->setTimeRatio(0.5);
           //设置播放比例范围,只播放20%-80%的动画片段
           playBackController->setRatioRange(0.2,0.8);
           //设置播放速度，-1.0为倒播
           playBackController->setPlaybackSpeed(-1.0);
           //设置循环模式 
           playBackController->setLoop(false);
           //复位所有设置到默认设置
           playBackController->reset();
       }
   ```
   
3. 动画状态机

   - 动画状态:定义一个动画状态对应一个动画片段；
   - 过渡 : 定义从A状态接收到某事件之后，在设定的时间之内，过渡到B状态；过渡方式为冻结过渡，不支持平滑过渡；
   - 状态机初始默认状态为第0个状态，调用translateState接口进行状态转换；

   ```c++
       std::unordered_map<std::string, AnimationClip> animationClips = animator->animationClips();
   
       //定义4种事件
       enum EVENT { FORWARD, UP, BACK, EVENTCOUNT };
       //定义4个状态，每个状态对应一个动画片段
       AnimationState fastRun("FASTRUN", animationClips["Running_mixamo.com"]);
       AnimationState jump("JUMP", animationClips["Jump_mixamo.com"]);
       AnimationState slowRun("SLOWRUN", animationClips["SlowRun_mixamo.com"]);
       AnimationState idle("IDLE", animationClips["Idle_mixamo.com"]);
   
       //定义过渡
       AnimationTranslation idleToslowRun(idle, FORWARD, slowRun, 1.0);
       AnimationTranslation idleToJump(idle, UP, jump, 2.0);
       AnimationTranslation slowRunToFastRun(slowRun, FORWARD, fastRun, 2.0);
       AnimationTranslation slowRunToJump(slowRun, UP, jump, 2.0);
       AnimationTranslation slowRunToIdle(slowRun, BACK, idle, 2.0);
       AnimationTranslation fastRunToJump(fastRun, UP, jump, 2.0);
       AnimationTranslation fastRunToSlowRun(fastRun, BACK, slowRun, 1.0);
       AnimationTranslation jumpToSlowRun(jump, FORWARD, slowRun, 3.0);
   
       std::vector<AnimationState> states = {fastRun, jump, slowRun, idle};
       std::vector<AnimationTranslation> translations = {idleToslowRun, idleToJump,    slowRunToFastRun, slowRunToJump,
                                                         slowRunToIdle, fastRunToJump, fastRunToRise,    jumpToSlowRun};
   
       //初始化动画状态机,初始状态为状态0，即fastRun
       animator->initStateMachine(states, translations);
       
   	//从默认状态fastRun过渡到Jump状态
       animator->translateState(EVENT::UP);
   	//从Jump状态转换到slowRun状态
       animator->translateState(EVENT::FORWARD);
   ```

   

4. 动画混合:目前只支持动画片段的混合，不支持对混合的结果再次混合；

   - 一维混合：支持对两个及以上动画片段进行混合，动画片段默认平均分布在0-1的座标上；例如：创建3个clip的一维混合，则三个片段的座标分别为0.0、0.5、1.0；该一维座标与指定的动画参数绑定，可以通过设置动画参数数值，进而调整各个动画片段的权重，得到不同的一维混合效果；

   ```c++
       std::string runClip = std::string(iriseditor::Asset::rootDirectory()) + "/AnimationTest/mixmao/Running.fbx";
       std::string slowRunClip = std::string(iriseditor::Asset::rootDirectory()) + "/AnimationTest/mixmao/SlowRun.fbx";
       std::string fastRunClip = std::string(iriseditor::Asset::rootDirectory()) + "/AnimationTest/mixmao/FastRun.fbx";
       std::string IdleClip = std::string(iriseditor::Asset::rootDirectory()) + "/AnimationTest/mixmao/Idle.fbx";
       std::string WalkClip = std::string(iriseditor::Asset::rootDirectory()) + "/AnimationTest/mixmao/Walking.fbx";
       auto m_rigid = ModelLoader::load(IdleClip.c_str());
       m_rigid->setParent(scene);
   
       auto animator = m_rigid->getComponent<irisengine::Animator>();
       animator->loadAnimationClip(WalkClip);
       animator->loadAnimationClip(slowRunClip);
       animator->loadAnimationClip(runClip);
       animator->loadAnimationClip(fastRunClip);
   
       std::unordered_map<std::string, AnimationClip> animationClips = animator->animationClips();
   
       animator->addParameter("Flex");
   	//创建一维混合，3个clip所默认的一维座标分别是0.0,0.5,1.0
       animator->createBlend1D("Blend1d",{animationClips["Walking_mixamo.com"],animationClips["SlowRun_mixamo.com"],animationClips["Running_mixamo.com"]},"Flex");
   
   	//调整动画参数,Flex = 0.5, 3个clip的权重分别为 0，1，0
       animator->setFloat("Flex", 0.5);
   	
   	//调整动画参数,Flex = 0.6, 3个clip的权重分别为 0，0.8，0.2
       animator->setFloat("Flex", 0.6);
   
   ```
   
   - 二维混合：支持在二维平面上对多个动画片段进行混合，每个动画片段可以设置二维座标；每个维度对应一个动画参数；通过设置两个动画参数的数值，调整动画片段权重，得不同的二维混合效果；
   
   ```c++
       animator->loadAnimationClip(Capture_R);
       animator->loadAnimationClip(First_R);
       animator->loadAnimationClip(Half_First_R);
       animator->loadAnimationClip(Pinch_R);
       animator->loadAnimationClip(Point_R);
       animator->loadAnimationClip(Three_Qutar_First_R);
       animator->loadAnimationClip(Thumb_Up_R);
       
       std::unordered_map<std::string, AnimationClip> animationClips = animator->animationClips();
   
       // 创建2维混合
       std::vector<Blend2dNode> blend2dNodes;
       blend2dNodes.push_back({{0.0, 0.0}, animationClips["Capture_R_Take 001"]});             // Capture_R
       blend2dNodes.push_back({{0.0, 0.835}, animationClips["Pinch_R_Take 001"]});             // Pinch_R
       blend2dNodes.push_back({{0.0, 1.0}, animationClips["Pinch_R_Take 001"]});               // Pinch_R
       blend2dNodes.push_back({{0.5, 0.0}, animationClips["Half_First_R_Take 001"]});          // Half_First_R
       blend2dNodes.push_back({{0.5, 1.0}, animationClips["Half_First_R_Take 001"]});          // Half_First_R
       blend2dNodes.push_back({{0.835, 0.0}, animationClips["Three_Qutar_First_R_Take 001"]}); // Three_Qutar_First_R
       blend2dNodes.push_back({{0.835, 1.0}, animationClips["Three_Qutar_First_R_Take 001"]}); // Three_Qutar_First_R
       blend2dNodes.push_back({{1.0, 0.0}, animationClips["First_R_Take 001"]});               // First_R
       blend2dNodes.push_back({{1.0, 1.0}, animationClips["First_R_Take 001"]});               // First_R
   
       animator->addParameter("Flex");
       animator->addParameter("Pinch");
       animator->createBlend2D("blend2d", blend2dNodes, "Flex", "Pinch");
   
       //调整动画参数，两个动画参数组成一个二维座标点，对该二维座标点所在的三角形的三个顶点对应的三个动画片段进行混合
       animator->setFloat("Flex", 0.0);
       animator->setFloat("Pinch", 0.0);
   
   ```
   
   以上代码创建的二维混合对应unity中的二维混合如下：



   ![](blend2d.png)

   
