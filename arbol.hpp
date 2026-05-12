#include <vector>
#include <iostream>

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
    Arbol(int _k);

    bool isEmpty();
    int size();

    string root();

    int padre(int value);
    vector<string> hijos(string val);

    bool insertar(string dataPadre, string data);
    bool remover(int value);
    
    Nodo* buscar(Nodo* nodo, string data);

    vector<string> preOrder();
    vector<int> postOrder();
    vector<int> inOrder();
};