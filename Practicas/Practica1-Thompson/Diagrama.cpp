#include <bits/stdc++.h>
using namespace std;
const int M = 5000;

class Diagrama{

    vector <psi> adyacencia[M];
    int estado_inicial = 1;

    int obtenerEstadoFinal(){
        int estado = -1;
         for (int i = 0; i < M; i++){
            if (adyacencia[i].size() > 0){
            for (auto j : adyacencia[i]) estado = max({estado, i, j.S});
            }
        }
         return estado;
    }

    public:

        void setEstadoInicial(int x){
            estado_inicial = x;
        }

        void mostrarDiagrama(){
            system("clear");
            system("dot -Tpng -Gsize=9,15\! -Gdpi=100 -osalida.png salida.gv");
            system("eog salida.png");
        }

        void imprimir(){
            cout << endl;
             for (int i = 0; i < M; i++){
                if (adyacencia[i].size() > 0){
                    for (auto j : adyacencia[i]) cout << i << " - " << j.F << " - " << j.S << endl;
                }
             }
             cout << endl;

          return;
        }

        void crearArchivo(){
            ofstream file { "salida.gv" };

            ofstream archivo;
            archivo.open("salida.gv");
            archivo << "digraph ejemplo{ \n";
            archivo << "\t rankdir=LR; \n \n";

            int estado_final = obtenerEstadoFinal();

            archivo << "\t node [shape = doublecircle]; " + to_string(estado_final) + "; \n"; 
            archivo << "\t node [shape = point ]; qi \n";
            archivo << "\t node [shape = circle];\n \n";
            archivo << "\t qi -> " + to_string(estado_inicial) + "; \n";

            for (int i = 0; i < M; i++){
                if (adyacencia[i].size() > 0){
                    for (auto j : adyacencia[i]) {
                        string a = "\t " + to_string(i) + " -> " + to_string(j.S) + " [ label= \"" + j.F + "\" ]; \n ";
                        archivo << a;
                    }
                }
            }

            archivo << "}" << endl;
            archivo.close();
        }
        
        void setAdjacencyList(auto adj){
            for (int i = 0; i < M; i++) adyacencia[i] = adj[i];
        }

};
