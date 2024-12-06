ll knapsack(vll& ww, ll C) {
    vll w;
    for (ll x : ww) {
        if (x > C) continue;
        if (x == 0) continue;
        w.push_back(x);
    }
    if (w.empty()) return 0;

    ll maxw = w[0];
    for (size_t i = 0; i < w.size(); i++) maxw = max(maxw, w[i]);
    vll dp(maxw*2 + 1, -1);
    vll prev(maxw*2 + 1, -1);
    auto xy = [=](ll x) {
        return (x-C+maxw);
    };

    size_t b = 0; ll sum = 0;
    for (size_t i = 0; i < w.size(); i++) {
        if (sum + w[i] > C) break;
        sum+=w[i]; b = i;
    }

    prev[xy(sum)] = b+1;
    for (size_t i = b+1; i < w.size(); i++) {
        for (ll j = C-maxw; j <= C + maxw; j++) dp[xy(j)] = prev[xy(j)];
        for (ll j = C-maxw; j <= C; j++) dp[xy(j+w[i])] = max(prev[xy(j)], dp[xy(j+w[i])]);
        for (ll j = C + maxw; j > C; j--) {
            for (ll k = dp[xy(j)]-1; k > prev[xy(j)]; k--) dp[xy(j-w[k])] = max(dp[xy(j-w[k])], k);
        }
        swap(prev, dp);
    }
    for (int i = C; i >= 0; i--) if (prev[xy(i)] != -1) return i;
    return -1;
}
