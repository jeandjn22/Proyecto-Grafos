#include <iostream>
#include <cstring>
#include <climits>
#include "./grafos.h"

using namespace std;


int main() {
    Grafo grafo;
    grafo.agregarNodo("A");
    grafo.agregarNodo("B");
    grafo.agregarNodo("C");
    grafo.agregarNodo("D");
    grafo.agregarNodo("E");

    grafo.conectarNodos("A", "B", 1);
    grafo.conectarNodos("A", "C", 1);
    grafo.conectarNodos("B", "C", 1);
    grafo.conectarNodos("B", "D", 1);
    grafo.conectarNodos("C", "D", 1);
    grafo.conectarNodos("D", "E", 1);

    grafo.encontrarCaminoMasCorto("A", "E");

    grafo.eliminarNodo("C");
    cout << "Grafo despues de eliminar el nodo 'C':\n";
    grafo.encontrarCaminoMasCorto("A", "E");

    return 0;
}
