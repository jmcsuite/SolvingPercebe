#include <bits/stdc++.h>
using namespace std;

vector<int> intToBinary(int num) {
    vector<int> binary;
    while(num > 0) {
        binary.insert(binary.begin(), num % 2);
        num = num / 2;
    }
    return binary;
}


int main(int argc, char const *argv[])
{
    int n;
    while(cin>>n, n){
        if (n==0) break;
        vector<int> vec = intToBinary(n);
        int a=0;
        int b=0;
        int cont=0;
        //cout<<vec[0]<<" "<<vec[1]<<" "<<vec[2]<<"\n";

        for(int bit=(vec.size()-1); bit>=0; bit--){
            int num = vec[bit];
            if (num==1 && cont%2==0){
                cont++;
                int xponent=pow(2,(vec.size()-bit-1));
                a+=xponent;
            }else if(num==1 && cont%2!=0){
                cont++;
                int xponent=pow(2,(vec.size()-bit-1));
                b+=xponent;
            }
        }

        cout<<a<<" "<<b<<"\n";

    }


    return 0;
}
