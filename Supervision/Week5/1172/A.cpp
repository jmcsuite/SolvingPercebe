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
            digits.push_back(number % BASE);
            number /= BASE;
        } while (number);
    }

    BigInteger operator+(const BigInteger &b) const {
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

    BigInteger operator*(const BigInteger &b) const {
        BigInteger res = BigInteger();
        res.digits = vector<ll>(b.digits.size() + digits.size() - 1, 0);
        for (size_t i=0; i<digits.size(); i++) 
            for (size_t j=0; j<b.digits.size(); j++)
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
        for (int i=digits.size() - 2; i>= 0; i--)
            cout << setw(9) << setfill('0') << digits[i];
    }

};

bool vis[31][31][31][3];
pair<bool, BigInteger> ff[31][31][31][3];
pair<bool, BigInteger> dp(ll A, ll B, ll C, ll x) {
    if (x == 0 && A == 0) return {false, 0};
    if (x == 1 && B == 0) return {false, 0};
    if (x == 2 && C == 0) return {false, 0};
    if (vis[A][B][C][x]) return ff[A][B][C][x];
    vis[A][B][C][x] = true;
    auto &d = ff[A][B][C][x];
    if (x == 0) A--;
    if (x == 1) B--;
    if (x == 2) C--;
    if (A == B && B == C && A == 0 && x != 0) return d = {true, 1};
    if (A == B && B == C && A == 0) return d = {false, 0};
    d = {false, 0};
    if (x != 0) {
        auto p = dp(A,B,C,0);
        if (p.first != false) d.first = p.first;
        if (p.first != false) d.second = d.second + BigInteger(A)*(p.second);
    }

    if (x != 1) {
        auto p = dp(A,B,C,1);
        if (p.first != false) d.first = p.first;
        if (p.first != false) d.second = d.second + BigInteger(B)*(p.second);
    }

    if (x != 2) {
        auto p = dp(A,B,C,2);
        if (p.first != false) d.first = p.first;
        if (p.first != false) d.second = d.second + BigInteger(C)*(p.second);
    }
    return d;
}

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll N; cin >> N;
    auto ans = dp(N-1,N,N,1);
    auto sol = ans.second * BigInteger(N);
    sol.print();
    cout << '\n';
}
