#include <iostream>
using namespace std;

int main(int argc, const char * argv[]) {
    ios::sync_with_stdio(0);
    cin.tie(0);
    
    int noches=0,diff;
    double cant,k;
    
    cin>>k;
    
    cant=(k-1)/11;
    diff=(k-1)/11;
    
    while(cant-diff!=0){
        noches++;
        k*=2;
        cant=(k-1)/11;
        diff=(k-1)/11;
    }
    
    cout<<noches<<" "<<(long long)k << '\n';

    
    return 0;
}
