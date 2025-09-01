#ifndef MINHEAP_HPP
#define MINHEAP_HPP

#include "evento.hpp"

class MinHeap {
private:
    Evento* vetor;
    int capacidade;
    int tam;

    void heapfyUp(int);
    void heapfyDown(int);
    void swap(int, int);

public:
    MinHeap(int cap);
    ~MinHeap();

    void inserir(Evento e);
    Evento removerMinimo();
    Evento consultarMinimo() const;
    bool estaVazio() const;
};

#endif
