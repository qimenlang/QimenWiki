### 动画系统进展 8.12

1. 集成ozz-animation,打通动画pipeline  DONE
2. 动画状态机 （预期7.29）
   - 接受手柄输入，切换不同状态对应的动画 PEND
   - 动画切换时实现平滑过渡  DONE
   - 使用配置文件的形式，配置状态机的动画状态、clip、混合参数等，以便快速迭代 PEND
3. 动画混合空间 
   - 动画片段采样 DONE
   - 一维混合 DONE
   - 二维混合 DONE
   - Mask混合 DONE
   - 加法混合 DONE
   - 混合树  待重新实现
4. 动画控制  DONE
   - 暂停、恢复、循环模式设置
5. 动画资源管理   需重构
6. 





 LOGI("LJX Initilizing Skeleton Mesh Object");

​        m_anim_resources.LoadAnimation("/sdcard/iris/Idle.fbx");

​        m_anim_resources.LoadAnimation("/sdcard/iris/Walk.fbx");

​        // m_anim_resources.LoadAnimation("/sdcard/iris/SlowRun.fbx");

​        m_anim_resources.LoadAnimation("/sdcard/iris/Running.fbx");

​        // m_anim_resources.LoadAnimation("/sdcard/iris/FastRun.fbx");



​        m_anim_resources.LoadAnimation("/sdcard/iris/HandRaising.fbx");

​        // m_anim_resources.LoadAnimation("/sdcard/iris/FemaleStandingPose.fbx");



​        // m_anim_resources.LoadAnimation("/sdcard/iris/Jump.fbx");



​        // m_anim_resources.LoadAnimation("/sdcard/iris/FemaleStandingPose.fbx");

​        // m_anim_resources.LoadAnimation("/sdcard/iris/FemaleStandingPose2.fbx");



​        // m_anim_resources.LoadAnimation("/sdcard/iris/BreathingIdle.fbx");

​        // m_anim_resources.LoadAnimation("/sdcard/iris/LeftStrafeWalk.fbx");

​        // m_anim_resources.LoadAnimation("/sdcard/iris/LeftStrafeWalking.fbx");

​        // m_anim_resources.LoadAnimation("/sdcard/iris/RightStrafeWalk.fbx");

​        // m_anim_resources.LoadAnimation("/sdcard/iris/ShakingHeadNo.fbx");



​        ozz::animation::offline::SkeletonBuilder skeleton_builder;

​        m_skeleton = skeleton_builder(m_anim_resources.GetRawSkeletonData());

​        m_pose = ozz::make_unique<Pose>(m_skeleton.get());



​        AnimationRes clip_res;

​        clip_res.anim_type = AnimationType::Clip;

​        clip_res.anim_name = "IDLE_CLIP";

​        clip_res.clips.push_back(m_anim_resources.GetRawAnimation(0));

​        AddAnimation(clip_res);



​        AnimationRes blend_1d_res;

​        blend_1d_res.anim_type = AnimationType::Blend1D;

​        blend_1d_res.anim_name = "blend_1d";

​        blend_1d_res.clips.push_back(m_anim_resources.GetRawAnimation(1));

​        blend_1d_res.clips.push_back(m_anim_resources.GetRawAnimation(2));

​        AddAnimation(blend_1d_res);



​        AnimationRes blend_mask_res;

​        blend_mask_res.anim_type = AnimationType::MaskBlend;

​        blend_mask_res.anim_name = "blend_mask";

​        blend_mask_res.clips.push_back(m_anim_resources.GetRawAnimation(1));

​        blend_mask_res.clips.push_back(m_anim_resources.GetRawAnimation(3));

​        AddAnimation(blend_mask_res);



​        // animtion state map

​        std::map<std::string, int> sm;

​        sm.insert({clip_res.anim_name, sm.size()});

​        sm.insert({blend_1d_res.anim_name, sm.size()});

​        sm.insert({blend_mask_res.anim_name, sm.size()});



​        std::vector<std::vector<int>>

​            transtab = {

​                /* CLIP  1D  MASK */

​                {sm["IDLE_CLIP"], sm["IDLE_CLIP"], sm["IDLE_CLIP"]},   /* On CLIP */

​                {sm["blend_1d"], sm["blend_1d"], sm["blend_1d"]},      /*On 1D*/

​                {sm["blend_mask"], sm["blend_mask"], sm["blend_mask"]} /* On MASK*/

​            };

​        //m_animation_fsm.SetTransTable(transtab, sm);