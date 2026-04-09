1. Spark 负责模拟，OSG负责渲染
   - 关闭Spark Renderer
   - 每帧获取粒子数据
   - 数据映射到OSG Geometry
     - 每帧从CPU更新VBO
     - instancing
2. 
   - 