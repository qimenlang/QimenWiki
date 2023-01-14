11-12月OKR

- O1 :  解决irisengine阴影效果不正确问题 ; （对应组内O3,KR1）
- O2 : 完善动画库，支持混合空间，支持morphtarget ;  （对应组内O3,KR6）
- O3 : 接入虚拟手，动画库支持虚拟手自然混合 ; （对应组内O5,KR6）





1. 混合空间模块代码移植 [dead line 11.1]
   - 动画资源管理器  DONE
     - 骨骼、动画资源管理 map<string_hash,resource>;
     - 获取骨骼可用的动画列表 ， 可用的定义：animation track在骨骼中都能找到；
     - 动画fbx资源标准：一个FBX只包含一个动画clip，方便直接使用fbx文件路径指代动画clip，在目前的动画资源管理器中，动画clip资源放在cache中，不方便使用；
   - 左手模型不能正常显示
   - 混合空间接口
   - delaunay算法实现
   - 使用事件设置参数
   - animator组件剥离，骨骼数据由Node树拼凑
   - 静态Node优化，加入到ozz解算中；

2. 万有引力需求  
   1. 约束动画
      - 路径约束  [需要增加曲线功能]
      - 注视约束
      - 限时约束
   2. CAT 骨骼动画支持

3. Morph target动画

4. 阴影显示不正确问题

   1. rendermanager  windowmanager  irisengine : renderable
   2. asw
   3. multiview：阴影正确显示过
   4. matc:只要把我们的mat材质放到filament demo中，效果正确，就说明材质没问题；
   5. 阴影在IBL时从来不显示，在无IBL时偶尔显示；计算错误；
   6. 怎么看shadow map ： 抓帧
   7. 比较深度时，一直返回等于？导致没有阴影？：shadow map是纯黑的；
   8. 走通filament渲染管线,三个开关对渲染管线的影响；
   9. irisengine渲染管线
   
5. 



