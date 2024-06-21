#include <iostream>
#include <vector>
using namespace std;

int main()
{
    int fechas, dia, mes, year;
    pair<string, int> personaMax("",-1), personaMin("", 1000000000);
    string nombre;
    
    cin >> fechas;
    while (fechas--) {
        
        cin >> nombre >> dia >> mes >> year;
 
        int comparator;
        comparator = year * 10000 + mes * 100 + dia;

        pair<string, int> persona(nombre, comparator);
        if (persona.second < personaMin.second) personaMin = persona;
        if (persona.second > personaMax.second) personaMax = persona;

    }

    cout << personaMin.first << endl << personaMax.first << endl;
}


