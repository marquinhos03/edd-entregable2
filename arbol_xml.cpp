#include "arbol.hpp"
#include "extern/tinyxml2.h"

using namespace tinyxml2;

struct InfoTag {
    const char* xml_tag;    // tag en el archivo xml
    const char* nodo_tag;   // nombre del nodo en el árbol
};

namespace Tags {
    constexpr InfoTag ROOT = { "GoodreadsResponse", "Raíz Libros" };
    constexpr InfoTag LIBRO = { "book", "Libro" };
    constexpr InfoTag ID = { "id", "ID" };
    constexpr InfoTag TITULO = { "title", "Título" };
    constexpr InfoTag ISBN = { "isbn", "ISBN" };
    constexpr InfoTag PUBLICATION_YEAR = { "publication_year", "Año de publicación" };
    constexpr InfoTag IDIOMA = { "language_code", "Idioma" };
    constexpr InfoTag DESCRIPCION = { "description", "Descripción" };
    constexpr InfoTag RATING_PROMEDIO = { "average_rating", "Rating promedio" };
    constexpr InfoTag NUMERO_PAGINAS = { "num_pages", "Número de páginas" };
};

void Arbol::insertarLibro(const string& archivo) {
    XMLDocument doc;
    doc.LoadFile(archivo.c_str());

    // Acceso a la raiz
    XMLNode* root = doc.FirstChildElement(Tags::ROOT.xml_tag);
    // Acceso al hijo
    XMLElement* book = root->FirstChildElement(Tags::LIBRO.xml_tag);

    // Acceso a hijos de book
    XMLElement* id = book->FirstChildElement(Tags::ID.xml_tag);
    XMLElement* title = book->FirstChildElement(Tags::TITULO.xml_tag);
    XMLElement* isbn = book->FirstChildElement(Tags::ISBN.xml_tag);
    XMLElement* publication_year = book->FirstChildElement(Tags::PUBLICATION_YEAR.xml_tag);
    XMLElement* language_code = book->FirstChildElement(Tags::IDIOMA.xml_tag);
    XMLElement* description = book->FirstChildElement(Tags::DESCRIPCION.xml_tag);
    XMLElement* average_rating = book->FirstChildElement(Tags::RATING_PROMEDIO.xml_tag);
    XMLElement* num_pages = book->FirstChildElement(Tags::NUMERO_PAGINAS.xml_tag);

    auto libro = insertar(raiz(), archivo);

    auto nodoId = insertar(libro, Tags::ID.nodo_tag);
    auto nodoTitulo = insertar(libro, Tags::TITULO.nodo_tag);
    auto nodoIsbn = insertar(libro, Tags::ISBN.nodo_tag);
    auto nodoPublicationYear = insertar(libro, Tags::PUBLICATION_YEAR.nodo_tag);
    auto nodoIdioma = insertar(libro, Tags::IDIOMA.nodo_tag);
    //auto nodoDescripcion = insertar(libro, Tags::DESCRIPCION.nodo_tag);
    auto nodoRatingPromedio = insertar(libro, Tags::RATING_PROMEDIO.nodo_tag);
    auto nodoNumeroPaginas = insertar(libro, Tags::NUMERO_PAGINAS.nodo_tag);

    insertar(nodoId, id->GetText());
    insertar(nodoTitulo, title->GetText());
    insertar(nodoIsbn, isbn->GetText());
    insertar(nodoPublicationYear, publication_year->GetText());
    insertar(nodoIdioma, language_code->GetText());
    //insertar(nodoDescripcion, id->GetText());
    insertar(nodoRatingPromedio, average_rating->GetText());
    insertar(nodoNumeroPaginas, num_pages->GetText());
}