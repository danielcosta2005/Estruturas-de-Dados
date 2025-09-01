#include "minheap.hpp"
#include <stdexcept>

using namespace std;

MinHeap::MinHeap(int cap) {
    capacidade = cap;
    vetor = new Evento[capacidade];
    tam = 0;
}

MinHeap::~MinHeap() {
    delete[] vetor;
}

void MinHeap::swap(int i, int j) {
    Evento temp = vetor[i];
    vetor[i] = vetor[j];
    vetor[j] = temp;
}

void MinHeap::heapfyUp(int i) {
    while (i > 0) {
        int pai = (i - 1) / 2;
        if (vetor[i] < vetor[pai]) {
            swap(i, pai);
            i = pai;
        } else {
            break;
        }
    }
}

void MinHeap::heapfyDown(int i) {
    while (2 * i + 1 < tam) {
        int filhoEsq = 2 * i + 1;
        int filhoDir = 2 * i + 2;
        int menor = filhoEsq;

        if (filhoDir < tam && vetor[filhoDir] < vetor[filhoEsq]) {
            menor = filhoDir;
        }

        if (vetor[menor] < vetor[i]) {
            swap(i, menor);
            i = menor;
        } else {
            break;
        }
    }
}

void MinHeap::inserir(Evento e) {
    if (tam == capacidade) {
        throw runtime_error("Heap cheia.");
    }
    vetor[tam] = e;
    heapfyUp(tam);
    tam++;
}

Evento MinHeap::removerMinimo() {
    if (tam == 0) {
        throw runtime_error("Heap vazia.");
    }
    Evento min = vetor[0];
    vetor[0] = vetor[tam - 1];
    tam--;
    heapfyDown(0);
    return min;
}

Evento MinHeap::consultarMinimo() const {
    if (tam == 0) {
        throw runtime_error("Heap vazia.");
    }
    return vetor[0];
}

bool MinHeap::estaVazio() const {
    return tam == 0;
}
