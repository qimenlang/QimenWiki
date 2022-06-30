// CPPBestPractice.cpp: 定义应用程序的入口点。
//
#include <iostream>
#include <memory>
#include "CPPBestPractice.h"

using namespace std;

void test_smart_pointer_copy()
{
	shared_ptr<int> a = make_shared<int>(42);
	shared_ptr<int> b = a;
	*b = 21;
	cout <<"shallow copy: " <<*a << endl;

	shared_ptr<int> c = make_shared<int>(*a);
	*c = 11;
	cout << "depth copy:" << *a << endl;
}

struct IObject {
    IObject() = default;
    IObject(IObject const&) = default;
    IObject& operator=(IObject const&) = default;
    virtual ~IObject() = default;

    virtual void eatFood() = 0;
    virtual shared_ptr<IObject> clone() const = 0;
};

template <class Derived, class Base = IObject>
struct IObjectClone : Base {
    virtual shared_ptr<IObject> clone() const override {
        Derived const* that = static_cast<Derived const*>(this);
        return make_shared<Derived>(*that);
    }
};

struct CatObject : IObjectClone<CatObject> {
    string m_catFood = "someFish";

    virtual void eatFood() override {
        cout << "eating " << m_catFood << endl;
        m_catFood = "fishBones";
    }

    virtual ~CatObject() override = default;
};

struct DogObject : IObjectClone<DogObject> {
    string m_dogFood = "someMeat";

    virtual void eatFood() override {
        cout << "eating " << m_dogFood << endl;
        m_dogFood = "meatBones";
    }

    virtual ~DogObject() override = default;
};

void eatTwice(IObject* obj) {
    shared_ptr<IObject> newObj = obj->clone();
    obj->eatFood();
    newObj->eatFood();
}

int main() {
    shared_ptr<CatObject> cat = make_shared<CatObject>();
    shared_ptr<DogObject> dog = make_shared<DogObject>();

    eatTwice(cat.get());
    eatTwice(dog.get());


    return 0;
}
