#ifndef LISTA_ENCADEADA_TPP
#define LISTA_ENCADEADA_TPP
#include <iostream>

#include "listaencadeada.hpp"

template <typename T>
ListaEncadeada<T>::ListaEncadeada() : head(nullptr), tail(nullptr) {}

template <typename T>
ListaEncadeada<T>::~ListaEncadeada() {
    //limpar();
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
}

template <typename T>
void ListaEncadeada<T>::pushFront(const T& valor) {
    Node<T>* novo = new Node<T>(valor);
    novo->next = head;  // Aponta para o antigo head
    head = novo;        // Atualiza head para o novo nó
    if (!tail) tail = head;
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
}

template <typename T>
Node<T>* ListaEncadeada<T>::getHead() const {
    return head;
}

#endif
