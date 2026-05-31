// Compilación: g++ main.cpp extern/tinyxml2.cpp arbol.cpp lector_xml.cpp
// Ejecucion: ./a.out (En windows .\a.exe)
#include <iostream>
#include <filesystem>
#include <vector>
#include <algorithm>
#include "arbol.hpp"

namespace fs = std::filesystem;
using namespace std;

int main() {
    // Inicializamos el árbol
    Arbol miArbol(1000);
    auto raiz = miArbol.insertar(nullptr, "Raiz Libros");

    // GENERADO CON GEMINI

    string dir = "books_xml";
    vector<fs::path> archivos;
    int contador_libros = 0;

    // 1. Recopilar todos los archivos .xml
    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_regular_file() && entry.path().extension() == ".xml") {
            archivos.push_back(entry.path());
        }
    }

    // 2. Ordenar numéricamente (1, 2, 3... 10, 11)
    sort(archivos.begin(), archivos.end(), [](const fs::path& a, const fs::path& b) {
        // .stem() obtiene el nombre sin extensión (ej. "10" en lugar de "10.xml")
        int numA = stoi(a.stem().string());
        int numB = stoi(b.stem().string());
        return numA < numB;
    });

    // 3. Procesar en orden
    cout << "INICIANDO LA CONSTRUCCIÓN DEL ÁRBOL" << endl;
    for (const auto& archivo : archivos) {
        //cout << "Se esta insertando " << archivo.string() << endl;
        miArbol.insertarLibro(archivo.string());
        contador_libros++;

        // Imprimir progreso cada 1000 archivos para monitorear el rendimiento
        if (contador_libros % 1000 == 0) {
            cout << "Insertados " << contador_libros << " libros ..." << endl;
        }
    }
    cout << endl;

    // FIN GENERADO CON GEMINI

    cout << "ÁRBOL CONSTRUIDO CON ÉXITO " << endl;
    cout << "Total de libros procesados: " << contador_libros << endl;
    cout << "Total de nodos en el árbol: " << miArbol.size() << endl;
    cout << endl;

    // FUNCIÓN LISTAR
    cout << "Llamada a función listar() ..." << endl;
    for (int i : miArbol.listar()) {
        cout << i << " ";
    }
    cout << endl << endl;

    // FUNCIÓN PRECURSORES
    cout << "Llamada a funcion precursores() ..." << endl;
    for (int i : miArbol.precursores()) {
        cout << i << " ";
    }
    cout << endl << endl;

    // FUNCIÓN BORRAR_RATINGS
    // Borramos libros con rating <= 4.45
    float r = 4.45f;

    cout << "Llamada a funcion borrar_ratings(" << r << ") ..." << endl << endl;
    miArbol.borrar_ratings(r);
    
    cout << "Total de nodos luego del borrado: " << miArbol.size() << endl;
    
    cout << "Llamada a funcion listar() luego del borrado ..." << endl;
    for (int i : miArbol.listar()) {
        cout << i << " ";
    }
    cout << endl;

    return 0;
}