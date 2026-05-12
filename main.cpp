// Compilación:  g++ main.cpp extern/tinyxml2.cpp arbol.cpp
// Ejecucion: ./a.out

#include <iostream>
#include "extern/tinyxml2.h"
#include "arbol.hpp"

using namespace std;
using namespace tinyxml2;

struct InfoTag {
    const char* xml_tag;    // tag en el archivo xml
    const char* nodo_tag;   // nombre del nodo en el árbol
};

namespace Tags {
    constexpr InfoTag ROOT = { "GoodreadsResponse", "Raíz" };
    constexpr InfoTag LIBRO = { "book", "Libro" };
    constexpr InfoTag ID = { "id", "ID" };
    constexpr InfoTag TITULO = { "title", "Título" };
    constexpr InfoTag ISBN = { "isbn", "ISBN" };
    constexpr InfoTag AAAA_PUBLICACION = { "publication_year", "Año de publicación" };
    constexpr InfoTag IDIOMA = { "language_code", "Idioma" };
    constexpr InfoTag DESCRIPCION = { "description", "Descripción" };
    constexpr InfoTag RATING_PROMEDIO = { "average_rating", "Rating promedio" };
    constexpr InfoTag NUMERO_PAGINAS = { "num_pages", "Número de páginas" };
};

int main() {
    XMLDocument doc;
    doc.LoadFile("1.xml");

    // Acceso a la raiz
    XMLNode* root = doc.FirstChildElement(Tags::ROOT.xml_tag);
    // Acceso al hijo
    XMLElement* book = root->FirstChildElement(Tags::LIBRO.xml_tag);

    // Acceso a hijos de book
    XMLElement* id = book->FirstChildElement(Tags::ID.xml_tag);

    XMLElement* title = book->FirstChildElement(Tags::TITULO.xml_tag);
    XMLElement* isbn = book->FirstChildElement(Tags::ISBN.xml_tag);
    XMLElement* publication_year = book->FirstChildElement(Tags::AAAA_PUBLICACION.xml_tag);
    XMLElement* language_code = book->FirstChildElement(Tags::IDIOMA.xml_tag);
    XMLElement* description = book->FirstChildElement(Tags::DESCRIPCION.xml_tag);
    XMLElement* average_rating = book->FirstChildElement(Tags::RATING_PROMEDIO.xml_tag);
    XMLElement* num_pages = book->FirstChildElement(Tags::NUMERO_PAGINAS.xml_tag);

    Arbol miArbol(6);

    miArbol.insertar("", Tags::ROOT.nodo_tag);

    miArbol.insertar(Tags::ROOT.nodo_tag, Tags::LIBRO.nodo_tag);
    miArbol.insertar(Tags::LIBRO.nodo_tag, Tags::ID.nodo_tag);
    miArbol.insertar(Tags::LIBRO.nodo_tag, Tags::TITULO.nodo_tag);
    miArbol.insertar(Tags::LIBRO.nodo_tag, Tags::ISBN.nodo_tag);
    miArbol.insertar(Tags::LIBRO.nodo_tag, Tags::AAAA_PUBLICACION.nodo_tag);
    miArbol.insertar(Tags::LIBRO.nodo_tag, Tags::IDIOMA.nodo_tag);
    //miArbol.insertar(Tags::LIBRO.nodo_tag, Tags::DESCRIPCION.nodo_tag);
    miArbol.insertar(Tags::LIBRO.nodo_tag, Tags::RATING_PROMEDIO.nodo_tag);
    miArbol.insertar(Tags::LIBRO.nodo_tag, Tags::NUMERO_PAGINAS.nodo_tag);

    miArbol.insertar(Tags::ID.nodo_tag, id->GetText());
    miArbol.insertar(Tags::TITULO.nodo_tag, title->GetText());
    miArbol.insertar(Tags::ISBN.nodo_tag, isbn->GetText());
    miArbol.insertar(Tags::AAAA_PUBLICACION.nodo_tag, publication_year->GetText());
    miArbol.insertar(Tags::IDIOMA.nodo_tag, language_code->GetText());
    //miArbol.insertar(Tags::DESCRIPCION.nodo_tag, description->GetText());
    miArbol.insertar(Tags::RATING_PROMEDIO.nodo_tag, average_rating->GetText());
    miArbol.insertar(Tags::NUMERO_PAGINAS.nodo_tag, num_pages->GetText());

    cout << "Tamaño: " << miArbol.size() << endl;

    cout << "PreOrder: ";
    for (string s : miArbol.preOrder()) {
        cout << s << " ";
    }
    cout << endl;

    return 0;
}