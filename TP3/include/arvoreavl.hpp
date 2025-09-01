#ifndef ARVORE_AVL_HPP
#define ARVORE_AVL_HPP

#include "noarvore.hpp"
#include <iostream>
#include <string>
#include "listaencadeada.hpp" 

template <typename Chave, typename Valor>
class ArvoreAVL {
private:
    NoArvore<Chave, Valor>* raiz;

    int altura(NoArvore<Chave, Valor>* no) const;
    int fatorBalanceamento(NoArvore<Chave, Valor>* no) const;
    void atualizarAltura(NoArvore<Chave, Valor>* no);

    NoArvore<Chave, Valor>* rotacionarDireita(NoArvore<Chave, Valor>* y);
    NoArvore<Chave, Valor>* rotacionarEsquerda(NoArvore<Chave, Valor>* x);

    NoArvore<Chave, Valor>* balancear(NoArvore<Chave, Valor>* no);

    // Versão recursiva de inserir, que retorna o novo nó raiz da subárvore
    NoArvore<Chave, Valor>* inserir(NoArvore<Chave, Valor>* no, const Chave& chave, const Valor& valor);
    
    // Versão recursiva de buscar, que retorna o nó 
    NoArvore<Chave, Valor>* buscar(NoArvore<Chave, Valor>* no, const Chave& chave) const; 

    void limpar(NoArvore<Chave, Valor>* no);

    // Versão auxiliar recursiva para coletar valores em ordem
    void inOrderCollectValues(NoArvore<Chave, Valor>* no, ListaEncadeada<Valor>& lista) const; 

    int max(int a, int b) const;

public:
    ArvoreAVL();
    ~ArvoreAVL();

    void inserir(const Chave& chave, const Valor& valor);

    // Métodos buscar públicos
    // Retorna um ponteiro para o VALOR, então o tipo de retorno é Valor*
    // Se Valor é PacoteInfo*, retorna PacoteInfo**.
    Valor* buscar(const Chave& chave);
    const Valor* buscar(const Chave& chave) const;

    // Método para buscar o NÓ 
    NoArvore<Chave, Valor>* buscarNo(const Chave& chave) const; // Adicionado 'const' aqui

    // Métodos para caminhamento 
    void inOrderTraversal() const;
    void inOrderTraversal(NoArvore<Chave, Valor>* no) const;

    // Coletar todos os valores em ordem para uma ListaEncadeada
    void inOrderCollectValues(ListaEncadeada<Valor>& lista) const; // Adicionado 'const' aqui

    NoArvore<Chave, Valor>* getRaiz() const;
    NoArvore<Chave, Valor>* noMinimo(NoArvore<Chave, Valor>* no) const;
};

#include "arvoreavl.tpp"
#endif 