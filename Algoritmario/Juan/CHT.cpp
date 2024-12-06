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

  ll prevInf = -1;

  bool Check(ll m, ll x) {
    if (mp.find(m) != mp.end()) {
      if (mp[m] >= x) return false;
      auto it = mp.find(m);
      auto n = ++it;
      --it;
      if (n == mp.end()) {
        qrange.erase(INF);
        qrange[INF] = m;
        prevInf = it->first * -1;
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
      prevInf = m * -100;
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
