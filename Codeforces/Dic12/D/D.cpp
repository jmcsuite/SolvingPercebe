#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;

const int maxn = 1e7+1;
bool p [MAXN] ;
void sieve( int n ) {
    for ( int i =0; i<n ; i++) p [ i ] = true ;
    p[ 0]= p[ 1]= false;
    for ( int i =2; i<n ; i++)
        for ( int j =2* i ; j<n ; j+=i )
            p [ j ] = false;
}
int crib[MAXN];
int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    sieve(MAXN);
    int ii = 0;
    for(int i  = 0; i < MAXN; i++){
        if(p[i]) ii=0;
        sieve[i] = ii;
        ii++;
    }
    
