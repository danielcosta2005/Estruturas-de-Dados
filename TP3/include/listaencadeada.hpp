#ifndef LISTA_ENCADEADA_HPP
#define LISTA_ENCADEADA_HPP

#include <iostream>
#include <stdexcept>

template <typename T>
struct Node {
    T dado;
    Node<T>* next;

    Node(const T& val) : dado(val), next(nullptr) {}
};

template <typename T>
class ListaEncadeada {
private:
    Node<T>* head;
    Node<T>* tail;

public:
    int _size;
    ListaEncadeada();
    ~ListaEncadeada();

    void pushBack(const T& valor);
    // método para retornar o ponteiro para o nó recém-adicionado
    Node<T>* pushBackAndReturnNode(const T& valor);
    void pushFront(const T& valor);
    bool pop(const T& valor);
    bool contem(const T& valor) const;
    void limpar();
    Node<T>* getHead() const;
    Node<T>* getTail() const;
    T& get(int indice);
    const T& get(int indice) const;
    int size() const; 
    bool estaVazia() const;
};

#include "listaencadeada.tpp"
#endif
