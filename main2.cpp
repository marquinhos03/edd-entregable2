// Compilación: g++ main2.cpp extern/tinyxml2.cpp arbol.cpp
// Ejecucion: ./a.out

#include <iostream>
#include "arbol.hpp"

using namespace std;

int main() {
    Arbol miArbol(6);

    auto raiz = miArbol.insertar(nullptr, "(Raíz Libros)");

    miArbol.insertarLibro("1.xml");
    miArbol.insertarLibro("2.xml");

    // auto libro1 = miArbol.insertar(raiz, "(Libro 1)");
    // auto libro2 = miArbol.insertar(raiz, "(Libro 2)");

    // auto id1 = miArbol.insertar(libro1, "(id)");
    // auto id2 = miArbol.insertar(libro2, "(id)");

    // auto titulo1 = miArbol.insertar(libro1, "(titulo)");
    // auto titulo2 = miArbol.insertar(libro2, "(titulo)");

    // miArbol.insertar(id1, "(1)");
    // miArbol.insertar(id2, "(2)");

    // miArbol.insertar(titulo1, "(Harry Potter 1)");
    // miArbol.insertar(titulo2, "(Harry Potter 2)");

    cout << "Tamaño: " << miArbol.size() << endl;

    cout << "PreOrder: ";
    for (string s : miArbol.preOrder()) {
        cout << s << " ";
    }
    cout << endl;


    return 0;
}