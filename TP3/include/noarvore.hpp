#ifndef NO_ARVORE_HPP
#define NO_ARVORE_HPP

#include <cstddef> // Para nullptr

// Node para a Árvore AVL
template <typename Chave, typename Valor>
struct NoArvore {
    Chave chave;
    Valor valor;
    NoArvore<Chave, Valor>* esquerda;
    NoArvore<Chave, Valor>* direita;
    NoArvore<Chave, Valor>* pai; 
    int altura; 

    NoArvore(const Chave& k, const Valor& v)
        : chave(k), valor(v), esquerda(nullptr), direita(nullptr), pai(nullptr), altura(1) {}
};

#endif 