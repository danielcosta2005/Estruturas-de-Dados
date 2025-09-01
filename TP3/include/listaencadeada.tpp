#ifndef LISTA_ENCADEADA_TPP
#define LISTA_ENCADEADA_TPP
#include <iostream>

#include "listaencadeada.hpp"

template <typename T>
ListaEncadeada<T>::ListaEncadeada() : head(nullptr), tail(nullptr), _size(0) {}

template <typename T>
ListaEncadeada<T>::~ListaEncadeada() {
    limpar();
}

template <typename T>
void ListaEncadeada<T>::pushBack(const T& valor) {
    Node<T>* novo = new Node<T>(valor);
    if (head == nullptr) {
        head = tail = novo;
    } else {
        tail->next = novo;
        tail = novo;
    }
    _size++;
}

template <typename T>
Node<T>* ListaEncadeada<T>::pushBackAndReturnNode(const T& valor) {
    Node<T>* novo = new Node<T>(valor);
    if (head == nullptr) {
        head = tail = novo;
    } else {
        tail->next = novo;
        tail = novo;
    }
    _size++;
    return novo; // Retorna o ponteiro para o novo nó
}

template <typename T>
void ListaEncadeada<T>::pushFront(const T& valor) {
    Node<T>* novo = new Node<T>(valor);
    novo->next = head;
    head = novo;
    if (!tail) {
        tail = head;
    }
    _size++;
}

template <typename T>
bool ListaEncadeada<T>::pop(const T& valor) {
    Node<T>* atual = head;
    Node<T>* anterior = nullptr;

    while (atual != nullptr) {
        if (atual->dado == valor) {
            if (anterior == nullptr) {
                head = atual->next;
                if (atual == tail) {
                    tail = nullptr;
                }
            } else {
                anterior->next = atual->next;
                if (atual == tail) {
                    tail = anterior;
                }
            }
            delete atual;
            _size--;
            return true;
        }
        anterior = atual;
        atual = atual->next;
    }
    return false;
}

template <typename T>
bool ListaEncadeada<T>::contem(const T& valor) const {
    Node<T>* atual = head;
    while (atual != nullptr) {
        if (atual->dado == valor) return true;
        atual = atual->next;
    }
    return false;
}

template <typename T>
void ListaEncadeada<T>::limpar() {
    Node<T>* atual = head;
    while (atual != nullptr) {
        Node<T>* temp = atual;
        atual = atual->next;
        delete temp;
    }
    head = tail = nullptr;
    _size = 0;
}

template <typename T>
Node<T>* ListaEncadeada<T>::getHead() const {
    return head;
}

template <typename T>
Node<T>* ListaEncadeada<T>::getTail() const {
    return tail;
}

template <typename T>
T& ListaEncadeada<T>::get(int indice) {
    if (indice < 0 || indice >= _size) {
        throw std::out_of_range("Indice fora dos limites da lista.");
    }
    Node<T>* atual = head;
    for (int i = 0; i < indice; ++i) {
        atual = atual->next;
    }
    return atual->dado;
}

template <typename T>
const T& ListaEncadeada<T>::get(int indice) const {
    if (indice < 0 || indice >= _size) {
        throw std::out_of_range("Indice fora dos limites da lista.");
    }
    Node<T>* atual = head;
    for (int i = 0; i < indice; ++i) {
        atual = atual->next;
    }
    return atual->dado;
}

template <typename T>
int ListaEncadeada<T>::size() const {
    return _size;
}

template <typename T>
bool ListaEncadeada<T>::estaVazia() const {
    return _size == 0;
}

#endif
