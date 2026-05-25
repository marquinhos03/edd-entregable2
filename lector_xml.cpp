#include "lector_xml.hpp"
#include "extern/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

LectorXML::LectorXML(const string& archivo) {
    XMLDocument doc;
    doc.LoadFile(archivo.c_str());

    // Acceso a la raiz
    XMLNode* root = doc.FirstChildElement("GoodreadsResponse");
    // Acceso al hijo
    XMLElement* book = root->FirstChildElement("book");

    // Acceso a hijos de book
    XMLElement* id = book->FirstChildElement("id");
    XMLElement* title = book->FirstChildElement("title");
    XMLElement* isbn = book->FirstChildElement("isbn");
    XMLElement* publication_year = book->FirstChildElement("publication_year");
    XMLElement* language_code = book->FirstChildElement("language_code");
    XMLElement* description = book->FirstChildElement("description");
    XMLElement* average_rating = book->FirstChildElement("average_rating");
    XMLElement* num_pages = book->FirstChildElement("num_pages");
    XMLElement* similar_books = book->FirstChildElement("similar_books");

    // Guardado de datos (contemplando que un .xml puede no contener ciertos datos)
    m_id = id ? id->GetText() : "Desconocido";
    m_titulo = title ? title->GetText() : "Desconocido";
    m_isbn = isbn ? isbn->GetText() : "Desconocido";
    m_publication_year = publication_year ? publication_year->GetText() : "Desconocido";
    m_idioma = language_code ? language_code->GetText() : "Desconocido";
    m_descripcion = description ? description->GetText() : "Desconocido";
    m_rating_promedio = average_rating ? average_rating->GetText() : "Desconocido";
    m_numero_paginas = num_pages ? num_pages->GetText() : "Desconocido";

    if (similar_books) {
        // Acceso al primer hijo <book> de <similar_books>
        XMLElement* sim_book = similar_books->FirstChildElement("book");

        // Iterar mientras queden <book> por revisar en <similar_books>
        while (sim_book != nullptr) {
            XMLElement* sim_book_title = sim_book->FirstChildElement("title");
            XMLElement* sim_book_isbn = sim_book->FirstChildElement("isbn");
            XMLElement* sim_book_publication_year = sim_book->FirstChildElement("publication_year");

            LibroSimilar libroSimilar;

            // Guardado de datos en el struct LibroSimilar (verificando que <tag> tenga datos almacenados)
            libroSimilar.m_titulo = (sim_book_title && sim_book_title->GetText())
                ? sim_book_title->GetText()
                : "Desconocido";
            
            libroSimilar.m_isbn = (sim_book_isbn && sim_book_isbn->GetText())
                ? sim_book_isbn->GetText()
                : "Desconocido";
            
            libroSimilar.m_publication_year = (sim_book_publication_year && sim_book_publication_year->GetText())
                ? sim_book_publication_year->GetText()
                : "Desconocido";

            // Guardado del struct LibroSimilar ya rellenado
            m_libros_similares.push_back(libroSimilar);

            // Pasar al siguiente <book>
            sim_book = sim_book->NextSiblingElement("book");
        }
    }
}

string LectorXML::getId() { return m_id; }
string LectorXML::getTitulo() { return m_titulo; }
string LectorXML::getIsbn() { return m_isbn; }
string LectorXML::getPublicationYear() { return m_publication_year; }
string LectorXML::getIdioma() { return m_idioma; }
string LectorXML::getDescripcion() { return m_descripcion; }
string LectorXML::getRatingPromedio() { return m_rating_promedio; }
string LectorXML::getNumeroPaginas() { return m_numero_paginas; }
vector<LibroSimilar> LectorXML::getLibrosSimilares() { return m_libros_similares; }