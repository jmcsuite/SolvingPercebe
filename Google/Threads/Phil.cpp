#include <bits/stdc++.h>
using namespace std;

const int maxn = 10;
std::mutex gabel[maxn];

void philosopher(const int t_id, int N) {
    int l1_id = t_id; 
    int l2_id = (t_id + 1) % N;
    if (l2_id < l1_id) swap(l2_id, l1_id);

    const std::lock_guard l1(gabel[l1_id]);
    {
        const std::lock_guard l2(gabel[l2_id]);
        cout << "eating: " << t_id << '\n';
    }
}

int main (int argc, char *argv[]) {
    if (argc != 2) {
        cout << "Usage ./Phil n_threads\n";
        return 0;
    }

    int N = stoi(argv[1]);
    if (N > maxn) {
        cout << "Can't spawn more than " << maxn << "threads\n";
        return 0;
    }

    if (N < 2) {
        cout << "You need at least 2 Philosophers\n";
        return 0;
    }

    vector<thread> threads;
    for (int i = 0; i < N; i++) {
        threads.emplace_back(philosopher, i, N);
    }
    for (auto& t : threads) t.join();
}
