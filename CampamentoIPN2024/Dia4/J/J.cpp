struct CHT {
  struct Frac {
    ll x, y;
    double eps = 1e-9;

    bool operator<(const Frac& other) const {
      return ((double(x) / double(y) + eps) <
              double(other.x) / double(other.y)) &&
             ((double(x) / double(y) - eps) <
              double(other.x) / double(other.y));
    }

    bool operator==(Frac other) const { return (other.y * x) == (other.x * y); }

    Frac(ll a, ll b) : x(a), y(b) {}
    Frac(ll a) : x(a), y(1) {}
  };

  map<ll, ll> mp;
  map<Frac, ll> qrange;
  Frac INF = {(1ll << 56), 1};

  Frac Intersect(map<ll, ll>::iterator a, map<ll, ll>::iterator b) {
    return {a->second - b->second, b->first - a->first};
  }


  bool Check(ll m, ll x) {
    if (mp.find(m) != mp.end()) {
      if (mp[m] >= x) return false;
      auto it = mp.find(m);
      auto n = ++it;
      --it;
      if (n == mp.end()) {
        qrange.erase(INF);
        qrange[INF] = m;
      } else {
        qrange.erase(Intersect(it, n));
      }

      if (it == mp.begin()) return true;
      auto xx = --it;
      ++it;
      qrange.erase(Intersect(xx, it));
      return true;
    }
    auto y = mp.upper_bound(m);
    if (y == mp.begin()) return true;

    if (y == mp.end()) {
      qrange.erase(INF);
      return true;
    }
    auto u = (--y);
    ++y;

    Frac sec = Intersect(u, y);
    Frac cross = {u->second - x, m - u->first};
    if (sec < cross) return false;
    qrange.erase(sec);
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
      Frac sec = Intersect(y, x);
      Frac cross = Intersect(y, it);
      if (cross < sec) return;

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

    while (x != mp.begin()) {
      auto y = --x;
      ++x;
      Frac sec = Intersect(y, x);
      Frac cross = Intersect(y, it);
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
    --it;
    UpdateQRange(it);
  }

  ll Eval(map<ll, ll>::iterator it, ll x) { return it->first * x + it->second; }

  ll GetMax(ll x) {
    auto it = qrange.lower_bound(x);
    return Eval(mp.find(it->second), x);
  }
};

const int maxn = 150001;
ll depth[maxn];
ll BottomUp[maxn];
ll TopDown[maxn];
ll Sum[maxn];
long long vl[maxn];
ll pa[maxn];
vll vadj[maxn];

struct ST {
  CHT Bot;
  CHT Top;
  vll vadj;
};

ll ans = 0;
ST st[maxn];

void Merge(ll x, ll v) {
  if (st[x].vadj.size() > st[v].vadj.size()) swap(st[x], st[v]);
  ll p = pa[v];

  for (ll a : st[x].vadj) {
    ll tp = BottomUp[a] - BottomUp[v] + Sum[v] * (depth[v] - depth[a]);
    tp = tp - Sum[p] * (depth[a] - 2 * depth[v] + 1) - TopDown[p];
    tp = tp + st[v].Top.GetMax(depth[a] - 2 * depth[v] + 1);
    ans = max(ans, tp);
  }

  for (ll a : st[x].vadj) {
    ll tp = TopDown[a] - TopDown[p] - BottomUp[v];
    tp = tp + Sum[a] * (1 - 2 * depth[v]) + Sum[p] * (2 * depth[v] - 1) +
         Sum[v] * depth[v];
    tp = tp + st[v].Bot.GetMax(Sum[a] - Sum[p] - Sum[v]);
    ans = max(ans, tp);
  }

  for (ll b : st[x].vadj) {
    st[v].Top.Add(Sum[b], TopDown[b]);
    st[v].Bot.Add(depth[b], BottomUp[b]);
    st[v].vadj.push_back(b);
  }
}

void DFS(ll x, ll p) {
  depth[x] = depth[p] + 1;
  Sum[x] = Sum[p] + vl[x];
  BottomUp[x] = BottomUp[p] + Sum[x];
  TopDown[x] = TopDown[p] + vl[x] * depth[x];
  pa[x] = p;

  ans = max(ans, BottomUp[x]);
  ans = max(ans, TopDown[x]);

  for (ll y : vadj[x]) {
    if (y == p) continue;
    DFS(y, x);
    Merge(y, x);
  }
  if (st[x].vadj.size() > 0) return;
  st[x].vadj.push_back(x);
  st[x].Top.Add(Sum[x], TopDown[x]);
  st[x].Bot.Add(depth[x], BottomUp[x]);
}

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  long long N;
  cin >> N;
  for (int i = 1; i < N; i++) {
    long long u, v;
    cin >> u >> v;
    vadj[u].push_back(v);
    vadj[v].push_back(u);
  }
  for (int i = 1; i <= N; i++) cin >> vl[i];
  DFS(1, 0);
  cout << (long long)ans << '\n';
}
