#include "arbol.hpp"
#include "lector_xml.hpp"
#include <algorithm>
#include <functional>

using namespace std;

// Nodo
Arbol::Nodo::Nodo(string data, Nodo* padre) {
    m_data = data;
    m_padre = padre;
}

/**
 * @brief Constructor
 * @param k Número de hijos por nodo
 */
Arbol::Arbol(int k) {
    this->k = k;
    rootNodo = nullptr;
    treeSize = 0;
}

bool Arbol::isEmpty() {
    return treeSize == 0;
}

int Arbol::size() {
    return treeSize;
}

/**
 * @brief Retorna el dato almacenado del nodo ráíz del arbol
 */
string Arbol::root() {
    if (!rootNodo) throw runtime_error("Arbol vacío");
    return rootNodo->m_data;
}

/**
 * @brief Método que busca recursivamente un nodo que coincida con el dato especificado.
 * @param nodo El nodo desde donde comienza la búsqueda (usualmente la raiz).
 * @param data El string exacto 'm_data' del nodo que queremos encontrar.
 * @return Puntero al nodo encontrado, o nullptr si no existe en la rama.
 */
Arbol::Nodo* Arbol::buscar(Nodo* nodo, string data) {
    if (!nodo) return nullptr;

    if (nodo->m_data == data) return nodo;

    for (auto hijo : nodo->m_hijos) {
        Nodo* encontrado = buscar(hijo, data);
        if (encontrado) return encontrado;
    }

    return nullptr;
}

Arbol::Nodo* Arbol::insertar(Nodo* padre, string data) {
    // Caso base: Si el arbol esta vacío, creamos el nodo raíz.
    if (!rootNodo) {
        rootNodo = new Nodo(data);
        treeSize++;
        return rootNodo;
    }

    // Caso error: Si ya existe rootNodo y se envía padre = nullptr, se rechaza la inserción.
    if (!padre) return nullptr;

    // Caso éxito: Se realiza la inserción.
    Nodo* nuevoNodo = new Nodo(data, padre);
    padre->m_hijos.push_back(nuevoNodo);
    treeSize++;

    return nuevoNodo;
}

string Arbol::padre(string data) {
    Nodo* nodo = buscar(rootNodo, data);
    //if (!nodo || !nodo->m_padre) throw runtime_error("No tiene padre");
    if (!nodo || !nodo->m_padre) return "No tiene padre";

    return nodo->m_padre->m_data;
}

/**
 * @brief Método para ver los hijos de un nodo
 * @param data El valor almacenado de un nodo cualquiera
 */
vector<string> Arbol::hijos(string data) {
    Nodo* nodo = buscar(rootNodo, data);
    vector<string> result;

    if (!nodo) return result;

    for (auto hijo : nodo->m_hijos) {
        result.push_back(hijo->m_data);
    }

    return result;
}

void Arbol::deleteSubtree(Nodo* nodo) {
    if (!nodo) return;
    for (auto hijo : nodo->m_hijos) {
        deleteSubtree(hijo);
    }
    delete nodo;
}

// Pregunta: ¿Es eficiente usar buscar()?
// ¿Seria más eficiente pasar el nodo?
bool Arbol::remover(string data) {
    Nodo* nodo = buscar(rootNodo, data);
    if (!nodo) return false;

    if (nodo == rootNodo) {
        deleteSubtree(rootNodo);
        rootNodo = nullptr;
        treeSize = 0;
        return true;
    }

    Nodo* padre = nodo->m_padre;
    auto& siblings = padre->m_hijos;

    siblings.erase(
        remove(siblings.begin(), siblings.end(), nodo),
        siblings.end()
    );

    deleteSubtree(nodo);
    treeSize--;
    return true;
}

/**
 * @brief Método recursivo para recorrido preorder
 */
void Arbol::preOrder(Nodo* nodo, vector<string>& result) {
    if (!nodo) return;

    result.push_back(nodo->m_data);
    for (auto hijo : nodo->m_hijos) {
        preOrder(hijo, result);
    }
}

vector<string> Arbol::preOrder() {
    vector<string> result;
    preOrder(rootNodo, result);
    return result;
}

/**
 * @brief Método recursivo para recorrido postorder
 */
void Arbol::postOrder(Nodo* nodo, vector<string>& result) {
    if (!nodo) return;
    for (auto hijo : nodo->m_hijos) {
        postOrder(hijo, result);
    }
    result.push_back(nodo->m_data);
}

vector<string> Arbol::postOrder() {
    vector<string> result;
    postOrder(rootNodo, result);
    return result;
}

/**
 * @brief Método recursivo privado para el recorrido inOrder
 */
void Arbol::inOrder(Nodo* nodo, vector<string>& result) {
    if (!nodo) return;

    int half = nodo->m_hijos.size() / 2;

    for (int i = 0; i < half; i++) {
        inOrder(nodo->m_hijos[i], result);
    }

    result.push_back(nodo->m_data);

    for (size_t i = half; i < nodo->m_hijos.size(); i++) {
        inOrder(nodo->m_hijos[i], result);
    }
}

