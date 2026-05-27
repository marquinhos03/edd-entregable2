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

    string directorio = "books_xml"; 
    int contador_libros = 0;

    cout << "Iniciando la construccion del arbol..." << endl;

    // 1. Crear un vector para almacenar las rutas de los archivos
    vector<fs::path> archivos;

    // 2. Leer todos los archivos válidos y guardarlos en el vector
    for (const auto& entry : fs::directory_iterator(directorio)) {
        if (entry.is_regular_file() && entry.path().extension() == ".xml") {
            archivos.push_back(entry.path());
        }
    }

    // 3. Ordenar el vector de forma numérica según el nombre del archivo
    sort(archivos.begin(), archivos.end(), [](const fs::path& a, const fs::path& b) {
        return stoi(a.stem().string()) < stoi(b.stem().string());
    });

    // 4. Iterar sobre el vector ya ordenado para insertarlos en el árbol
    for (const auto& ruta : archivos) {
        try {
            miArbol.insertarLibro(ruta.string());
            contador_libros++;

            // Imprimir progreso cada 10 archivos para monitorear el rendimiento
            if (contador_libros % 10 == 0) {
                cout << "Procesados " << contador_libros << " libros..." << endl;
            }
        } catch (const exception& e) {
            cerr << "Error procesando " << ruta.string() << ": " << e.what() << endl;
        }
    }

    cout << "\nArbol construido con exito" << endl;
    cout << "Total de libros procesados: " << contador_libros << endl;
    cout << "Cantidad total de nodos en el arbol: " << miArbol.size() << endl;

    cout << "Llamada a función listar() ..." << endl;
    for (int i : miArbol.listar()) {
        cout << i << " ";
    }
        cout << endl;

    return 0;
}