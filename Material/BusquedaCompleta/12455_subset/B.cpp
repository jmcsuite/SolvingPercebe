//Barras
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

bool barras(vector <int>, int, int, int);

int main() {
  int entrada;
  cin >> entrada;
  
  do{
    if(entrada==0)break;
    int length, nBars;
    cin >> length;
    cin >> nBars;
    vector <int> sizes(nBars);
    for(int i = 0; i<nBars; i++)cin >> sizes[i];

    sort(sizes.begin(), sizes.end());

    bool posible = barras(sizes, 0, 0, length);

    if(length == 0 || posible == true)cout << "YES\n";else cout << "NO\n";
    entrada--;
  }while(entrada > 0);
}

bool barras(vector <int> sizes, int i, int sum, int sumObj){
  if(sum > sumObj || i>= (int)sizes.size())return false;
    
  else if(i == (int)sizes.size()-1)return(sum+sizes[i]==sumObj);
  else if(sum==sumObj)return true;
    
  else{
    return barras(sizes, i+1, sum+sizes[i], sumObj) || barras(sizes, i+1, sum, sumObj);
  }
}
