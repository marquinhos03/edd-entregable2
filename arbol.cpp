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
 * @brief Método recursivo privado para listar los IDs siguiendo un recorrido preOrder.
 *
 * Recorre el árbol verificando si el "padre" del "nodo" actual tiene el tag "ID".
 * Si lo anterior se cumple, guarda el dato almacenado (el id) del "nodo" actual como tipo entero
 *
 * @param nodo Puntero al nodo actual en la llamada recursiva.
 * @param result Referencia al vector que guarda los IDs de los libros.
 */
void Arbol::listarPreOrder(Nodo* nodo, vector<int>& result) {
    if (!nodo) return;

    // Validacion que toma O(1)
    if (nodo->m_padre != nullptr && nodo->m_padre->m_data == "ID") {
        result.push_back(stoi(nodo->m_data));
    }

    for (auto hijo : nodo->m_hijos) {
        listarPreOrder(hijo, result);
    }
}

/**
 * @brief Listar los IDs de los libros siguiendo un recorrido preOrder.
 *
 * Realiza un recorrido recursivo desde la raiz del árbol para encontrar y almacenar las hojas que almacenan
 * el "id" de un libro.
 *
 * Lo anterior toma complejidad O(n), donde n es el tamaño del arbol.
 *
 * @return vector<int> Un vector con los IDs de los libros.
 */
vector<int> Arbol::listar() {
    vector<int> result;
    listarPreOrder(rootNodo, result);
    return result;
}

/**
 * @brief Listar los IDs de libros que sólo tengan libros similares publicados en años posteriores.
 *
 * Se evalúa cada libro/archivo ".xml" en el árbol comparando su año de publicación
 * con el de sus libros similares. Si el año de publicación del libro o de un libro 
 * similar es "Desconocido", dicho libro no es considerado para la validación.
 *
 * @return vector<int> Un vector con los IDs de los libros precursores
 */
vector<int> Arbol::precursores() {
    vector<int> result;

    // Iteramos sobre cada 'libro/xml' del arbol
    for (auto nodo_libro : rootNodo->m_hijos) {
        // Buscamos la hoja que tiene guardado el año de publicacion del libro
        auto nodo_py = buscar(nodo_libro, "Año de publicación");
        string hoja_de_py = nodo_py->m_hijos[0]->m_data;

        // Si no hay registro del año de publicacion, pasamos al sig. 'libro/xml'
        if (hoja_de_py == "Desconocido") continue;

        auto nodo_similares = buscar(nodo_libro, "Libros similares");
        // flag para luego determinar si agregamos o no el id a 'result'
        bool esPrecursor = true;

        // Iteramos sobre cada 'libro similar' en 'libros similares'
        for (auto nodo_similar : nodo_similares->m_hijos) {
            // Buscamos la hoja que tiene guardado el año de publicacion del libro similar
            auto nodo_py_similar = buscar(nodo_similar, "Año de publicación");
            string hoja_de_py_similar = nodo_py_similar->m_hijos[0]->m_data;

            // Si no hay registro del año de publicacion, pasamos al sig. 'libro similar'
            if (hoja_de_py_similar == "Desconocido") continue;

            // Si el 'año de publicación' del 'libro similar' es menor o igual al 'año de publicación' del 'libro',
            // entonces 'libro similar' no es posterior a 'libro', y salimos del bucle de 'libros similares'.
                if (stoi(hoja_de_py_similar) <= stoi(hoja_de_py)) {
                esPrecursor = false;
                break;
            }
        }

        // Si esPrecursor = true, entonces guardamos el 'id' del 'libro/xml' en 'result'
        // En caso contrario, no hacemos nada y pasamos al sig. 'libro/xml'
        if (esPrecursor) {
            auto nodo_id = buscar(nodo_libro, "ID");
            string hoja_de_id = nodo_id->m_hijos[0]->m_data;
            result.push_back(stoi(hoja_de_id));
        }
    }

    return result;
}

/**
 * @brief Elimina del árbol todos los libros con un rating promedio menor o igual a r.
 * @param r El valor máximo de rating para que un libro sea eliminado.
 */
void Arbol::borrar_ratings(float r) {
    if (!rootNodo || rootNodo->m_hijos.empty()) return;

    auto& libros = rootNodo->m_hijos;

    // Iteramos de atrás hacia adelante para poder eliminar elementos del vector de forma segura
    for (int i = libros.size() - 1; i >= 0; --i) {
        Nodo* nodo_libro = libros[i];

        // Buscamos el nodo que almacena el rating
        Nodo* nodo_rating = buscar(nodo_libro, "Rating promedio");

        // Verificamos que el nodo exista y tenga un hijo con el dato numérico
        if (nodo_rating && !nodo_rating->m_hijos.empty()) {
            string string_rating = nodo_rating->m_hijos[0]->m_data;

            // Ignoramos los libros que no tienen registro del rating
            if (string_rating != "Desconocido") {
                // Convertimos el string a float para la comparación
                float rating_actual = stof(string_rating);

                if (rating_actual <= r) {
                    // 1. Borramos todos los nodos descendientes y el nodo del libro
                    deleteSubtree(nodo_libro);
                    
                    // 2. Lo quitamos del vector de hijos de la raíz
                    libros.erase(libros.begin() + i);
                    
                    // 3. Ajustamos el contador del árbol
                    // Nota: Si quieres que treeSize sea exacto, deberías restar 
                    // la cantidad total de nodos que conformaban este libro.
                    treeSize--; 
                }
            }
        }
    }
}