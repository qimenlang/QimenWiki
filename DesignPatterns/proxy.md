# Proxy

- Provide a surrogate or placeholder for another object to control access to it. 

  ![proxy_diagram](https://www.bogotobogo.com/DesignPatterns/images/proxy/proxy_diagram.gif)

- A Proxy pattern is useful to modify the behavior of the **RealSubject** class while still preserving its interface. 

```c++
#include <iostream>

using namespace std; 

class Subject 
{
public:
	virtual void request() = 0;
	virtual ~Subject() {}
};
 
class RealSubject : public Subject 
{
public:
	void request() { 
		cout << "RealSubject.request()" << endl; 
	}
};
 
class Proxy : public Subject 
{
private:
	Subject* realSubject;
public:
	Proxy() : realSubject (new RealSubject()) 
	{}
	~Proxy() { 
		delete realSubject; 
	}
	// Forward calls to the RealSubject:
	void request() { 
		realSubject->request(); 
	}
};
 
int main() {
	Proxy p;
	p.request();
}
```

