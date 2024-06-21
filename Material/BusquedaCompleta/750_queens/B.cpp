// backtracking
// diagonal _ arriba
// diagonal _ abajo
// fila
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

bool d_up[30];
bool d_down[30];
bool rows[30];
int sol[8];

int c = 0;
void print_sol() {
    c++;
    if (c <= 9) cout << " ";
    cout << c << "      " ;
    for (int i = 0; i < 8; i++) cout << sol[i]+1 << (i < 7 ? " " : "\n");
    /* 
     *  if ( i < 7 ) {
     *      return " ";
     *   else 
     *       return "\n";
     */
}

// iterar columna por columna
// si llego al final imprimo
// si la columna, es la del input, tengo que procesal la fila del input

// por cada fila checo, rows, d_up, d_down.
// set rows, d_up, d_down, sol[c],
// recursividad, checo columna + 1
// unset rows, d_up, d_down.

// if (x + y) == (i+j), entonces comparten d_up. 
// if (x-y) == (i-j) entonces comparted d_down.   [-7, 7], entonces le sumo 7

int r_input, c_input;
// if (c == c_input && r != r_input) continue;

void queens(int c) {
    if (c == 8) {
        print_sol();
        return;
    }
    for (int i = 0; i < 8; i++) {
        if (rows[i] || d_up[i+c] || d_down[i-c+7]) continue;
        if (c == c_input && i != r_input) continue;
        rows[i] = d_up[i+c] = d_down[i-c+7] = true;
        sol[c] = i;
        queens(c+1);
        sol[c] = rows[i] = d_up[i+c] = d_down[i-c+7] = 0;
    }
}

void header() {
    cout << "SOLN       COLUMN\n";
    cout << " #      1 2 3 4 5 6 7 8\n\n";
}

int main () {
    cin.tie(0);
    ios::sync_with_stdio(0);

    bool first = true;
    ll T; cin >> T;
    for (int i = 0; i < T; i++) {
        c = 0;
        if (!first) cout << '\n';
        first = false;
        header();
        cin >> r_input >> c_input;
        r_input--; c_input--;
        queens(0);
    }
}
