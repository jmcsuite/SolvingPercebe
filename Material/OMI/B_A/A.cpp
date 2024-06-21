#include <bits/stdc++.h>
using namespace std;


// represento cada solucion como numero
// cada opcion como un 1 o un 0

string sol[8] = {"aguia", "pomba", "vaca", "homem", "pulga", "lagarta", "sanguessuga", "minhoca" };
map<string, int> m1 = {{"invertebrado", 1}, {"mamifero", 1}, {"anelideo", 1}, {"onivoro",1}};
map<string, int> m2 = {{"herbivoro", 1}, {"onivoro", 1}};


// voy a leer mis tres cadenas.
// la primera decide el rango [0, 4), [4, 8}
// la segunda representa el segundo bit.
// la tercera el bit mas pequenio. 

// para la tercera, si es el mapa de arriba , es decir , [0, 4) uso m1;
// si no, m2.
int main () {
    string a,b,c;
    cin >> a >> b >> c;
    int i = 4;
    int ans = 0;

    ans += m1[a]*i;
    i/=2;

    ans += m1[b]*i;
    i/=2;

    if (ans >= 4) ans += m2[c]*i;
    else ans += m1[c]*i;
    cout << sol[ans] << '\n';
}
