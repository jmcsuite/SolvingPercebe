#include <bitset>
#include <iostream>
using namespace std;
int main() {
  ios::sync_with_stdio(0);
  cin.tie(0);
  const int maxt = 50000;
  int n,n2,pares=0,impares=0,posi=0,j=0,comp,resimpares[maxt],respares[maxt];
  while(true){
    posi=0;
    pares=0;
    impares=0;
    cin>>n;
    comp=1;
    if(n==0)break;
    else{
      for(int i=0;i<31;i++){
        n2=n|comp;
        if(n2==n){
          posi++;
          if(posi%2==0){pares=pares|comp;}
          else {impares=impares|comp;}
        }
        if(i<30)comp=comp<<1;
      }
      respares[j]=pares;
      resimpares[j]=impares;
      j++;
    }
  }
  for(int x=0;x<j;x++){
    
    cout<<resimpares[x]<<" "<<respares[x]<<endl;
  }
}
//0253051@up.edu.mx
