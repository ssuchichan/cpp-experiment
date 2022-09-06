# Operator Overload
## 通过操作符重载，引出friend关键字
```c++
#include <iostream>
using namespace std;

class Integer {
public:
    explicit Integer(int n): val(n) {}
    // 成员函数
    Integer operator*(int n) const {
        return Integer(val * n);
    }
    void print() const {
        cout << val << endl;
    }
private:
    int val;
};


int main() {
    Integer integer(10);
    Integer integer1 = integer * 2; // OK
    integer1.print();
    
    // Integer integer2 = 2 * integer1; // Error: no match for operator*
    
    return 0;
}
```
上述代码是以成员函数的方式重载，`*`左边是调用对象（`integer1`），右边是乘数。但是交换一下两个数的位置，编译器就报错了。错误原因在于：是以成员函数的
形式重载，但是乘数10（`int`）是原生类型，不是一个类，根本没有成员函数这种说法。
## 解决办法
不用成员函数的方式，用非成员函数的方式重载。
```c++
Integer operator*(const Integer& integer, int n) {
    return Integer(integer.val * n);
}
```
但是又产生新问题：非成员函数无法访问私有成员。上述代码中`integer.val`是无法通过编译的。
## friend
为了解决非成员函数重载操作符的问题，引入了`friend`关键字。`friend`可以修饰类和函数，是得这些类和函数可以访问所关联类的私有成员。
```c++
class Integer {
public:
    explicit Integer(int n):val(n){}
    // // 成员函数
    Integer operator*(int n) const {
        return Integer(val*n);
    }
    void print() const {
        cout << val << endl;
    }
    // 非成员函数
    friend Integer operator*(int n, const Integer& integer) {
        return Integer(integer.val * n);
    }
private:
    int val;
};
```
注意：
参数列表中的顺序，要保持一直。
```c++
integer * 2; // operator*(int n);
2 * integer; // operator*(int n, const Integer& integer);
```

