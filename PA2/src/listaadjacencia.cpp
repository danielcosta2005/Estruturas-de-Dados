#include <iostream> 
#include "listaadjacencia.hpp"

using namespace std;

ListaAdjacencia::ListaAdjacencia(){
    head=nullptr;
    tail=nullptr;
    nArestas=0;
    nVertices=0;
}


ListaAdjacencia::~ListaAdjacencia() {
    Vertice* current = head;

    while (current != nullptr) {
        Vizinho* vizinho = current->headListaVizinhos;
        while (vizinho != nullptr) {
            Vizinho* tempVizinho = vizinho;
            vizinho = vizinho->next;
            delete tempVizinho;
        }

        Vertice* tempVertice = current;
        current = current->next;
        delete tempVertice;
    }

    head = nullptr;
    tail = nullptr;
    nArestas = 0;
    nVertices = 0;
}

void ListaAdjacencia::insereVertice(){
    Vertice* novoVertice;
    novoVertice = new Vertice();
    novoVertice->id = nVertices;
    novoVertice->headListaVizinhos = nullptr;
    novoVertice->tailListaVizinhos = nullptr;
    novoVertice->next = nullptr;

    if (head == nullptr) {
        head = novoVertice;
        tail = novoVertice;
    } else {
        tail->next = novoVertice;
        tail = novoVertice;
    }

    nVertices++;
}

void ListaAdjacencia::adicionaVizinho(Vertice *vertice, int idVizinho){
    Vizinho* novoVizinho;
    novoVizinho = new Vizinho();
    novoVizinho->id = idVizinho;
    novoVizinho->next = nullptr;

    if (vertice->headListaVizinhos == nullptr){
        vertice->headListaVizinhos = novoVizinho;
        vertice->tailListaVizinhos = novoVizinho;
    }

    else {
        vertice->tailListaVizinhos->next = novoVizinho;
        vertice->tailListaVizinhos = novoVizinho;
    }
}

Vertice* ListaAdjacencia::buscaVertice(int v){
    Vertice* current = head;
    
    while (current != nullptr && current->id != v){
        current = current->next;
    }

    return current;
}

void ListaAdjacencia::insereAresta(int v, int w){
    Vertice* verticeV = buscaVertice(v);
    Vertice* verticeW = buscaVertice(w);

    if (verticeV != nullptr && verticeW != nullptr) {
        adicionaVizinho(verticeV, w);
        adicionaVizinho(verticeW, v);
        nArestas++; 
    }
}

void ListaAdjacencia::imprimeVizinhos(int v){
    Vertice* vertice = buscaVertice(v);

    if (vertice != nullptr){
        Vizinho* current = vertice->headListaVizinhos;
    while (current != nullptr){
        cout << current->id << " ";
        current = current->next;
    }
    cout << endl;
    }
}

int ListaAdjacencia::nVizinhos(Vertice* vertice){
    int nVizinhos = 0;
    Vizinho* current = vertice->headListaVizinhos;
    while (current != nullptr){
        nVizinhos++;
        current = current->next;
    }
    return nVizinhos;
}

int ListaAdjacencia::grauMaximo(){
    Vertice* current = head;
    int grauMax = 0;

    while (current != nullptr){
        int grauCurrent = nVizinhos(current);
        if (grauCurrent > grauMax){
            grauMax = grauCurrent;
        }
        current = current->next;
    }
    return grauMax;
}

int ListaAdjacencia::grauMinimo(){
    if (head == nullptr){
        return 0;
    }

    Vertice* current = head;
    int grauMin = nVizinhos(current);

    while (current != nullptr){
        int grauCurrent = nVizinhos(current);
        if(grauCurrent < grauMin){
            grauMin = grauCurrent;
        }
        current = current->next;
    }
    return grauMin;
}

int ListaAdjacencia::quantidadeArestas(){
    return nArestas;
}

int ListaAdjacencia::quantidadeVertices(){
    return nVertices;
}

