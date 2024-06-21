vector<int> z_func(string a) {
    // z[i] = max x such that [0, 1, ..., x) = [i, i+1, ..., i+x)
    // z[i] is the length
    vector<int> z(a.size(),0);
    for(int i = 1, l = 0, r = 0; i < (int)a.size(); ++i){
        if(i <= r) z[i] = min(r-i+1, z[i-l]);
        while(z[i] + i < (int)a.size() && a[z[i]] == a[z[i]+i])z[i]++;
        if(i+z[i]-1 > r)l = i, r = z[i]+i-1;
    }
    // optional: z[0] = a.size();
    return z;
}
