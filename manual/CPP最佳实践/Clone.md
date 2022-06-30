#### Clone函数：实现拷贝构造的多态

C++的构造函数不能是虚的，因为虚函数表是在构造函数中指定的；

可以实现一个clone虚函数，子类分别实现对本类对象的深拷贝；



```c++
struct IObject {
    IObject() = default;
    IObject(IObject const &) = default;
    IObject &operator=(IObject const &) = default;
    virtual ~IObject() = default;

    virtual void eatFood() = 0;
    virtual shared_ptr<IObject> clone() const = 0;
};

struct CatObject : IObject {
    string m_catFood = "someFish";

    virtual void eatFood() override {
        cout << "eating " << m_catFood << endl;
        m_catFood = "fishBones";
    }

    virtual shared_ptr<IObject> clone() const override {
        return make_shared<CatObject>(*this);
    }

    virtual ~CatObject() override = default;
};
```



#### 批量生成clone函数

1. 使用宏的方式批量生成clone函数

   ```c++
   struct IObject {
       IObject() = default;
       IObject(IObject const&) = default;
       IObject& operator=(IObject const&) = default;
       virtual ~IObject() = default;
   
       virtual void eatFood() = 0;
       virtual shared_ptr<IObject> clone() const = 0;
   };
   
   //IOBJECT_DEFINE_CLONE  宏的本质是文本替换
   //宏的缺点是全局可见，可能会与其他库、文件中定义的同名的宏冲突
   //decay_t<decltype(*this)> 获取了this指针指向对象的类型
   
   #define IOBJECT_DEFINE_CLONE \
       virtual shared_ptr<IObject> clone() const override { \
           return make_shared<decay_t<decltype(*this)>>(*this); \
       }
   
   struct CatObject : IObject {
       string m_catFood = "someFish";
   
       IOBJECT_DEFINE_CLONE
   
       virtual void eatFood() override {
           cout << "eating " << m_catFood << endl;
           m_catFood = "fishBones";
       }
   
       virtual ~CatObject() override = default;
   };
   ```

   

2. 定义IObjectClone模板类接口

```c++
struct IObject {
    IObject() = default;
    IObject(IObject const &) = default;
    IObject &operator=(IObject const &) = default;
    virtual ~IObject() = default;

    virtual void eatFood() = 0;
    virtual shared_ptr<IObject> clone() const = 0;
};

//模板类接口，实现clone方法
template <class Derived, class Base = IObject>
struct IObjectClone : Base {
    virtual shared_ptr<IObject> clone() const override {
        //this 指针是 IObjectClone const* 型，也需要转化成Derived const *
        Derived const *that = static_cast<Derived const *>(this);
        return make_shared<Derived>(*that);
    }
};

//
struct CatObject : IObjectClone<CatObject> {
    string m_catFood = "someFish";

    virtual void eatFood() override {
        cout << "eating " << m_catFood << endl;
        m_catFood = "fishBones";
    }

    virtual ~CatObject() override = default;
};
```

1. 奇异递归模板模式(Curiously Recurring Template Pattern  CRTP)
   - 形如：`struct Derived:Base<Derived>{}`,基类模板参数是派生类，包含派生类是为了**在基类中能调用派生类的某些函数**；
   - CRTP主要用于**在基类调用一些子类的无法定义为虚函数的函数，比如拷贝构造，拷贝赋值**