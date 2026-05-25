#ifndef LECTOR_XML_HPP
#define LECTOR_XML_HPP

#include <iostream>
#include <string.h>

class LectorXML {
private:
    std::string m_id;
    std::string m_titulo;
    std::string m_isbn;
    std::string m_publication_year;
    std::string m_idioma;
    std::string m_descripcion;
    std::string m_rating_promedio;
    std::string m_numero_paginas;

public:
    LectorXML(const std::string& archivo);

    std::string getId();
    std::string getTitulo();
    std::string getIsbn();
    std::string getPublicationYear();
    std::string getIdioma();
    std::string getDescripcion();
    std::string getRatingPromedio();
    std::string getNumeroPaginas();
};

#endif