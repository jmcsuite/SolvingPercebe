#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace CHT {
map<ll, ll> mp;
map<double, ll> qrange;
double INF = 1e18;

double Intersect(map<ll, ll>::iterator a, map<ll, ll>::iterator b) {
  return double(a->second - b->second) / double(b->first - a->first);
}

bool Check(ll m, ll x) {
  if (mp.find(m) != mp.end()) {
    if (mp[m] >= x) return false;
    return true;
  }

  auto y = mp.upper_bound(m);
  if (y == mp.end() || y == mp.begin()) return true;
  auto u = (--y);
  ++y;
  double sec = Intersect(u, y);
  double cross = double(u->second - x) / double(m - u->first);
  if (sec < cross) return false;
  return true;
}

void UpdateQRange(map<ll, ll>::iterator it) {
  auto x = ++it;
  --it;
  if (x == mp.end())
    qrange[INF] = it->first;
  else
    qrange[Intersect(it, x)] = it->first;
}

void UpdateRight(ll m) {
  auto it = mp.find(m);
  auto x = ++it;
  --it;
  if (x == mp.end()) return;
  while (1) {
    auto y = ++x;
    --x;
    if (y == mp.end()) return;
    double sec = Intersect(y, x);
    double cross = Intersect(y, it);
    if (sec > cross) return;
    qrange.erase(sec);
    mp.erase(x);
    x = y;
  }
}

void UpdateLeft(ll m) {
  auto it = mp.find(m);
  if (it == mp.begin()) return;
  auto x = --it;
  ++it;

  auto n = ++it;
  --it;
  if (n == mp.end())
    qrange.erase(INF);
  else
    qrange.erase(Intersect(x, n));

  while (x != mp.begin()) {
    auto y = --x;
    ++x;
    double sec = Intersect(y, x);
    double cross = Intersect(y, it);
    if (sec < cross) return;
    qrange.erase(sec);
    mp.erase(x);
    x = y;
  }
}

void Add(ll m, ll x) {
  if (!Check(m, x)) return;
  mp[m] = x;
  UpdateRight(m);
  UpdateLeft(m);
  auto it = mp.find(m);
  UpdateQRange(it);
  if (it == mp.begin()) return;
  UpdateQRange(--it);
}

ll Eval(map<ll, ll>::iterator it, ll x) { return it->first * x + it->second; }

ll GetMax(ll x) {
  auto it = qrange.lower_bound(x);
  return Eval(mp.find(it->second), x);
}
}  // namespace CHT

const int maxn = 2e5;
ll vl[maxn];

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  ll N;
  cin >> N;
  for (int i = 0; i < N; i++) cin >> vl[i];
  ll ans, sum, res;
  ans = sum = res = 0;
  CHT::Add(0, 0);
  for (ll i = N - 1; i >= 0; i--) {
    res = res + sum + vl[i];
    sum = sum + vl[i];
    ans = max(ans, res + CHT::GetMax(i));
    CHT::Add(sum, (res + i * sum) * -1ll);
  }
  cout << ans << '\n';
}
