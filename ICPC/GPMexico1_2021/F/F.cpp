#include<bits/stdc++.h>
using namespace std;
using ll = long long;
using vll = vector<ll>;
using pll = pair<ll,ll>;

string MilisToString(ll milis){
    ll mil = milis%1000;
    milis/=1000;
    ll sec = milis%60;
    milis/=60;
    ll min = milis%60;
    milis/=60;
    ll hours = milis;

    string mMil = to_string(mil);
    string mSec  = to_string(sec);
    string mMin = to_string(min);
    string mHours = to_string(hours);
    if(mMil.size() == 1) mMil = "0"+mMil;
    if(mMil.size() == 2) mMil = "0"+mMil;
    if(mSec.size() == 1) mSec = "0"+mSec;
    if(mMin.size() == 1) mMin = "0"+mMin;
    if(mHours.size() == 1) mHours = "0"+mHours;
    string del = ":";
    string ans = mHours+del+mMin+del+mSec+","+mMil;
    return ans;
}

ll StringToMilis(string& str){
    stringstream ss(str);
    vector<string> vs;
    string temp;
    while(getline(ss,temp,':')){
        if(temp.size() > 2){
            stringstream ds(temp);
            getline(ds,temp,',');
            vs.push_back(temp);
            getline(ds,temp);
            vs.push_back(temp);
            continue;
        }
        vs.push_back(temp);
    }
    ll ans = stoi(vs[0])*60*60*1000 + stoi(vs[1])*60*1000 + stoi(vs[2])*1000 + stoi(vs[3]);
    return ans;
}

ll StringInpToMilis(string& str){
    stringstream ss(str);
    string a;
    string b;
    getline(ss,a,'.');
    getline(ss,b,'.');
    return stoi(a)*1000 + stoi(b);
}

int main(){
    ios::sync_with_stdio(0);
    cin.tie(0);
    string first;
    getline(cin,first);
    string line;
    vector<vector<string>> input;
    vector<string> cap;
    while(getline(cin,line)){
        if(line.size() == 0){
            input.push_back(cap);
            cap.clear();
            continue;
        }
        cap.push_back(line);
    }
    input.push_back(cap);
    
    stringstream ss(first);
    string aa; ss>>aa;
    ss>>aa;
    ll add = StringInpToMilis(aa);
    ll N = input.size();
    for(int i=0; i<N; i++){
        string a,b,c;
        stringstream temp(input[i][1]);
        temp>>a>>b>>c;
        ll na, nc;
        na = StringToMilis(a);
        nc = StringToMilis(c);
        na+=add;
        nc+=add;
        string leAns = MilisToString(na) + " --> " + MilisToString(nc);
        input[i][1] = leAns;
    }

    for(int i=0; i<N; i++){
        for(size_t j=0; j<input[i].size(); j++){
            cout << input[i][j] << '\n';
        }
        if(i != N-1) cout << '\n';
    }
}
