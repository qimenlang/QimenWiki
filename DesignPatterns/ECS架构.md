# ECS架构

1. 概述

   - ECS(Entity-Component-System 实体-组件-系统)，遵循组合优于继承原则；

   - 每一个基本单元都是一个实体，每个实体由一个或多个组件构成，每个组件仅包含代表其特性的数据；

   - 实体与组件是一对多的关系，可以动态的增加或者删除组件；

   - 系统用于处理相同组件的数据；

     <img src="https://pic1.zhimg.com/80/v2-04e15b14964c9b61bffdfad42e907ffc_720w.jpg" alt="img" style="zoom: 67%;" />

     ![img](https://pic3.zhimg.com/80/v2-5ba6b2aec06fc6eebbb5baeaf343a586_720w.jpg)

2. 实体

   - 游戏世界中的独特物体，用一个ID标记，所有该实体的组件都会被其ID标记；

3. 组件

   - 是数据的集合，没有方法，只有数据用于存储状态，可以用struct实现；
   - 经典的实现方法是：所有组件继承自一个共同的基类；
   - 单例组件：整个世界中有且只有一个实体拥有组件；例如：输入组件；

4. 系统

   - 系统是处理游戏逻辑的部分，一个系统就是对组件进行操作的工具，只有行为没有状态；
   - UtilityFunction(实用函数)：多个系统需要运行同一个逻辑，将该公用的逻辑放在UtilityFunction中；

5. https://zhuanlan.zhihu.com/p/106946506   未读完