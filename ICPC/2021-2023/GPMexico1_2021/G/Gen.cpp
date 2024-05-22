#include<bits/stdc++.h>
using namespace std;


int main(){
    for(int i=0; i<400; i+=4*4){
        cout << i << " : " << (__builtin_popcount(i)%2 == 0 ? "Good" : "Bad") << endl;
    }
}
