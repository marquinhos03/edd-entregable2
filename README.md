# Entregable 2: XML

## Integrantes
- Matías Cuello
- Marco Liguempi

## Sobre el árbol

Se adjunta una imágen con la **idea** para la representación del [**Árbol de Libros/XML**](https://raw.githubusercontent.com/marquinhos03/edd-entregable2/refs/heads/main/idea-arbol-libros.png), donde se uso como guía el diseño del XML de **customers** mencionado en el enunciado del entregable.

## 💻 Instalación, compilación y ejecución

### 1. Clonar el repositorio

```
git clone https://github.com/marquinhos03/edd-entregable2.git
cd edd-entregable2 
```

### 2. Compilación

#### 2.1 Con Makefile
```
make
```
#### 2.2 Sin Makefile
```
g++ main.cpp extern/tinyxml2.cpp arbol.cpp lector_xml.cpp -o main
```
**Nota:** para ambos casos, el nombre del ejecutable será el mismo.

### 3. Ejecución
```
./main
```
