// Compilación: g++ abc.cpp extern/tinyxml2.cpp
// Ejecución ./a.out

#include <iostream>
#include "extern/tinyxml2.h"

using namespace std;
using namespace tinyxml2;

int main() {
    XMLDocument doc;
    doc.LoadFile("1.xml");

    // Acceso a la raiz
    XMLNode* root = doc.FirstChildElement("GoodreadsResponse");
    // Acceso al hijo
    XMLElement* book = root->FirstChildElement("book");

    // Acceso al valor del texto
    const char* title = book->FirstChildElement("title")->GetText();

    cout << "Titulo: " << title << endl;

    return 0;
}