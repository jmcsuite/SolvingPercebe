struct slope {
  ll m, a, i;
  ll eval(ll x) { return x * m + a; }
};

struct cht {
  // gets minimum;
  // increasing queries
  // non-increasing (decreasing) slopes
  list<slope> dq;

  // does b intersect base before a?
  bool remove(slope base, slope a, slope b) {
    ll deltaa = (base.a - a.a) * (b.m - base.m);
    ll deltab = (base.a - b.a) * (a.m - base.m);
    return deltaa >= deltab;
  }

  void add(slope x) {
    if (dq.empty()) {
      dq.push_back(x);
      return;
    }

    // slope could be the same
    if (dq.size() == 1) {
      if (dq.back().m != x.m) {
        dq.push_back(x);
        return;
      }
      slope a = dq.back();
      dq.pop_back();
      if (a.a < x.a)
        dq.push_back(a);
      else
        dq.push_back(x);
      return;
    }

    slope a = dq.back();
    dq.pop_back();
    slope base = dq.back();
    while (remove(base, a, x)) {
      a = base;
      dq.pop_back();
      if (dq.empty()) break;
      base = dq.back();
    }
    dq.push_back(a);

    // slope could be the same
    if (x.m != a.m) dq.push_back(x);
  }

  // for index i > j
  ll getmin(ll x, ll j) {
    while (dq.front().i <= j) dq.pop_front();
    if (dq.size() == 1) return dq.front().eval(x);

    slope a = dq.front();
    dq.pop_front();
    slope b = dq.front();
    while (b.eval(x) <= a.eval(x)) {
      a = b;
      dq.pop_front();
      if (dq.empty()) break;
      b = dq.front();
    }
    dq.push_front(a);
    return dq.front().eval(x);
  }
};
