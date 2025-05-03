#include <iostream>
#include <string>
#include "graph.hpp" 

using namespace std;

int main(int argc, char* argv[]) {
    if (argc != 2) {
        return 1;
    }

    string operacao = argv[1]; 
    Grafo grafo;

    int n;
    cin >> n;

    for (int i = 0; i < n; i++) {
        grafo.InsereVertice();
    }

    for (int i = 0; i < n; i++) {
        int m;
        cin >> m;
        for (int j = 0; j < m; j++) {
            int vizinho;
            cin >> vizinho;
            if (i < vizinho) { 
                grafo.InsereAresta(i, vizinho);
            }
        }
    }

    if (operacao == "-d") {
        cout << grafo.QuantidadeVertices() << endl;
        cout << grafo.QuantidadeArestas() << endl;
        cout << grafo.GrauMinimo() << endl;
        cout << grafo.GrauMaximo() << endl;
    } 
    else if (operacao == "-n") {
        for (int i = 0; i < grafo.QuantidadeVertices(); i++) {
            grafo.ImprimeVizinhos(i);
        }
    }
    else if (operacao == "-k") {
        if (grafo.GrauMaximo() == grafo.GrauMinimo()){
            cout << "1" << endl;
        }
        else {
            cout << "0" << endl;
        }
    }

    return 0;
}
