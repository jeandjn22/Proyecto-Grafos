#include <iostream>

using namespace std;

const int MAX_NODOS = 100; // Creamos un número máximo de nodos permitidos en el grafo
const int INF = INT_MAX;

class Grafo {
private:
    int matrizAdyacencia[MAX_NODOS][MAX_NODOS];  //Matriz de adyacencia para representar las conexiones entre nodos 
    string nodos[MAX_NODOS];
    int numNodos;

    int buscarNodo(const string& nodo) {
        for (int i = 0; i < numNodos; ++i) {
            if (nodos[i] == nodo) {
                return i;
            }
        }
        return -1;
    }

public:
    Grafo() : numNodos(0) {
        for (int i = 0; i < MAX_NODOS; ++i) {
            for (int j = 0; j < MAX_NODOS; ++j) {
                matrizAdyacencia[i][j] = INF;
            }
        }
    }

    void agregarNodo(const string& nodo) {
        if (numNodos < MAX_NODOS && buscarNodo(nodo) == -1) {
            nodos[numNodos++] = nodo;
        }
    }

    void conectarNodos(const string& nodo1, const string& nodo2, int peso = 1) {
        int idx1 = buscarNodo(nodo1);
        int idx2 = buscarNodo(nodo2);
        if (idx1 != -1 && idx2 != -1) {
            matrizAdyacencia[idx1][idx2] = peso;
            matrizAdyacencia[idx2][idx1] = peso;
        } else {
            cout << "Uno o ambos nodos no existen." << endl;
        }
    }

    void eliminarNodo(const string& nodo) {
        int idx = buscarNodo(nodo);
        if (idx != -1) {
            for (int i = 0; i < numNodos; ++i) {
                matrizAdyacencia[idx][i] = INF;
                matrizAdyacencia[i][idx] = INF;
            }
            for (int i = idx; i < numNodos - 1; ++i) {
                nodos[i] = nodos[i + 1];
                for (int j = 0; j < numNodos; ++j) {
                    matrizAdyacencia[i][j] = matrizAdyacencia[i + 1][j];
                    matrizAdyacencia[j][i] = matrizAdyacencia[j][i + 1];
                }
            }
            --numNodos;
        } else {
            cout << "El nodo no existe." << endl;
        }
    }

    void encontrarCaminoMasCorto(const string& inicio, const string& fin) {
        int distancias[MAX_NODOS];
        bool visitados[MAX_NODOS];
        int predecesores[MAX_NODOS];

        for (int i = 0; i < MAX_NODOS; ++i) {
            distancias[i] = INF;
            visitados[i] = false;
            predecesores[i] = -1;
        }

        int idxInicio = buscarNodo(inicio);
        int idxFin = buscarNodo(fin);
        if (idxInicio == -1 || idxFin == -1) {
            cout << "Nodo de inicio o fin no existe." << endl;
            return;
        }

        distancias[idxInicio] = 0;

        for (int i = 0; i < numNodos - 1; ++i) {
            int minDistancia = INF, minIdx = -1;

            for (int j = 0; j < numNodos; ++j) {
                if (!visitados[j] && distancias[j] < minDistancia) {
                    minDistancia = distancias[j];
                    minIdx = j;
                }
            }

            if (minIdx == -1) break;

            visitados[minIdx] = true;

            for (int j = 0; j < numNodos; ++j) {
                if (!visitados[j] && matrizAdyacencia[minIdx][j] != INF &&
                    distancias[minIdx] + matrizAdyacencia[minIdx][j] < distancias[j]) {
                    distancias[j] = distancias[minIdx] + matrizAdyacencia[minIdx][j];
                    predecesores[j] = minIdx;
                }
            }
        }

        if (distancias[idxFin] == INF) {
            cout << "No hay camino entre " << inicio << " y " << fin << endl;
            return;
        }

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