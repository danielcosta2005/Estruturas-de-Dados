#ifndef LISTA_ENCADEADA_HPP
#define LISTA_ENCADEADA_HPP

template <typename T>
struct Node {
    T dado;
    Node* next;

    Node(const T& d) : dado(d), next(nullptr) {}
};

template <typename T>
class ListaEncadeada {
private:
    Node<T>* head;
    Node<T>* tail;
    
public:
    ListaEncadeada();
    ~ListaEncadeada();

    void pushBack(const T& valor);
    void pushFront(const T& valor);
    bool pop(const T& valor);
    bool contem(const T& valor) const;
    void limpar();
    Node<T>* getHead() const;
};

#include "listaencadeada.tpp"
#endif
