#include <bits/stdc++.h>

#define forr(i, a, b) for(int i = a; i <= b; ++ i)
#define for1(i, n) forr(i, 1, n)
#define for0(i, n) forr(i, 0, n - 1)
#define forn(i, n) for0(i, n)
#define pb push_back
#define fi first
#define se second

using namespace std;

typedef long long ll;
typedef vector<int> vi;
typedef vector<ll> vl;
typedef pair<int, int> ii;

const int MX = 100005;
int n, m, k[MX];
vi a[MX], pos[MX], ind[MX];

tuple<ll, ll, ll> extendedGcd (ll a, ll b) {
	if (b == 0) {
		if (a > 0) return {a, 1, 0};
		return {-a, -1, 0};
	} else {
		auto [d, x, y] = extendedGcd(b, a % b);
		return {d, y, x - y * (a / b)};
	}
}


pair<ll, ll> crt (ll x, ll mod, ll a, ll m) {
	if (x == -1 || a == -1) return {-1, -1};
	
	auto [d, s, t] = extendedGcd(mod, -m);
	if ((a - x) % d != 0) return {-1, -1};
	ll step = m / d;
	ll k = s * (((a - x) / d) % step) % step;
	if (k < 0) k += step;
	x += mod * k;
	mod *= step;
	
	return {x, mod};
}

struct SparseTable {
	vector<vl> x, mod;
	vi logTable;
	
	SparseTable (int n, vl a, vl b) {
		int k = log2(n) + 3;
		x.assign(k, vl(n));
		mod.assign(k, vl(n));
		logTable.resize(n + 5);
		
		for (int i = 2; i < n + 5; i++) {
			logTable[i] = logTable[i / 2] + 1;
		}
		
		forn (i, n) {
			x[0][i] = a[i];
			mod[0][i] = b[i];
		}
		
		for (int j = 1; j < k; j++) {
			for (int i = 0; i + (1 << j) <= n; i++) {
				auto [a, b] = crt(x[j - 1][i], mod[j - 1][i], x[j - 1][i + (1 << (j - 1))], mod[j - 1][i + (1 << (j - 1))]);
				x[j][i] = a;
				mod[j][i] = b;
			}
		}
	}
	
	pair<ll, ll> query (int l, int r) {
		int j = logTable[r - l + 1];
		auto [a, b] = crt(x[j][l], mod[j][l], x[j][r - (1 << j) + 1], mod[j][r - (1 << j) + 1]);
		return {a, b};
	}
};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0);
    
    cin >> n >> m;
    forn (i, n) {
		cin >> k[i];
		a[i].resize(k[i]);
		
		forn (j, k[i]) {
			cin >> a[i][j];
			pos[a[i][j]].pb(i);
			ind[a[i][j]].pb(j);
		}
	}
	
	forr (x, 1, m) {
		if (!pos[x].size()) {
			cout << 0 << endl;
			continue;
		}
		
		vl a, b;
		forn (i, pos[x].size()) {
			a.pb(ind[x][i]);
			b.pb(k[pos[x][i]]);
		}
		
		SparseTable st(pos[x].size(), a, b);
		int mx = 0, i = 0, j = 0;
		
		while (j < (int)pos[x].size()) {
			if (j && pos[x][j - 1] + 1 < pos[x][j])
				i = j;
			
			while (st.query(i, j).fi == -1)
				i++;
			
			mx = max(mx, j - i + 1);
			j++;
		}
		
		/* if (x == 1) {
			auto [a, b] = st.query(0, 2);
			cout << a << " " << b << endl;
		} */
		
		cout << mx << endl;
	}
    
    return 0;
}

  	 	  	 		 	    		 	 	 		 	 	
