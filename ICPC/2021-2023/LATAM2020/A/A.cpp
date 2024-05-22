#include <bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;
string ans;
vll va;

void solve(int N){
    if(N == 1) return;
    set<string> st;
    char c = char(1);
    string base; base+=c;
    st.insert(base);
    queue<string> q;
    q.push(base);
    while(1){
        string curr = q.front();
        q.pop();
        int M = curr.size();
        for(int i=0; i<M; i++){
            for(int j=0; j<M; j++){
                ll ii = curr[i];
                ll jj = curr[j];
                if(ii + jj <= int(curr[M-1])) continue;
                if(ii + jj > N) break;
                if(ii + jj ==N){
                    curr += char(ii+jj);
                    ans = curr;
                    return;
                }
                string curr2 = curr+char(ii+jj);
                if(st.find(curr2) == st.end()) {
                    st.insert(curr2);
                    q.push(curr2);
                }
            }
        }
    }
}
void cot(string A){
    if(A.size() == 1) return;
    string B = A.substr(0,A.size()-1);
    ll M = B.size();
    for(int i=0; i<M; i++){
        for(int j=0; j<M; j++){
            ll ii = B[i];
            ll jj = B[j];
            if(int(A[M] == ii+jj)){
                cot(B);
                cout << "1 " << ii << endl;
                cout << "1 " << jj << endl;
                return;
            }
        }
    }
}

        

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    ll X,N; cin>>X>>N;
    if(X != 1){
        cout << "*\n";
        return 0;
    }
        
    solve(N);
    /*for(int i=0; i<ans.size(); i++){
        cout <<  int(ans[i]) << endl;
    }*/
    cot(ans);
}
