#include <bits/stdc++.h>
#define psi pair <string,int>
#define F first
#define S second
#define PB push_back
using namespace std;
string epsilon = "Є";
const int N = 500;

// Algoritmo de los subconjuntos : AFN -> AFD

    // Input : 
    // 0.- Tamaño del abecedario
    // 1.- Entrada de mi abecedario
    // 2.- Cual es mi nodo inicial
    // 3.- Cuantas transiciones tiene mi lista de adyacencia
    // 4.- Los datos de mi lista de adyacencia 

    // Output:
    // El AFD

set <char> alpha;
int nodo_inicial = -1;
vector <psi> adj[N];

// Funciones del algoritmo de los subconjuntos :
//  1.- Cerradura  (Hacer dfs con epsilon)
//  2.- Mover      (Hacer dfs con todo el abecedario)


void inicial(int nodo_inicial){

}



int main(){

    for (int i = 0; i < 26; i++) {
        char x; cin >> x;
        alpha.insert(x);
    }

    cin >> nodo_inicial;

    int n; cin >> n;

    for (int i = 0; i < n; i++){
        int from, to;
        string w;
        cin >> from >> w >> to;
        adj[from].PB({w, to});
    }

    inicial(nodo_inicial);
//    algoritmo();


    return 0;
}
