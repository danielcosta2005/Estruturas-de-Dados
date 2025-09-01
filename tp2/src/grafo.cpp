#include "grafo.hpp"
#include <stdexcept>

struct Par {
    int destino;
    int anterior;

    Par(int d, int a) : destino(d), anterior(a) {}
};// Será importante na busca em largura para guardar cada (vizinho, anterior) encontrado

void Grafo::adicionarArmazem(int idArmazem) {
    // Não adiciona duplicado
    if (buscaArmazem(idArmazem) != nullptr) return;

    Vertice novo;
    novo.armazem = new Armazem(idArmazem);
    vertices.pushBack(novo);
}

Armazem* Grafo::buscaArmazem(int id) {
    Node<Vertice>* atual = vertices.getHead();
    while (atual) {
        if (atual->dado.armazem->getId() == id) {
            return atual->dado.armazem;
        }
        atual = atual->next;
    }
    return nullptr;
}

void Grafo::adicionaVizinho(Armazem* armazem, int idVizinho) {
    Node<Vertice>* atual = vertices.getHead();
    while (atual) {
        if (atual->dado.armazem == armazem) {
            if (!atual->dado.vizinhos.contem(idVizinho)) {
                atual->dado.vizinhos.pushBack(idVizinho);
            }
            return;
        }
        atual = atual->next;
    }
}

void Grafo::adicionarConexao(int id1, int id2) {
    Armazem* a1 = buscaArmazem(id1);
    Armazem* a2 = buscaArmazem(id2);

    if (!a1) {
        adicionarArmazem(id1);
        a1 = buscaArmazem(id1);
    }

    if (!a2) {
        adicionarArmazem(id2);
        a2 = buscaArmazem(id2);
    }

    adicionaVizinho(a1, id2);
    adicionaVizinho(a2, id1);
}

Grafo::~Grafo() {
    Node<Vertice>* atual = vertices.getHead();
    while (atual) {
        delete atual->dado.armazem;
        atual = atual->next;
    }
}

ListaEncadeada<int> Grafo::menorRota(int origem, int destino) {
    ListaEncadeada<int> fila;
    ListaEncadeada<int> visitados;
    ListaEncadeada<Par> predecessores;
    ListaEncadeada<int> rota;

    fila.pushBack(origem);
    visitados.pushBack(origem);

    bool encontrou = false;

    while (fila.getHead() != nullptr) {
        int atual = fila.getHead()->dado;
        fila.pop(atual);

        if (atual == destino) {
            encontrou = true;
            break;
        }

        // Achar o vértice cujo armazem tem id == atual
        Node<Vertice>* vert = vertices.getHead();
        while (vert) {
            if (vert->dado.armazem->getId() == atual) {
                Node<int>* viz = vert->dado.vizinhos.getHead();
                while (viz) {
                    int vizId = viz->dado;
                    if (!visitados.contem(vizId)) {
                        fila.pushBack(vizId);
                        visitados.pushBack(vizId);
                        predecessores.pushBack(Par(vizId, atual));
                    }
                    viz = viz->next;
                }
                break;
            }
            vert = vert->next;
        }
    }

    if (!encontrou) {
        return rota; // rota vazia
    }

    // Reconstrução do caminho
    ListaEncadeada<int> reverso;
    int atual = destino;

    while (atual != origem) {
        reverso.pushBack(atual);

        Node<Par>* p = predecessores.getHead();
        bool achou = false;
        while (p) {
            if (p->dado.destino == atual) {
                atual = p->dado.anterior;
                achou = true;
                break;
            }
            p = p->next;
        }

        if (!achou) {
            break; // erro na construção da rota
        }
    }

    reverso.pushBack(origem); // adicionar origem por último (em reverso)

    // Inverter lista reversa na ordem correta
    Node<int>* no = reverso.getHead();
    while (no) {
        rota.pushFront(no->dado); // pushFront precisa estar implementado corretamente
        no = no->next;
    }

    return rota;
}

ListaEncadeada<Grafo::Vertice>& Grafo::getVertices(){
    return vertices;                                                        
}



