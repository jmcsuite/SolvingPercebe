#include <bits/stdc++.h>

using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  int casos;
  cin >> casos;
  
  for (int i = 0; i < casos; i++){
    int n;
    vector<int> sumas(n-1);
    cin>>n;
    int com=0;
    for(int j=2;j<=n;j++){
      int suma=0;
      for(int k=j;k<=n;k++){
        if(k%j==0)suma+=k;
      }
      sumas[com]=suma;
      com++;
    }
    int max=*max_element(sumas.begin(),sumas.end());
    int pos=1;
    for(int x:sumas){
      pos++;
      if(x==max)break;;
    }
    cout<<pos<<endl;
  }
}
