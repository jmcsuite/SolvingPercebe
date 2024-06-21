#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <string>
#include <map>

using namespace std;


int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	int cas = 1;
	while (T--) {
		int rungs; cin >> rungs;
		map <int, int> diffs;
		int prev = 0;
		for (int i = 0; i < rungs; i++) {
			int h; cin >> h;
			diffs[h - prev]++;
			prev = h;
		}

		/*int prevStep = -2;
		int prevfreq = -2;
		auto last = std::prev(diffs.end());
		if (diffs.size() > 1) {
			auto plast = std::prev(last);
			prevStep = plast->first;
			prevfreq = plast->second;
		}*/
		auto lastF = std::prev(diffs.end());
		auto last = lastF;
		bool increment = last->second > 1;
		if (!increment && diffs.size() > 1) {
			auto plast = std::prev(last);
			rungs -= 2;
			while (rungs--) {
				if (plast->first + 1 != last->first)
					break;
				if (plast->second > 1)
					increment = true;
				last = std::prev(last);
				plast = std::prev(plast);
			}
		}

		if (increment)
			cout << "Case " << cas << ": " << lastF->first + 1 << endl;
		else {
			cout << "Case " << cas << ": " << lastF->first << endl;
		}
		cas++;
	}
}

