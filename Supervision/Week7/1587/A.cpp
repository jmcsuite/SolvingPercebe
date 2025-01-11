#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int BASE = 1e9;
struct BigInteger {
    vll digits;

    BigInteger() {
        digits.clear();
        digits.push_back(0);
    }
    BigInteger(ll number) {
        digits.clear();
        do {
            digits.push_back(number%BASE);
            number /=BASE;
        } while (number);
    }

    BigInteger operator + (const BigInteger &b) const {
        BigInteger res = BigInteger();
        res.digits.resize(max(b.digits.size(), digits.size()));
        ll remainder = 0;
        for (size_t i=0; i<res.digits.size(); i++) {
            if (i < digits.size()) remainder += digits[i];
            if (i < b.digits.size()) remainder += b.digits[i];
            res.digits[i] = remainder % BASE;
            remainder /= BASE;
        }
        while (remainder) {
            res.digits.push_back(remainder % BASE);
            remainder /= BASE;
        }
        return res;
    }

    BigInteger operator * (const BigInteger &b) const {
        BigInteger res = BigInteger();
        res.digits = vector<ll>(b.digits.size() + digits.size() - 1, 0);
        for (size_t i=0; i<digits.size(); i++) for(size_t j=0; j<b.digits.size(); j++)
            res.digits[i+j] += digits[i] * b.digits[j];
        ll remainder = 0;
        for (size_t i=0; i<res.digits.size(); i++) {
            remainder += res.digits[i];
            res.digits[i] = remainder % BASE;
            remainder /= BASE;
        }
        while (remainder) {
            res.digits.push_back(remainder % BASE);
            remainder /= BASE;
        }
        return res;
    }

    void print() {
        cout << digits.back();
        for (int i = digits.size() - 2; i>=0; i--) cout << setw(9) << setfill('0') << digits[i];
    }

    static BigInteger power(const BigInteger &b, ll k) {
        if (k == 0) return BigInteger(1);
        if (k == 1) return b;
        BigInteger res = power(b, k/2);
        res = res * res;
        if (k&1) return res * b;
        return res;
    }

    bool operator <(const BigInteger&b) const {
        if (digits.size() != b.digits.size()) return digits.size() < b.digits.size();
        for (int i = digits.size() - 1; i>=0; i--) {
            if (digits[i] != b.digits[i]) return (digits[i] < b.digits[i]);
        }
        return false;
    }
};

const int maxn = 5e4;
BigInteger v[maxn];
ll vl[maxn];

BigInteger rr(ll a, ll b) {
    // a < b
    if (a+1 == b) return v[a];

    ll d = 0;
    for (int i=a; i<b; i++) if (vl[i] < 0) d^=1;
    if (d == 0) {
        BigInteger ans(1);
        for (int i=a; i<b; i++) ans = ans * v[i];
        return ans;
    }
    int f,e;
    for (int i=a; i<b; i++) if (vl[i] < 0) e=i;
    for (int i=b-1; i>=a; i--) if (vl[i] < 0) f=i;

    BigInteger x(1);
    BigInteger y(1);
    for (int i=f+1; i<b; i++) x = x * v[i];
    for (int i=a; i<e; i++) y = y * v[i];
    if (f+1 == b) return y;
    if (a == e) return x;
    if (x < y) return y;
    return x;
}
bool valid(ll a, ll b) {
    if (b > a+1) return true;
    if (b < a+1) return false;
    if (vl[a] < 0) return false;
    return true;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll n; cin>>n;
    for (int i=0; i<n; i++) cin>>vl[i];
    if (n == 1) {
        cout << vl[0] << '\n';
        return 0;
    }
    BigInteger ans(0);
    for (int i=0; i<n; i++) {
        if (vl[i] < 0) v[i] = BigInteger(vl[i]*-1);
        else v[i] = BigInteger(vl[i]);
    }
    ll p = 0; 
    for (int i=0; i<n; i++) {
        if (vl[i] != 0) continue;
        if (valid(p,i)) {
            BigInteger b = rr(p,i);
            if (ans < b) ans = b;
            p = i+1;
        }
    }
    if (valid(p,n)) {
        BigInteger b = rr(p,n);
        if (ans < b) ans = b;
    }
    ans.print();
    cout << '\n';
}

