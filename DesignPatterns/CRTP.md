"CRTP" (Curiously Recurring Template Pattern)，派生类作为基类的一个模板参数来继承基类的实现。

CRTP 的主要优点是，将编译时多态性 (compile-time polymorphism) 带入C++的静态类型系统。因此，CRTP 在运行时具有与虚拟函数相同的性能，同时将编译时处理类型的能力带入编译器。

CRTP 的实现基本上是一个类模板，它使用派生类本身作为基类模板参数，并将其最终导出类型作为返回类型的模板方法。CRTP 可以被用来使派生类继承某种基类的实现，同时又能为每个继承类提供一些特定的行为。

下面是一个C++版本的CRTP的最佳实践：

```

```

```c++
template<typename Derived> 
class Base {
public:
    void interface()
    {
        // 共同的或基础行为都在这里实现
        // ...
        static_cast<Derived*>(this)->implementation();
        // ...
        // 其他共同的或基础行为也在这里实现
        // ...
    }
};  

class Derived1 : public Base<Derived1> {
public:
    void implementation()
    {
        // 在这里实现类派生1 特定的行为
    }
};

class Derived2 : public Base<Derived2> {
public:
    void implementation()
    {
        // 在这里实现类派生2 特定的行为
    }
};
```



在该示例中，我们定义了一个名为 `Base` 的基类，使用单个模板参数 `Derived`。 `Base` 类中定义了一个名为 `interface` 的公共成员函数，该函数提供了共同的或基础行为。 `Derived` 派生类从该基类中继承了该函数，并定义了一个名为 `implementation` 的特殊函数，以提供自定义的功能。

通过使用 `Base<DerivedN>` 模板声明，每个 `Derived` 派生类都指定了自己作为一个类的基类。这使得每个 `Derived` 派生类都能够通过 `interface` 成员函数继承 `Base` 的实现。然后，每个 `Derived` 派生类都定义了其特定于类自身的行为，以及 `Base` 类中声明的共同的或基础行为。

使用CRTP的优点是可以在编译时处理类型，可以消除框架代码的运行时开销，并且有助于生成高效的代码以优化性能。CRTP还通过模板生成代码来增加代码生成的灵活性和可维护性，从而提高了代码的可扩展性。



