#include "armazem.hpp"
#include <stdexcept>

Armazem::Armazem(const int& id) : idArmazem(id) {}

Armazem::~Armazem() {
    Node<Secao>* atual = secoes.getHead();
    while (atual) {
        delete atual->dado.pilhaPacotes;  // Libera a pilha
        atual = atual->next;
    }
}

void Armazem::armazenarPacote(Pacote* p, const int& destino) {
    Node<Secao>* atual = secoes.getHead();

    while (atual) {
        if (atual->dado.destino == destino) {
            atual->dado.pilhaPacotes->empilhar(p);
            return;
        }
        atual = atual->next;
    }

    // Se a Secao ainda não existir, cria uma nova
    Secao nova;
    nova.destino = destino;
    nova.pilhaPacotes = new Pilha<Pacote*>();
    nova.pilhaPacotes->empilhar(p);
    secoes.pushBack(nova);
}

Pacote* Armazem::retirarPacote(const int& destino) {
    Node<Secao>* atual = secoes.getHead();

    while (atual) {
        if (atual->dado.destino == destino && !atual->dado.pilhaPacotes->estaVazia()) {
            return atual->dado.pilhaPacotes->desempilhar();
        }
        atual = atual->next;
    }

    throw std::runtime_error("Não há pacotes para o destino informado.");
}


bool Armazem::temPacotePara(const int& destino) const {
    Node<Secao>* atual = secoes.getHead();

    while (atual) {
        if (atual->dado.destino == destino && !atual->dado.pilhaPacotes->estaVazia()) {
            return true;
        }
        atual = atual->next;
    }

    return false;
}

int Armazem::getId() const {
    return idArmazem;
}

