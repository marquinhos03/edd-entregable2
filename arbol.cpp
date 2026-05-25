#include "arbol.hpp"
#include <algorithm>
#include <functional>

// Nodo
Arbol::Nodo::Nodo(string data, Nodo* padre) {
    m_data = data;
    m_padre = padre;
}

/**
 * @brief Constructor
 * @param k Número de hijos por nodo
 */
Arbol::Arbol(int k) {
    this->k = k;
    rootNodo = nullptr;
    treeSize = 0;
}

bool Arbol::isEmpty() {
    return treeSize == 0;
}

int Arbol::size() {
    return treeSize;
}

/**
 * @brief Retorna el nodo ráíz del arbol
 */
Arbol::Nodo* Arbol::raiz() {
    if (!rootNodo) throw runtime_error("Arbol vacío");
    return rootNodo;
}

 // string Arbol::raiz() {
//     if (!rootNodo) throw runtime_error("Arbol vacío");
//     return rootNodo->m_data;
// }

Arbol::Nodo* Arbol::buscar(Nodo* nodo, string data) {
    if (!nodo) return nullptr;

    if (nodo->m_data == data) return nodo;

    for (auto hijo : nodo->m_hijos) {
        Nodo* encontrado = buscar(hijo, data);
        if (encontrado) return encontrado;
    }

    return nullptr;
}

Arbol::Nodo* Arbol::insertar(Nodo* padre, string data) {
    // Caso base: Si el arbol esta vacío, creamos el nodo raíz.
    if (!rootNodo) {
        rootNodo = new Nodo(data);
        treeSize++;
        return rootNodo;
    }

    // Caso error: Si ya existe rootNodo y se envía padre = nullptr,
    // se rechaza la inserción.
    if (!padre) return nullptr;

    // Caso éxito: Se realiza la inserción.
    Nodo* nuevoNodo = new Nodo(data, padre);
    padre->m_hijos.push_back(nuevoNodo);
    treeSize++;

    return nuevoNodo;
}

/**
 * @brief Método para ver los hijos de un nodo
 * @param data El valor almacenado de un nodo cualquiera
 */
vector<string> Arbol::hijos(string data) {
    Nodo* nodo = buscar(rootNodo, data);
    vector<string> result;

    if (!nodo) return result;

    for (auto hijo : nodo->m_hijos) {
        result.push_back(hijo->m_data);
    }

    return result;
}

/**
 * @brief Método recursivo para recorrido preorder
 */
void Arbol::preOrder(Nodo* nodo, vector<string>& result) {
    if (!nodo) return;

    result.push_back(nodo->m_data);
    for (auto hijo : nodo->m_hijos) {
        preOrder(hijo, result);
    }
}

vector<string> Arbol::preOrder() {
    vector<string> result;
    preOrder(rootNodo, result);
    return result;
}