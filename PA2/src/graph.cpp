#include <iostream>
#include "graph.hpp"
#include "listaadjacencia.hpp"

using namespace std;
 
Grafo::Grafo() {
    
}

Grafo::~Grafo() {
    
}

void Grafo::InsereVertice() {
    vertices.insereVertice();
}

void Grafo::InsereAresta(int v, int w) {
    vertices.insereAresta(v, w);
}

int Grafo::QuantidadeVertices() {
    return vertices.quantidadeVertices();
}

int Grafo::QuantidadeArestas() {
    return vertices.quantidadeArestas();
}

int Grafo::GrauMinimo() {
    return vertices.grauMinimo();
}

int Grafo::GrauMaximo() {
    return vertices.grauMaximo();
}

void Grafo::ImprimeVizinhos(int v) {
    vertices.imprimeVizinhos(v);
}
