#include <bits/stdc++.h>
using namespace std;

class Foo {
    public:
        Foo() : f_counter(0) {}
        void f1() {
            cout << "Function 1 \n";
            int expected = 0;
            f_counter.compare_exchange_strong(expected, 1);
        }

        void f2(int n_retry) {
            for (; n_retry >= 0; n_retry--) {
                if (f_counter.load() >= 1) {
                    cout << "Function 2 \n";
                    f_counter.store(2);
                    break;
                }
            }
        }

        void f3(int n_retry) {
            for(; n_retry >= 0; n_retry--) {
                int cc = f_counter.load();
                if (cc == 2) {
                    cout << "Function 3\n";
                    return;
                }
            }
        }

    private:
        atomic_int f_counter;
};

void f1(Foo* foo) {
    foo->f1();
}

void f2 (Foo* foo) {
    foo->f2(INT_MAX);
}

void f3 (Foo* foo) {
    foo->f3(INT_MAX);
}

int main () {
    Foo foo;
    thread t3(f3, &foo);
    thread t2(f2, &foo);
    thread t1(f1, &foo);
    t3.join();
    t2.join();
    t1.join();
}
