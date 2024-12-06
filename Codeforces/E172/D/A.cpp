#include <bits/stdc++.h>
#define left lll
#define right rrr
using namespace std;
const int N = 2e5 + 5;
int n, ansL[N], ansR[N], ST[8 * N], resL[N], resR[N];
struct Data {
    int L, R, id;
} a[N];
bool cmp1(Data A, Data B) {
    return A.R > B.R || (A.R == B.R && A.L < B.L);
}
bool cmp2(Data A, Data B) {
    return A.L < B.L || (A.L == B.L && A.R > B.R);
}
void update(int id, int l, int r, int pos) {
    if (pos < l || pos > r) return;
    if (l == r) {
        ST[id] = 1;
        return;
    }
    int mid = (l + r) / 2;
    update(id * 2, l, mid, pos);
    update(id * 2 + 1, mid + 1, r, pos);
    ST[id] = ST[id * 2] + ST[id * 2 + 1];
}
int get(int id, int l, int r, int u, int v) {
    if (v < l || u > r) return 0;
    if (u <= l && v >= r) return ST[id];
    int mid = (l + r) / 2;
    return get(id * 2, l, mid, u, v) + get(id * 2 + 1, mid + 1, r, u, v);
}
int calc1(int l, int r) {
    int pos = r;
    if (get(1, 1, 2 * n, l, r) == 0) return 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (get(1, 1, 2 * n, mid, pos) >= 1) l = mid + 1;
        else r = mid - 1;
    }
    return l - 1;
}
int calc2(int l, int r) {
    int pos = l;
    if (get(1, 1, 2 * n, l, r) == 0) return 0;
    while (l <= r) {
        int mid = (l + r) / 2;
        if (get(1, 1, 2 * n, pos, mid) >= 1) r = mid - 1;
        else l = mid + 1;
    }
    return r + 1;
}

void Solve() {
    cin >> n;
    fill(ST, ST + 8 * n + 1, 0);
    vector<int> trace;
    trace.push_back(-1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i].L >> a[i].R;
        trace.push_back(a[i].L);
        trace.push_back(a[i].R);
        a[i].id = i;
    }
    sort(trace.begin(), trace.end());
    for (int i = 1; i <= n; i++) {
        a[i].L = lower_bound(trace.begin(), trace.end(), a[i].L) - trace.begin();
        a[i].R = lower_bound(trace.begin(), trace.end(), a[i].R) - trace.begin();
    }
    sort(a + 1, a + n + 1, cmp1);
    for (int i = 1; i <= n; i++) {
        int left = a[i].L, right = a[i].R;
        if (i < n && a[i].L == a[i + 1].L && a[i].R == a[i + 1].R) ansL[a[i].id] = 0;
        else ansL[a[i].id] = calc1(1, left);
        update(1, 1, 2 * n, left);
    }

    fill(ST, ST + 8 * n + 1, 0);
    sort(a + 1, a + n + 1, cmp2);
    for (int i = 1; i <= n; i++) {
        int left = a[i].L, right = a[i].R;
        if (i < n && a[i].L == a[i + 1].L && a[i].R == a[i + 1].R) ansL[a[i].id] = 0;
        else ansR[a[i].id] = calc2(right, 2 * n);
        update(1, 1, 2 * n, right);
    }
    for (int i = 1; i <= n; i++) {
        resL[a[i].id] = a[i].L;
        resR[a[i].id] = a[i].R;
    }

    for (int i = 1; i <= n; i++) {
        if (ansR[i] == 0 || ansL[i] == 0) cout << 0 << '\n';
        else {
            cout << 1LL * trace[ansR[i]] - trace[ansL[i]] - trace[resR[i]] + trace[resL[i]] << '\n';
        }
    }
}

main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL); cout.tie(NULL);
    int test;
    cin >> test;
    while (test--) Solve();
    return 0;
}
