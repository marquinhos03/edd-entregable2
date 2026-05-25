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

    // Guardado de datos (contemplando que un .xml puede no contener ciertos datos)
    m_id = id ? id->GetText() : "Desconocido";
    m_titulo = title ? title->GetText() : "Desconocido";
    m_isbn = isbn ? isbn->GetText() : "Desconocido";
    m_publication_year = publication_year ? publication_year->GetText() : "Desconocido";
    m_idioma = language_code ? language_code->GetText() : "Desconocido";
    m_descripcion = description ? description->GetText() : "Desconocido";
    m_rating_promedio = average_rating ? average_rating->GetText() : "Desconocido";
    m_numero_paginas = num_pages ? num_pages->GetText() : "Desconocido";
}

string LectorXML::getId() { return m_id; }
string LectorXML::getTitulo() { return m_titulo; }
string LectorXML::getIsbn() { return m_isbn; }
string LectorXML::getPublicationYear() { return m_publication_year; }
string LectorXML::getIdioma() { return m_idioma; }
string LectorXML::getDescripcion() { return m_descripcion; }
string LectorXML::getRatingPromedio() { return m_rating_promedio; }
string LectorXML::getNumeroPaginas() { return m_numero_paginas; }