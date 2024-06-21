#include <bitset>
#include <iostream>
using namespace std;

int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);

  long long comp;
  int n,n2,pares=0,impares=0,posi=0;
  while(true){
    posi=0;
    pares=0;
    impares=0;
    cin>>n;
    comp=1;
    if(n==0)break;
    else{
      for(int i=0;i<30;i++){
        n2=n|comp;
        if(n2==n){
          posi++;
          if(posi%2==0){pares=pares|comp;}
          else {impares=impares|comp;}
        }
        comp=comp<<1;
      }
    }
    cout << impares << " " << pares << endl;
  }
  /*
  for(int x=0;x<j;x++){
    
    cout<<resimpares[x]<<" "<<respares[x]<<endl;
  }
  */
}