/**
 * @brief Método público para imprimir el recorrido inOrder
 */
vector<string> Arbol::inOrder() {
    vector<string> result;
    inOrder(rootNodo, result);
    return result;
}


void Arbol::insertarLibro(const string& archivo) {
    LectorXML archivoXML(archivo);

    // Insertamos el libro como hijo de la raiz
    auto nodoLibro = insertar(rootNodo, archivo);

    // DEBUG
    // cout << "Se está insertando " << archivo << endl;

    // Insertamos nodos hijos del libro
    auto nodoId = insertar(nodoLibro, "ID");
    auto nodoTitulo = insertar(nodoLibro, "Título");
    auto nodoIsbn = insertar(nodoLibro, "ISBN");
    auto nodoPublicationYear = insertar(nodoLibro, "Año de publicación");
    auto nodoIdioma = insertar(nodoLibro, "Idioma");
    auto nodoDescripcion = insertar(nodoLibro, "Descripción");
    auto nodoRatingPromedio = insertar(nodoLibro, "Rating promedio");
    auto nodoNumeroPaginas = insertar(nodoLibro, "Número de páginas");
    auto nodoLibrosSimilares = insertar(nodoLibro, "Libros similares");

    // Insertamos nodos hijos (con los datos del libro)
    insertar(nodoId, archivoXML.getId());
    insertar(nodoTitulo, archivoXML.getTitulo());
    insertar(nodoIsbn, archivoXML.getIsbn());
    insertar(nodoPublicationYear, archivoXML.getPublicationYear());
    insertar(nodoIdioma, archivoXML.getIdioma());
    insertar(nodoDescripcion, archivoXML.getDescripcion());
    insertar(nodoRatingPromedio, archivoXML.getRatingPromedio());
    insertar(nodoNumeroPaginas, archivoXML.getNumeroPaginas());
    //insertar(nodoLibrosSimilares, archivoXML.getLibrosSimilares());

    // Insertamos libros similares
    vector<LibroSimilar> librosSim = archivoXML.getLibrosSimilares();

    int contador = 1;
    for (const LibroSimilar& libroSim : librosSim) {
        auto nodoLibroSim = insertar(nodoLibrosSimilares, "Libro " + to_string(contador));

        auto nodoTituloSim = insertar(nodoLibroSim, "Título");
        auto nodoIsbnSim = insertar(nodoLibroSim, "ISBN");
        auto nodoPublicationYearSim = insertar(nodoLibroSim, "Año de publicación");

        insertar(nodoTituloSim, libroSim.m_titulo);
        insertar(nodoIsbnSim, libroSim.m_isbn);
        insertar(nodoPublicationYearSim, libroSim.m_publication_year);

        contador++;
    }
}

/**
 * @brief Listar los IDs de los libros siguiendo un recorrido preorder.
 *
 * Realiza un recorrido PreOrder buscando los nodos cuyo padre sea 'ID', en caso de encontrarlo,
 * guarda su valor como tipo entero.
 * @return vector<int> Un vector con los IDs de los libros.
 */
vector<int> Arbol::listar() {
    // result guardará los IDs
    vector<int> result;

    // Hacemos el recorrido PreOrder
    for (string s : preOrder()) {
        string str1 = padre(s);

        // Si el padre de 's' es 'ID', entonces 's' tiene almacenado el id de algun libro
        if (str1.compare("ID") == 0) {
            int id = stoi(s);
            result.push_back(id);
        }
    }

    return result;
}


/**
 *
 * @return vector<int> Un vector con los IDs de libros
 */
vector<int> Arbol::precursores() {
    vector<int> result;

    for (auto nodoLibro : rootNodo->m_hijos) {
        // PY: PublicationYear
        auto nodoPY = buscar(nodoLibro, "Año de publicación");
        string hojaDePY = nodoPY->m_hijos[0]->m_data;

        if (hojaDePY == "Desconocido") continue;

        auto nodoSimilares = buscar(nodoLibro, "Libros similares");

        bool esPrecursor = true;
        for (auto nodoSimilar : nodoSimilares->m_hijos) {
            auto nodoPYSimilar = buscar(nodoSimilar, "Año de publicación");
            string hojaDePYSimilar = nodoPYSimilar->m_hijos[0]->m_data;

            if (hojaDePYSimilar == "Desconocido") continue;
            if (stoi(hojaDePYSimilar) <= stoi(hojaDePY)) {
                esPrecursor = false;
                break;
            }
        }

        if (esPrecursor) {
            auto nodoID = buscar(nodoLibro, "ID");
            string hojaDeID = nodoID->m_hijos[0]->m_data;
            result.push_back(stoi(hojaDeID));
        }
    }

    return result;
}