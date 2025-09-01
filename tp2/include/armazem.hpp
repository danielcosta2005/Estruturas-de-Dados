#ifndef ARMAZEM_HPP
#define ARMAZEM_HPP

#include "pilha.hpp"
#include "pacote.hpp"

using namespace std;

class Armazem {
private:
    int idArmazem;

    struct Secao {
        int destino;
        Pilha<Pacote*> *pilhaPacotes;
    };//jeito de conseguir saber onde irá o pacote.

    ListaEncadeada<Secao> secoes;
public:
    Armazem(const int& id);
    ~Armazem();
    void armazenarPacote(Pacote* p, const int& destino);
    Pacote* retirarPacote(const int& destino);
    bool temPacotePara(const int& destino) const;
    int getId() const;
};

#endif
