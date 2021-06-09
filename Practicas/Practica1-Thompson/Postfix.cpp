#include <bits/stdc++.h>
#define F first
#define S second
using namespace std;


class Expresion{
    private:
        map <int,int> ubicacion_parentesis;
        set <char> alpha;

        void ubicarParentesis(string expresion){
            int n = expresion.size();
            stack <pair<char,int> > p;

            for (int i = 0; i < n; i++){
                char c = expresion[i];
                if (c == '(') p.push({c,i});
                else{
                    if (!p.empty() && c == ')'){
                        if(p.top().F == '('){ubicacion_parentesis[p.top().S] = i; p.pop();}
                        else p.push({c,i});
                    }
                }
            }

            return;
          }

        string construccionFinal(stack <string> &A, stack <string> &B){
            string expresion_postfija = "";
    
            while(B.size() >= 1){
                if (B.top() == "*"){
                    if (A.size() >= 1){
                        string t = A.top(); A.pop();
                        A.push(t + "*");
                    }
                    else return "";
                }
                else if (B.top() == "|"){
                    if (A.size() >= 2){
                        string t1 = A.top(); A.pop();
                        string t2 = A.top(); A.pop();
                        A.push(t2 + t1 + "|");
                    }
                    else return "";
                }
                B.pop();
            }

            bool b = false;

             while(A.size() > 1){
                expresion_postfija = (A.top() + "?" + expresion_postfija);
                A.pop();
                b = true;
            }

            if (A.size() == 1 ){
                if (b) expresion_postfija = A.top() + expresion_postfija; 
                else expresion_postfija = A.top();
                A.pop();
            }

            return expresion_postfija;
        }


        string construccion(string expresion, int index_inicial, int index_final){
            stack<string> A,B;
            // La pila A es de lo que llevamos de la pila, es decir los caracteres ya concatenados con algún operador de OR, cerradura o unión
            // La pila B es responsable de los operadores de OR, cerradura y unión
    
            while(index_inicial < index_final){
                if (expresion[index_inicial] == '('){
                    string a = construccion(expresion, index_inicial + 1, ubicacion_parentesis[index_inicial]);
                    if (A.size() == 0) A.push(a);
                    else{
                        string x = construccionFinal(A,B);
                        x += (a + "?");
                        A.push(x);
                    }
                    
                    index_inicial = ubicacion_parentesis[index_inicial];
                }

                else if (expresion[index_inicial] == '*'){
                    if (A.size() == 0) return "";
                    
                    string a = A.top(); A.pop();
                    a += "*";
                    A.push(a);
                }

                else if (expresion[index_inicial] == '|'){
                    if (A.size() == 0) return "";
                    if (A.size() == 1) {
                        string t1 = A.top(); A.pop();
                        string t2 = construccion(expresion, index_inicial + 1, index_final);
                        index_inicial = index_final;
                        A.push(t1 + t2 + "|");
                    }
                    else{
                        string t1 = construccionFinal(A, B);
                        string t2 = construccion(expresion, index_inicial + 1, index_final);
                        index_inicial = index_final;
                        A.push(t1 + t2 + "|");
                        }
                }
                
                else{
                    string a (1,expresion[index_inicial]);
                    A.push(a);
                }

                index_inicial++;
            }
    
           string expresion_final = construccionFinal(A,B);
           return expresion_final;
        }

    public:

       string expresion_postfija;
       string expresion_infija;

       void convertirPostfija(string expresion, set <char> abec){
           alpha = abec;                             // Hacemos un setter del abecedario que estams ocupando
           ubicarParentesis(expresion);              // Función de ayuda para encontrar los parentesis y sus respectivo par para construir lo que hay en su interior
           expresion_infija = expresion;             // Se hace un setter de la expresión infija a la expresion de entrada con los ajustes de parentesis 
           string expresion_final = construccion(expresion, 0, expresion.size()); // Función para la construcción de la expresión postfija
           expresion_postfija = expresion_final;    // Setter de la expresión construida en el paso anterior 

           return;
       }

};
