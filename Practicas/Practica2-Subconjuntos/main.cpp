#include <bits/stdc++.h>
#define psi pair <string,int>
#define F first
#define S second
#define PB push_back
#include "Diagrama.cpp"
using namespace std;
string epsilon = "Є";
const int N = 5000;

// Algoritmo de los subconjuntos : AFN -> AFD

    // Input : 
    // 0.- Tamaño del alfabeto
    // 1.- Entrada de mi alfabeto
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
        int nodo_aceptado = -1;
        set <set <int> > kernels;

        int contador_conjunto = 0;
        string id_conjunto = "A";
        string conjunto_vacio = "";
        bool hay_vacio = false;

        bool visitado[N];
        set <int> nodos_encontrados;

        string nuevoConjunto(string conjunto_actual, int n){       // Con este metodo conseguimos el nuevo id del subconjuto encontrado
            string conjuntos = "ABCDEFGHIJLMNOPQRSTUVWXYZ";

            if (n > 25){
                n%=25;
                conjunto_actual.push_back(conjuntos[n]);
            }
            else conjunto_actual[conjunto_actual.size() - 1] = conjuntos[n];
            

            return conjunto_actual;
        }

        void cerradura(int s){                                        // Hacemos un dfs para saber hasta donde podemos movernos dentro de nuestro grafo
            visitado[s] = true;
            nodos_encontrados.insert(s);

            for(int i = 0; i < adyacencia[s].size(); i++){
                if (visitado[adyacencia[s][i].S] == false && adyacencia[s][i].F == epsilon)
                    cerradura(adyacencia[s][i].S);
            }
        }


        void mover(string conjunto, set <int> valores_conjunto){    // La función de mover, necesitada en el algoritmo, en la cual nos movemos con todos el alfabeto 
           set <int> kernel_actual;

           for (auto i : alfabeto){
               for (auto j : valores_conjunto){
                   for (int k = 0; k < adyacencia[j].size(); k++){
                       if (adyacencia[j][k].F == i)
                           kernel_actual.insert(adyacencia[j][k].S);
                   }
               }

               if (kernel_actual.size() == 0){
                   if (conjunto_vacio.size() == 0){
                      conjunto_vacio = nuevoConjunto(id_conjunto, contador_conjunto++);
                   }

                   movimientos[conjunto][i] = conjunto_vacio;               // No encontramos ningun kernel por lo enviamos al pozo
                   hay_vacio = true;
               }
               else if (!kernels.count(kernel_actual) && kernel_actual.size() > 0){             // El kernel todavía no lo hemos visto antes
                    for (auto l : kernel_actual) cerradura(l);
                   string nuevo = nuevoConjunto(id_conjunto, contador_conjunto++);

                   subconjuntos[nuevo] = nodos_encontrados;
                   if (nodos_encontrados.count(nodo_aceptado)) aceptados.push_back(nuevo);

                   kernel[nuevo] = kernel_actual;
                   nodos_encontrados.clear();
                   movimientos[conjunto][i] = nuevo;

                   memset(visitado, false, sizeof(visitado));
               }
               kernel_actual.clear();
           }


       }

        void inicial(){ // Hacemos el paso principal del algoritmo, que es hacer cerradura con epsilon
            kernels.insert({nodo_inicial});

            cerradura(nodo_inicial);
            if (nodos_encontrados.count(nodo_aceptado)) aceptados.push_back(id_conjunto);
            subconjuntos[id_conjunto] = nodos_encontrados;
            kernel[id_conjunto] = {nodo_inicial};

            contador_conjunto++;

            nodos_encontrados.clear();
            memset(visitado, false, sizeof(visitado));
        }


    public :
        vector <psi> adyacencia[N];                         // La lista de adyacencia del AFN
        map <string, set<int> > subconjuntos;               // Tenemos un map de todos los subconjutos que encontramos 
        map <string, set<int> > kernel;                     // Tenemos un map de todos los kernels de los subconjuntos que encontramos
        map <string, map <string, string> > movimientos;    // Tenemos un map que nos ayuda hacer seguimiento de todos los movientos que realizamos
        vector <string> aceptados;
        set <string> alfabeto;

        void setDatos(int nodo_i, int nodo_a, set <string> alpha, auto adj){ // Hacemos un setter de los datos que vamos a ocupar
            nodo_inicial  = nodo_i;
            nodo_aceptado = nodo_a;
            alfabeto = alpha;
 
            for (int i = 0; i < N; i++)  adyacencia[i] = adj[i];
        }

        void constuir(){
            inicial();
            for (auto it : subconjuntos) mover(it.F, it.S);
            if (hay_vacio){
                for (auto i : alfabeto)
                   movimientos[conjunto_vacio][i] = conjunto_vacio;
            }
        }

};



int main(){

    set <string> alpha;
    int nodo_inicial, nodo_aceptado;
    vector <psi> adj[N];
    
    int n; cin >> n;

    for (int i = 0; i < n; i++) {
        string x; cin >> x;
        alpha.insert(x);
    }

    cin >> nodo_inicial >> n;

    for (int i = 0; i < n; i++){
        int from, to;
        string w;
        cin >> from >> to >> w;
        adj[from].PB({w, to});
    }

    cin >> nodo_aceptado;

    Subconjuntos actual;
    actual.setDatos(nodo_inicial, nodo_aceptado, alpha, adj);
    actual.constuir();

    
    Diagrama diagrama_actual;
    diagrama_actual.setDatos("A", actual.aceptados, actual.movimientos, actual.alfabeto);
    diagrama_actual.crearArchivo();
    diagrama_actual.mostrarDiagrama();


    return 0;
}
