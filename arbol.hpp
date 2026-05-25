#include <iostream>
#include <vector>

using namespace std;

class Arbol {
private:
    // Nodo
    struct Nodo {
        string m_data;    // tag/campo o valor a almacenar
        Nodo* m_padre;
        vector<Nodo*> m_hijos;

        Nodo(string data, Nodo* padre = nullptr);
    };

    Nodo* rootNodo;
    int treeSize;
    int k;  // Número de hijos por cada nodo

    void preOrder(Nodo* nodo, vector<string>& result);
    void postOrder(Nodo* nodo, vector<int>& result);
    void deleteSubtree(Nodo); //si se borra un nodo, se borran todos sus hijos y luego ese nodo.

public:
    Arbol(int k);

    bool isEmpty();
    int size();

    //string raiz();
    Nodo* raiz();

    int padre(int value);
    vector<string> hijos(string val);

    Nodo* insertar(Nodo* padre, string data);
    bool remover(int value);
    
    Nodo* buscar(Nodo* nodo, string data);

    vector<string> preOrder();
    vector<int> postOrder();
    vector<int> inOrder();


    // Uso de string& para pasar una referencia al string original.
    // Sin el &, se crearia una copia del string.
    void insertarLibro(const string& archivo);
};