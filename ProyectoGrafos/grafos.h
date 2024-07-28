#include <iostream>

using namespace std;

const int MAX_NODOS = 100; // Creamos un número máximo de nodos permitidos en el grafo
const int INF = INT_MAX; //Valor para representar la ausencia de conexión

class Grafo {
private:
    int matrizAdyacencia[MAX_NODOS][MAX_NODOS];  //Matriz de adyacencia para representar las conexiones entre nodos 
    string nodos[MAX_NODOS];
    int numNodos; // Variable como contador de nodos en el grafo

    // Busca el índice de un nodo en el arreglo de nodos
    int buscarNodo(const string& nodo) {
        for (int i = 0; i < numNodos; ++i) {
            if (nodos[i] == nodo) {
                return i;
            }
        }
        return -1; // Retorna -1 si el nodo no es encontrado
    }

public:
    // Constructor que inicia el grafo
    Grafo() : numNodos(0) {
        for (int i = 0; i < MAX_NODOS; ++i) {
            for (int j = 0; j < MAX_NODOS; ++j) {
                matrizAdyacencia[i][j] = INF; // Inicializa todas las conexiones
            }
        }
    }

    // Agrega un nuevo nodo al grafo si no existe ya y si hay espacio
    void agregarNodo(const string& nodo) {
        if (numNodos < MAX_NODOS && buscarNodo(nodo) == -1) {
            nodos[numNodos++] = nodo;
        }
    }

    // Conecta dos nodos con un peso especificado (por defecto 1)
    void conectarNodos(const string& nodo1, const string& nodo2, int peso = 1) {
        int idx1 = buscarNodo(nodo1);
        int idx2 = buscarNodo(nodo2);
        if (idx1 != -1 && idx2 != -1) {
            matrizAdyacencia[idx1][idx2] = peso; // Establece el peso de la conexión nodo1 -> nodo2 
            matrizAdyacencia[idx2][idx1] = peso; // Establece el peso de la conexión nodo2 -> nodo1 
        } else {
            cout << "Uno o ambos nodos no existen." << endl;
        }
    }

    // Elimina un nodo y todas sus conexiones del grafo 
    void eliminarNodo(const string& nodo) {
        int idx = buscarNodo(nodo);
        if (idx != -1) {
            for (int i = 0; i < numNodos; ++i) {
                matrizAdyacencia[idx][i] = INF; // Elimina conexiones del nodo eliminado 
                matrizAdyacencia[i][idx] = INF;
            }
            for (int i = idx; i < numNodos - 1; ++i) {
                nodos[i] = nodos[i + 1]; // Reorganiza el arreglo de nodos 
                for (int j = 0; j < numNodos; ++j) {
                    matrizAdyacencia[i][j] = matrizAdyacencia[i + 1][j]; // Reorganiza la matriz de adyacencia 
                    matrizAdyacencia[j][i] = matrizAdyacencia[j][i + 1];
                }
            }
            --numNodos; // Disminuye el contador de nodos 
        } else {
            cout << "El nodo no existe." << endl;
        }
    }

    // Encuentra y muestra el camino más corto entre dos nodos 
    void encontrarCaminoMasCorto(const string& inicio, const string& fin) {
        int distancias[MAX_NODOS]; // Arreglo para almacenar las distancias mínimas desde el nodo de inicio
        bool visitados[MAX_NODOS]; // Arreglo para marcar los nodos visitados 
        int predecesores[MAX_NODOS]; // Arreglo para almacenar los predecesores de cada nodo en el camino más corto 

        for (int i = 0; i < MAX_NODOS; ++i) {
            distancias[i] = INF;
            visitados[i] = false;
            predecesores[i] = -1;
        }

        int idxInicio = buscarNodo(inicio); // Índice del nodo de inicio 
        int idxFin = buscarNodo(fin); // Índice del nodo de fin 
        if (idxInicio == -1 || idxFin == -1) {
            cout << "Nodo de inicio o fin no existe." << endl;
            return;
        }

        distancias[idxInicio] = 0; // La distancia al nodo de inicio es 0 

        // Encuentra el nodo no visitado con la distancia mínima 
        for (int i = 0; i < numNodos - 1; ++i) {
            int minDistancia = INF, minIdx = -1;

            for (int j = 0; j < numNodos; ++j) {
                if (!visitados[j] && distancias[j] < minDistancia) {
                    minDistancia = distancias[j];
                    minIdx = j;
                }
            }

            if (minIdx == -1) break; // Si no se encuentra un nodo, termina el ciclo 

            visitados[minIdx] = true; // Marca el nodo como visitado 

            // Actualiza las distancias a los nodos vecinos 
            for (int j = 0; j < numNodos; ++j) {
                if (!visitados[j] && matrizAdyacencia[minIdx][j] != INF &&
                    distancias[minIdx] + matrizAdyacencia[minIdx][j] < distancias[j]) {
                    distancias[j] = distancias[minIdx] + matrizAdyacencia[minIdx][j];
                    predecesores[j] = minIdx; // Actualiza el predecesor del nodo 
                }
            }
        }

        if (distancias[idxFin] == INF) {
            cout << "No hay camino entre " << inicio << " y " << fin << endl;
            return;
        }
        // Reconstruye el camino más corto desde el nodo de fin al de inicio
        cout << "Camino mas corto de " << inicio << " a " << fin << ": ";
        int nodo = idxFin;
        string camino = "";
        while (nodo != -1) {
            camino = nodos[nodo] + " " + camino;
            nodo = predecesores[nodo];
        }
        cout << camino << "\nDistancia: " << distancias[idxFin] << endl;
    }
};