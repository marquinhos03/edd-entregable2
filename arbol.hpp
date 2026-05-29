#ifndef ARBOL_HPP
#define ARBOL_HPP

#include <iostream>
#include <vector>

class Arbol {
private:
    // Nodo
    struct Nodo {
        std::string m_data;    // tag/campo o valor a almacenar
        Nodo* m_padre;
        std::vector<Nodo*> m_hijos;

        Nodo(std::string data, Nodo* padre = nullptr);
    };

    Nodo* rootNodo;     // Nodo raíz del arbol
    int treeSize;       // Tamaño del arbol
    int k;              // Número de hijos por cada nodo

    void preOrder(Nodo* nodo, std::vector<std::string>& result);
    void postOrder(Nodo* nodo, std::vector<std::string>& result);
    void inOrder(Nodo* nodo, std::vector<std::string>& result);
    void deleteSubtree(Nodo* nodo); //si se borra un nodo, se borran todos sus hijos y luego ese nodo.

public:
    Arbol(int k);

    bool isEmpty();
    int size();

    std::string root();

    std::string padre(std::string data);
    std::vector<std::string> hijos(std::string data);

    Nodo* insertar(Nodo* padre, std::string data);
    bool remover(std::string data);
    
    Nodo* buscar(Nodo* nodo, std::string data);

    std::vector<std::string> preOrder();
    std::vector<std::string> postOrder();
    std::vector<std::string> inOrder();


    // Uso de string& para pasar una referencia al string original.
    // Sin el &, se crearia una copia del string.
    void insertarLibro(const std::string& archivo);


    // Funciones a implementar
    std::vector<int> listar();
    // borrar_ratings(r);
    std::vector<int> precursores();
};

#endif