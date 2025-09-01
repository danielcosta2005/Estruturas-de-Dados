#ifndef PILHA_CPP
#define PILHA_CPP

#include "pilha.hpp"
#include <stdexcept>  

using namespace std;

template <typename T>
Pilha<T>::Pilha() : topo(nullptr) {}

template <typename T>
Pilha<T>::~Pilha() {
    limpar();
}

template <typename T>
void Pilha<T>::empilhar(const T& valor) {
    NoPilha<T>* novo = new NoPilha<T>(valor);
    novo->next = topo;
    topo = novo;
}

template <typename T>
T Pilha<T>::desempilhar() {
    if (estaVazia()) {
        throw runtime_error("Tentativa de desempilhar de uma pilha vazia.");
    }
    NoPilha<T>* temp = topo;
    T valor = temp->dado;
    topo = topo->next;
    delete temp;
    return valor;
}

template <typename T>
T Pilha<T>::acessarTopo() const {
    if (estaVazia()) {
        throw runtime_error("Tentativa de acessar topo de uma pilha vazia.");
    }
    return topo->dado;
}

template <typename T>
bool Pilha<T>::estaVazia() const {
    return topo == nullptr;
}

template <typename T>
void Pilha<T>::limpar() {
    while (!estaVazia()) {
        desempilhar();
    }
}

#endif
