#include <iostream>
#include <cstring>
#include <climits>  // Usamos la biblioteca climits para usar INT_MAX
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
    grafo.conectarNodos("C", "E", 1);

    // Encuentra y muestra el camino más corto de A a E
    grafo.encontrarCaminoMasCorto("A", "E");

    // Elimina el nodo C y muestra el estado del grafo 
    grafo.eliminarNodo("C");
    cout << "Grafo despues de eliminar el nodo 'C':\n";
    grafo.encontrarCaminoMasCorto("A", "E");

    cout<<" "<<endl;

    //Encuentra y muestra el camino mas corto de E a B
    grafo.encontrarCaminoMasCorto("E", "B");
    grafo.agregarNodo("C"); //Agregamos de nuevo el nodo C

    // Elimina el nodo D y muestra el estado actual del grafo 
    grafo.eliminarNodo("D");
    cout << "Grafo despues de eliminar el nodo 'D':\n";
    grafo.encontrarCaminoMasCorto("A", "D");


    return 0;
}

