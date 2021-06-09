#include <bits/stdc++.h>
#define psi pair<string,int>
#define pii pair<int,int>
#define PB push_back
#define F first
#define S second
#include "Postfix.cpp"
#include "Diagrama.cpp"
using namespace std;
string epsilon = "Є";

const int N = 5000;


class Thompson{
private :
    set <char> alpha;
    stack <pii> A;          // Pila que ocupamos al momento de hacer las diferentes operaciones dentro de la construcción de thompson

    pii agregarConcatenacion(pii a, pii b, int n){
        pii p = {a.F,b.S};
        
        vector <psi> clean, temp = adj[b.F];
        adj[b.F] = clean;

        for (auto i : temp) adj[a.S].PB(i);

        for (int i = 1; i <= n; i++){
            for (auto it : adj[i]){
                if (it.S == b.F) it.S = b.F;
            }
        }

        return p;
    }

    pii agregarOr(pii a, pii b, int i){
        pii regresar = {i, i+1};
        
        adj[i].PB({epsilon, a.F});
        adj[i].PB({epsilon, b.F});

        adj[a.S].PB({epsilon, i+1});
        adj[b.S].PB({epsilon, i+1});

        return regresar;
    }

    pii agregarCerradura(pii a, int i){
        pii p = {i, i + 1};
        adj[i].PB({epsilon, a.F});
        adj[i].PB({epsilon, i+1});

        adj[a.S].PB({epsilon, a.F});
        adj[a.S].PB({epsilon, i+1});

        return p;
    }
    
public :
    string expresion;
    int estado_inicial = -1;
    vector <psi> adj[N];    // Lista de adyacencia para el gráfo resultado de la contrucción de thompson

    void construir(set <char> abec){
        alpha = abec;
        int n = expresion.size();
        int contadorId = 1;
        estado_inicial = contadorId;

        for (int i = 0; i < n; i++){
            if (expresion[i] == '|'){ // Good - Or
                pii a = A.top(); A.pop();
                pii b = A.top(); A.pop();
                pii c = agregarOr(b, a, contadorId);
                A.push(c);
                estado_inicial = contadorId;
                contadorId+=2;
            }
            else if (expresion[i] == '*'){ // Good - Cerradura
                pii a = A.top(); A.pop();
                pii c = agregarCerradura(a, contadorId);
                estado_inicial = contadorId;
                A.push(c);
                contadorId+=2;
            }
            else if (expresion[i] == '?'){ // Good - Concatenacion
                pii a = A.top(); A.pop();
                pii b = A.top(); A.pop();
                pii c = agregarConcatenacion(b, a, contadorId);
                A.push(c);
            }
            else{   // Un nodo normal
                string s(1, expresion[i]);
                adj[contadorId].PB({s,contadorId+1}); 
                A.push({contadorId, contadorId+1});
                contadorId += 2;
            }
        }

       if (adj[estado_inicial].size() == 0) estado_inicial = 1;
    }
};


int main(){

    // Hacemos la creación del abecedario ocupado 
    string abc = "abcdefghijklmniopqrstuvwxyz";
    set <char> abc_entrada;
    for (char c : abc) abc_entrada.insert(c);


    // Pedimos al usuario la expresión
    cout << endl;
    cout << "Expresión  ->  ";
    string expresion_entrada; cin >> expresion_entrada;


    // Creamos una instancia de la clase de Expresion para obtener la expresion postfija
    Expresion expresion_actual;
    expresion_actual.convertirPostfija(expresion_entrada, abc_entrada);


    // Creams una instancia de la Clase Thompson para poder realizar su algoritmo
    Thompson actual;                                         // Creamos una instancia para poder realizar una construcción de thompson 
    actual.expresion = expresion_actual.expresion_postfija;  // Hacemos un Setter de la expresión que tomamos del input a la instancia creada 
    actual.construir(abc_entrada);                           // Hacemos el proceso de construir 


    // Creamos una instancia de la Clase Diagrama para poder mostrar el grafo de manera grafica
    Diagrama diagrama_actual;                                   // Creamos la instancia de la clase diagrama
    diagrama_actual.setAdjacencyList(actual.adj);               // Hacemos un setter de la lista de adyacencia para poder realizar el recorrido
    diagrama_actual.setEstadoInicial(actual.estado_inicial);   // Hacemos un setter del estado inicial para mostrarlo dentro del diagrama
    diagrama_actual.crearArchivo();                             // Aplicamos el método para crear archivo que es usado para representar el diagrama
    diagrama_actual.mostrarDiagrama();                          // Mostramos el diagrama

    return 0;
}
