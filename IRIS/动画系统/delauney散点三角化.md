1. 构建超级三角形，包含所有散点：取所有散点的x,y极值，得到4个点组成的矩形，使用矩形的外接圆作为超级三角形的内接圆，生成超级三角形；

   ![](/home/lijiaxiang/WorkSpace/repos/QimenWiki/IRIS/images/delauney_1.jpg)

2. 加入一个新节点，找出所有外接圆包含新加入节点的三角形，并删除，将被删除的三角形的点与新节点相连，形成新的三角形网格；

   ![](/home/lijiaxiang/WorkSpace/repos/QimenWiki/IRIS/images/delauney_2.jpg)

   ![](/home/lijiaxiang/WorkSpace/repos/QimenWiki/IRIS/images/delauney_3.jpg)

   ![](/home/lijiaxiang/WorkSpace/repos/QimenWiki/IRIS/images/delauney_4.jpg)

3. 不断重复步骤2，直到所有节点全部加入；

4. 最后删除包含三角形顶点的三角形？？？