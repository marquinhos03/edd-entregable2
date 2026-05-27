// Compilación: g++ main.cpp extern/tinyxml2.cpp arbol.cpp lector_xml.cpp
// Ejecucion: ./a.out (En windows .\a.exe)
#include <iostream>
#include <filesystem>
#include "arbol.hpp"

namespace fs = std::filesystem;
using namespace std;

int main() {
    // Inicializamos el árbol
    Arbol miArbol(1000); 
    auto raiz = miArbol.insertar(nullptr, "Raiz Libros");

    string directorio = "books_xml"; 
    int contador_libros = 0;

    cout << "Iniciando la construccion del arbol..." << endl;

    // miArbol.insertarLibro("books_xml/1.xml");
    // miArbol.insertarLibro("books_xml/2.xml");
    // miArbol.insertarLibro("books_xml/3.xml");
    // miArbol.insertarLibro("books_xml/5.xml");
    // miArbol.insertarLibro("books_xml/6.xml");
    // miArbol.insertarLibro("books_xml/8.xml");
    // miArbol.insertarLibro("books_xml/10.xml");
    // miArbol.insertarLibro("books_xml/11.xml");
    // miArbol.insertarLibro("books_xml/13.xml");

    // Iteramos sobre todos los archivos del directorio
    for (const auto& entry : fs::directory_iterator(directorio)) {
        // Verificamos que sea un archivo regular y tenga extensión .xml
        if (entry.is_regular_file() && entry.path().extension() == ".xml") {
            try {
                miArbol.insertarLibro(entry.path().string());
                contador_libros++;

                // Imprimir progreso cada 500 archivos para monitorear el rendimiento
                if (contador_libros % 500 == 0) {
                    cout << "Procesados " << contador_libros << " libros..." << endl;
                }
            } catch (const exception& e) {
                cerr << "Error procesando " << entry.path().string() << ": " << e.what() << endl;
            }
        }
    }

    cout << "\nArbol construido con exito" << endl;
    cout << "Total de libros procesados: " << contador_libros << endl;
    cout << "Cantidad total de nodos en el arbol: " << miArbol.size() << endl;

    // cout << "PreOrder: " << endl;
    // for (string s : miArbol.preOrder()) {
    //     cout << s << endl;
    // }
    // cout << endl;

    cout << "Llamada a función listar() ..." << endl;
    for (int i : miArbol.listar()) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}