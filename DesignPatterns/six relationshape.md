1. 依赖

2. 关联

3. 聚合：分散的部分聚合到一起，整体和部分的关系，可以分离

   ```c
   // Whole (one-sided one to many relationship)
   public class Main{
   
       //The associated part is initialized only when it is used, indicating that it can be separated
       private A a;
       private B b;
       
       public void setA(A a){
           this.a = a;
       }
       
       public void setB(B b){
           this.b = b;
       }
   
   }
   // part
   class A{
   
   }
   // part
   class B{
   
   }
   ```

   

4. 组合:也是整体和部分的关系，但是不可分离，整体在被初始化的时候，部分也被初始化；

   ```c
   // whole
   public class Main{
   
       //The combination relationship is inseparable. When the whole is initialized, the part is also initialized, indicating that the whole cannot be separated from the part
       private A a = new A();
       private B b = new B();
   
   }
   // part
   class A{
   
   }
   // part
   class B{
   
   }
   ```

   





1. 实现
2. 继承

reference：

https://blog.csdn.net/zhy1379/article/details/123313897

https://programs.wiki/wiki/six-relationships-between-design-pattern-classes.html

