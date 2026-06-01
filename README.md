# Entregable 2: XML

## Integrantes
- Matías Cuello
- Marco Liguempi

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
