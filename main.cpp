// Compilación: g++ main.cpp extern/tinyxml2.cpp arbol.cpp arbol_xml.cpp
// Ejecucion: ./a.out
#include <iostream>
#include "arbol.hpp"

using namespace std;

int main() {
    Arbol miArbol(6);

    auto raiz = miArbol.insertar(nullptr, "Raíz Libros");

    miArbol.insertarLibro("1.xml");
    miArbol.insertarLibro("2.xml");

    cout << "Tamaño: " << miArbol.size() << endl;

    cout << "PreOrder: ";
    for (string s : miArbol.preOrder()) {
        cout << s << " ";
    }
    cout << endl;


    return 0;
}