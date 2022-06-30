### CPP特性

1. 基类的虚析构函数

   如果基类的析构函数不是虚函数，则用一个基类的指针指向了子类的对象，在delete该指针时，只调用了基类的析构函数，没有调用子类的析构函数，会导致该对象的子类部分内存不被释放；基类的析构函数加上virtual之后，析构函数的调用同样使用了多态规则；

2. default/delete/noexcept修饰符 

   - default :在函数末尾加上”= default”来显式地指示编译器去生成该函数的默认版本。
   - delete : 显式删除修饰的函数，可能修饰编译器默认给类编译的六个成员函数；
   - noexcept: **编译期**完成声明和检查工作.`noexcept` 主要是解决的问题是**减少运行时开销**. 运行时开销指的是, 编译器需要为代码生成一些额外的代码用来包裹原始代码，当出现异常时可以抛出一些相关的堆栈`stack unwinding`错误信息, 这里面包含，错误位置, 错误原因, 调用顺序和层级路径等信息.当使用`noexcept`声明一个函数不会抛出异常候, 编译器就不会去生成这些额外的代码, 直接的减小的生成文件的大小, 间接的优化了程序运行效率.

3. 类中的友元 friend有什么用？B是A的友元类，B可以直接访问A类对象的private 成员；破坏了封装；

   ```c++
   #include <iostream>
   class A {
   private:
   	int a;
   
   public:
   	A() { a = 0; }
   	friend class B; // Friend Class
   };
   
   class B {
   private:
   	int b;
   
   public:
   	void showA(A& x)
   	{
   		// Since B is friend of A, it can access
   		// private members of A
   		std::cout << "A::a=" << x.a;
   	}
   };
   
   int main()
   {
   	A a;
   	B b;
   	b.showA(a);
   	return 0;
   }
   
   ```

   

   - 

4. 

