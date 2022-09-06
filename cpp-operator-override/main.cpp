#include <iostream>
using namespace std;

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


int main() {
    Integer integer(10);
    Integer integer1 = integer * 2;
    integer1.print();
    // Error: no match for operator*
    // Integer integer2 = 2 * integer1;
    return 0;
}
