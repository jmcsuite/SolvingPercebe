vector<int> kmp(string& s){
    int n = s.size();
    vector<int> vs(n);
    //vs[i] = kmp que acaba en la posicion i
    for(int i=1; i<n; i++){
        int j = vs[i-1]; // j = aproximacion anterior
        while(j!=0 && s[i] != s[j]){
            j = vs[j-1];
        }
        if(s[i] == s[j]) j++;
        vs[i] = j;
    }
    return vs;
}
    
