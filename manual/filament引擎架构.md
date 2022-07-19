1. 可扩展渲染管线（Frame Graph）
   - 定义
   - 三个阶段
     - Setup ： 用户自定义资源阶段，创建虚拟资源，设置其使用方式等；
     - Compile ： 根据Setup的虚拟资源和各个PassNode之间的引用关系，剔除无引用的虚拟资源；
     - Execute ： FrameGraph根据用户定义的虚拟资源引用关系生成真正的GPU Handle；执行用户自定义的渲染流程；
   - 在引擎编译之前的setup阶段，设置好渲染管线frame graph的配置；
2. 骨骼动画相关代码走读
   - 蒙皮权重：cgltf_attribute_type_weights  BONE_WEIGHTS
   - 
3. 

