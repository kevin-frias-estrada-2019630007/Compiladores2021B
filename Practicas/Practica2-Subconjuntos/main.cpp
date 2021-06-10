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
    
    // Funciones del algoritmo de los subconjuntos :
    //  1.- Cerradura  (Hacer dfs con epsilon)
    //  2.- Mover      (Hacer dfs con todo el abecedario)

class Subconjuntos{
    private :
        int nodo_inicial = -1;
        set <char> abc;
        set <set <int> > kernels;

        int contador_conjunto = 0;
        string id_conjunto = "A";

        bool visitado[N];
        set <int> nodos_encontrados;

        void dfs(int s){                                        // Hacemos un dfs para saber hasta donde podemos movernos dentro de nuestro grafo
            visitado[s] = true;
            nodos_encontrados.insert(s);

            for(int i = 0; i < adyacencia[s].size(); i++){
                if (visitado[adyacencia[s][i].S] == false && adyacencia[s][i].F == epsilon)
                    dfs(adyacencia[s][i].S);
            }
        }

        void mover(set <char> ){                                // La función de mover, necesitada en el algoritmo, en la cual nos movemos con todos el alfabeto 
            int n = abc.size();                                 // en los subconjuntos que tenemos
            for (int i = 0; i < n; i++){
            }
        }

        void cerradura(int nodo){
        }

        string idConjunto(string conjunto_actual, int n){       // Con este metodo conseguimos el nuevo id del subconjuto encontrado
            string conjuntos = "ABCDEFGHIJLMNOPQRSTUVWXYZ";

            if (n > 25){
                n%=25;
                conjunto_actual.push_back(conjuntos[n]);
            }
            else{
                conjunto_actual[conjunto_actual.size() - 1] = conjuntos[n];
            }

            return conjunto_actual;
        }


    public :
        vector <psi> adyacencia[N];               // La lista de adyacencia del AFN
        map <string, set<int> > subconjuntos;     // Tenemos un map de todos los subconjutos que encontramos 
        map <string, set<int> > kernel;           // Tenemos un map de todos los kernels de los subconjuntos que encontramos

        void imprimir(){
            for (auto it : subconjuntos){
                auto s = it.S;
                cout << it.F << "  |  ";
                for (auto it2 : s) cout << it2 << " ";
                cout << "  |  Kernel ->  ";

                auto x = kernel[it.F];
                for (auto it3 : x) cout << it3 << " ";
                cout << endl;

            }
        }

        void setDatos(int nodo, set<char> alpha, auto adj){ // Hacemos un setter de los datos que vamos a ocupar
            nodo_inicial = nodo;
            abc = alpha;
 
            for (int i = 0; i < N; i++)  adyacencia[i] = adj[i];
        }

        void inicial(){ // Hacemos el paso principal del algoritmo, que es hacer cerradura con epsilon
            set <int> kernel_inicial;
            kernel_inicial.insert(nodo_inicial);
            kernels.insert(kernel_inicial);

            dfs(nodo_inicial);
            subconjuntos[id_conjunto] = nodos_encontrados;
            kernel[id_conjunto] = kernel_inicial;

            contador_conjunto++;

            nodos_encontrados.clear();
            memset(visitado, false, sizeof(visitado));
        }

        void nombreTemporal(){

        }

};



int main(){

    set <char> alpha;
    int nodo_inicial = -1;
    vector <psi> adj[N];

    for (int i = 0; i < 26; i++) {
        char x; cin >> x;
        alpha.insert(x);
    }

    cin >> nodo_inicial;
    int n; cin >> n;

    for (int i = 0; i < n; i++){
        int from, to;
        string w;
        cin >> from >> to >> w;
        adj[from].PB({w, to});
    }


    Subconjuntos actual;
    actual.setDatos(nodo_inicial, alpha, adj);
    actual.inicial();
    actual.imprimir();

    return 0;
}
