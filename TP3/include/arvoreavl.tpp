#include "arvoreavl.hpp"

template <typename Chave, typename Valor>
int ArvoreAVL<Chave, Valor>::max (int a, int b) const {
    if (a >= b) return a;
    else {return b;};
}

template <typename Chave, typename Valor>
ArvoreAVL<Chave, Valor>::ArvoreAVL() : raiz(nullptr) {}

template <typename Chave, typename Valor>
ArvoreAVL<Chave, Valor>::~ArvoreAVL() {
    limpar(raiz);
}

template <typename Chave, typename Valor>
void ArvoreAVL<Chave, Valor>::limpar(NoArvore<Chave, Valor>* no) {
    if (no != nullptr) {
        limpar(no->esquerda);
        limpar(no->direita);
        delete no;
    }
}

template <typename Chave, typename Valor>
int ArvoreAVL<Chave, Valor>::altura(NoArvore<Chave, Valor>* no) const {
    if (no == nullptr) {
        return 0;
    }
    return no->altura;
}

template <typename Chave, typename Valor>
int ArvoreAVL<Chave, Valor>::fatorBalanceamento(NoArvore<Chave, Valor>* no) const {
    if (no == nullptr) {
        return 0;
    }
    return altura(no->esquerda) - altura(no->direita);
}

template <typename Chave, typename Valor>
void ArvoreAVL<Chave, Valor>::atualizarAltura(NoArvore<Chave, Valor>* no) {
    if (no != nullptr) {
        no->altura = 1 + max(altura(no->esquerda), altura(no->direita));
    }
}

template <typename Chave, typename Valor>
NoArvore<Chave, Valor>* ArvoreAVL<Chave, Valor>::rotacionarDireita(NoArvore<Chave, Valor>* y) {
    NoArvore<Chave, Valor>* x = y->esquerda;
    NoArvore<Chave, Valor>* T2 = x->direita;

    x->direita = y;
    y->esquerda = T2;

    if (x) x->pai = y->pai;
    if (y) y->pai = x;
    if (T2) T2->pai = y;

    atualizarAltura(y);
    atualizarAltura(x);

    return x;
}

template <typename Chave, typename Valor>
NoArvore<Chave, Valor>* ArvoreAVL<Chave, Valor>::rotacionarEsquerda(NoArvore<Chave, Valor>* x) {
    NoArvore<Chave, Valor>* y = x->direita;
    NoArvore<Chave, Valor>* T2 = y->esquerda;

    y->esquerda = x;
    x->direita = T2;

    if (y) y->pai = x->pai;
    if (x) x->pai = y;
    if (T2) T2->pai = x;

    atualizarAltura(x);
    atualizarAltura(y);

    return y;
}

template <typename Chave, typename Valor>
NoArvore<Chave, Valor>* ArvoreAVL<Chave, Valor>::balancear(NoArvore<Chave, Valor>* no) {
    if (no == nullptr) return no;

    atualizarAltura(no);

    int fb = fatorBalanceamento(no);

    if (fb > 1 && fatorBalanceamento(no->esquerda) >= 0) {
        return rotacionarDireita(no);
    }

    if (fb < -1 && fatorBalanceamento(no->direita) <= 0) {
        return rotacionarEsquerda(no);
    }

    if (fb > 1 && fatorBalanceamento(no->esquerda) < 0) {
        no->esquerda = rotacionarEsquerda(no->esquerda);
        return rotacionarDireita(no);
    }

    if (fb < -1 && fatorBalanceamento(no->direita) > 0) {
        no->direita = rotacionarDireita(no->direita);
        return rotacionarEsquerda(no);
    }

    return no;
}

