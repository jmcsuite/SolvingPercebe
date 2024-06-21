#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
int main() {
  int cases, objects, num;
  int suma;
  cin >> cases;
  for (int i = 0; i < cases; i++) {
    suma = 0;
    cin >> objects;
    vector<int> prices;
    for (int j = 0; j < objects; j++) {
      cin >> num;
      prices.push_back(num);
    }
    sort(prices.begin(), prices.end());

    for (size_t i = 0; i < prices.size(); i += 3) {
      int min = prices[i];
      for (size_t j = i; j < i + 3; ++j) {
       // cout << prices[j] << " ";

        if (prices[j] < min) {
          min = prices[j];
        }
      }
      suma += min;
    }
    cout << suma << '\n';
  }
}
