// Compilación: g++ pruebas.cpp extern/tinyxml2.cpp arbol.cpp lector_xml.cpp
// Ejecucion: ./a.out (En windows .\a.exe)
#include <iostream>
#include <vector>
#include <algorithm>
#include "arbol.hpp"

using namespace std;

int main() {
    // Inicializamos el árbol
    Arbol miArbol(1000);
    auto raiz = miArbol.insertar(nullptr, "Raiz Libros");

    // rating = 4.54
    miArbol.insertarLibro("books_xml/1.xml");
    cout << "Cantidad de nodos tras insertar 1er libro: " << miArbol.size() << endl;
    // rating = 4.46
    miArbol.insertarLibro("books_xml/2.xml");
    cout << "Cantidad de nodos tras insertar 2do libro: " << miArbol.size() << endl;
    // rating = 4.44
    miArbol.insertarLibro("books_xml/3.xml");
    cout << "Cantidad de nodos tras insertar 3er libro: " << miArbol.size() << endl;

    cout << "\nArbol generado con éxito" << endl;
    cout << "Total de libros procesados: " << 3 << endl;
    cout << "Cantidad total de nodos en el arbol: " << miArbol.size() << endl;

    cout << "Llamada a funcion listar() ..." << endl;
    for (int i : miArbol.listar()) {
        cout << i << " ";
    }
    cout << endl;

    // Borramos libros con rating <= 4.45
    float r = 4.45f; 
    cout << "Llamada a funcion borrar_ratings(" << r << ") ..." << endl;

    miArbol.borrar_ratings(r);

    cout << "Se han eliminado todos los libros con rating promedio <= " << r << "..." << endl;
    
    cout << "Cantidad total de nodos en el árbol luego del borrado: " << miArbol.size() << endl;
    
    cout << "Llamada a funcion listar() luego del borrado ..." << endl;
    for (int i : miArbol.listar()) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}