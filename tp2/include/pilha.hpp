#ifndef PILHA_HPP
#define PILHA_HPP

template <typename T>
struct NoPilha {
    T dado;
    NoPilha* next;

    NoPilha(const T& d) : dado(d), next(nullptr) {}
};

template <typename T>
class Pilha {
private:
    NoPilha<T>* topo;

public:
    Pilha();
    ~Pilha();

    void empilhar(const T& valor);
    T desempilhar();
    T acessarTopo() const;
    bool estaVazia() const;
    void limpar();
};
#include "pilha.tpp"
#endif
