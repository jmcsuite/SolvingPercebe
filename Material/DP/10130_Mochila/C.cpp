#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <iomanip>
#include <numeric>
#include <string>
#include <map>

using namespace std;

int maxValue(vector<pair<int, int>>& goodsData, int index, int sumP, int sumW) {
	if (index >= (int)goodsData.size()) {
		if (sumW >= 0) return sumP;
		else return 0; // cuidado 
	}
	if (sumW - goodsData[index].second >= 0) {
		int newSumP = sumP + goodsData[index].first;
		int newSumW = sumW - goodsData[index].second;
		return max(maxValue(goodsData, index + 1, sumP, sumW), maxValue(goodsData, index + 1, newSumP, newSumW));
	}
	else {
		return maxValue(goodsData, index + 1, sumP, sumW);
	}
}

int main() {
	ios::sync_with_stdio(0);
	cin.tie(0);
	int T;
	cin >> T;
	while (T--) {
		int totalSum = 0;
		int qGoods;
		int qPersons;
		cin >> qGoods;
		vector<pair<int, int>> goodsData(qGoods);
		for (int i = 0; i < qGoods; i++) {
			cin >> goodsData[i].first;
			cin >> goodsData[i].second;
		}
		cin >> qPersons;
		vector<int> personsCap(qPersons);
		for (int i = 0; i < qPersons; i++) {
			cin >> personsCap[i];
			totalSum += maxValue(goodsData, 0, 0, personsCap[i]);
		}
		cout << totalSum << endl;

	}
}

