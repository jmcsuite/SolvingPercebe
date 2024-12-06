#include <bits/stdc++.h>
using namespace std;

atomic_int cc; 

void Fizz(int n) {
    while (1) {
        int current = cc.load(memory_order_seq_cst);
        if (current > n) return;
        if (current % 5 == 0) continue;
        if (current % 3 != 0) continue;
        cout << "Fizz\n";
        cc.store(++current);
    }
}

void FizzBuzz(int n) {
    while (1) {
        int current = cc.load(memory_order_seq_cst);
        if (current > n) return;
        if (current % 5 != 0) continue;
        if (current % 3 != 0) continue;
        cout << "FizzBuzz\n";
        cc.store(++current);
    }
}

void Buzz(int n) {
    while (1) {
        int current = cc.load(memory_order_seq_cst);
        if (current > n) return;
        if (current % 5 != 0) continue;
        if (current % 3 == 0) continue;
        cout << "Buzz\n";
        cc.store(++current);
    }
}

void Nums(int n) {
    while (1) {
        int current = cc.load(memory_order_seq_cst);
        if (current > n) return;
        if (current % 5 == 0) continue;
        if (current % 3 == 0) continue;
        cout << current << '\n';
        cc.store(++current);
    }
}

int main (int argc, char *argv[]) {

    if (argc != 2) {
        cout << "Usage ./Fizz maxnn\n";
        return 0;
    }
    int N = stoi(argv[1]);

    cc.store(1, memory_order_seq_cst);
    thread t1(Nums, N);
    thread t2(Fizz, N);
    thread t3(Buzz, N);
    thread t4(FizzBuzz, N);

    t1.join(); t2.join(); t3.join(); t4.join();
}