template <typename Chave, typename Valor>
NoArvore<Chave, Valor>* ArvoreAVL<Chave, Valor>::inserir(NoArvore<Chave, Valor>* no, const Chave& chave, const Valor& valor) {
    if (no == nullptr) {
        return new NoArvore<Chave, Valor>(chave, valor);
    }

    if (chave < no->chave) {
        NoArvore<Chave, Valor>* novoFilho = inserir(no->esquerda, chave, valor);
        no->esquerda = novoFilho;
        if (novoFilho) {
             novoFilho->pai = no;
        }
    } else if (chave > no->chave) {
        NoArvore<Chave, Valor>* novoFilho = inserir(no->direita, chave, valor);
        no->direita = novoFilho;
        if (novoFilho) {
            novoFilho->pai = no;
        }
    } else {
        no->valor = valor;
        return no;
    }

    return balancear(no);
}

template <typename Chave, typename Valor>
void ArvoreAVL<Chave, Valor>::inserir(const Chave& chave, const Valor& valor) {
    raiz = inserir(raiz, chave, valor);
}

template <typename Chave, typename Valor>
NoArvore<Chave, Valor>* ArvoreAVL<Chave, Valor>::buscar(NoArvore<Chave, Valor>* no, const Chave& chave) const {
    if (no == nullptr || no->chave == chave) {
        return no;
    }

    if (chave < no->chave) {
        return buscar(no->esquerda, chave);
    } else {
        return buscar(no->direita, chave);
    }
}

template <typename Chave, typename Valor>
Valor* ArvoreAVL<Chave, Valor>::buscar(const Chave& chave) {
    NoArvore<Chave, Valor>* resultadoNo = buscar(raiz, chave);
    if (resultadoNo != nullptr) {
        return &(resultadoNo->valor);
    }
    return nullptr;
}

template <typename Chave, typename Valor>
const Valor* ArvoreAVL<Chave, Valor>::buscar(const Chave& chave) const {
    NoArvore<Chave, Valor>* resultadoNo = buscar(raiz, chave);
    if (resultadoNo != nullptr) {
        return &(resultadoNo->valor);
    }
    return nullptr;
}

template <typename Chave, typename Valor>
NoArvore<Chave, Valor>* ArvoreAVL<Chave, Valor>::buscarNo(const Chave& chave) const {
    return buscar(raiz, chave);
}

template <typename Chave, typename Valor>
void ArvoreAVL<Chave, Valor>::inOrderTraversal(NoArvore<Chave, Valor>* no) const {
    if (no != nullptr) {
        inOrderTraversal(no->esquerda);
        std::cout << "Chave: " << no->chave
                  << ", Valor: " << no->valor
                  << ", Altura: " << no->altura
                  << ", Pai: " << (no->pai ? std::to_string(no->pai->chave) : "N/A")
                  << std::endl;
        inOrderTraversal(no->direita);
    }
}

template <typename Chave, typename Valor>
void ArvoreAVL<Chave, Valor>::inOrderTraversal() const {
    inOrderTraversal(raiz);
}

template <typename Chave, typename Valor>
void ArvoreAVL<Chave, Valor>::inOrderCollectValues(ListaEncadeada<Valor>& lista) const {
    inOrderCollectValues(raiz, lista);
}

template <typename Chave, typename Valor>
void ArvoreAVL<Chave, Valor>::inOrderCollectValues(NoArvore<Chave, Valor>* no, ListaEncadeada<Valor>& lista) const {
    if (no != nullptr) {
        inOrderCollectValues(no->esquerda, lista);
        lista.pushBack(no->valor);
        inOrderCollectValues(no->direita, lista);
    }
}

template <typename Chave, typename Valor>
NoArvore<Chave, Valor>* ArvoreAVL<Chave, Valor>::getRaiz() const {
    return raiz;
}

template <typename Chave, typename Valor>
NoArvore<Chave, Valor>* ArvoreAVL<Chave, Valor>::noMinimo(NoArvore<Chave, Valor>* no) const {
    NoArvore<Chave, Valor>* atual = no;
    while (atual && atual->esquerda != nullptr) {
        atual = atual->esquerda;
    }
    return atual;
}