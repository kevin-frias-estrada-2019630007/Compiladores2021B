#include <bits/stdc++.h>
using namespace std;
const int M = 5000;

class Diagrama{

    string estado_inicial;
    vector <string> estados_aceptacion;
    map <string, map <string, string> > movimientos;    // Tenemos un map que nos ayuda hacer seguimiento de todos los movientos que realizamos
    set <string> alfabeto;

    public:

       void setDatos(string nodo_a, vector <string> nodo_b, auto moves, set<string> alfa){
           estado_inicial = nodo_a;
           estados_aceptacion = nodo_b;
           movimientos = moves;
           alfabeto = alfa;
       }

        void mostrarDiagrama(){
            system("clear");
            system("dot -Tpng -Gsize=9,15! -Gdpi=100 -osalida.png salida.gv");
            system("eog salida.png");
        }

        void crearArchivo(){
            ofstream file { "salida.gv" };

            ofstream archivo;
            archivo.open("salida.gv");
            archivo << "digraph ejemplo{ \n";
            archivo << "\t rankdir=LR; \n \n";

            string estados_f = "";
            for (int i = 0; i < estados_aceptacion.size(); i++) estados_f += (estados_aceptacion[i] + " ");

            archivo << "\t node [shape = doublecircle]; " + estados_f + "; \n"; 
            archivo << "\t node [shape = point ]; qi \n";
            archivo << "\t node [shape = circle];\n \n";
            archivo << "\t qi -> " + estado_inicial + "; \n";

            for (auto it : movimientos){
                for (auto i : alfabeto){
                    if ((it.S).find(i) != (it.S).end()){
                        string a = "\t " + it.F + " -> " + movimientos[it.F][i] + " [ label= \"" + i + "\" ]; \n ";
                        archivo << a;
                    }
                }
            }

            archivo << "}" << endl;
            archivo.close();
        }
};
