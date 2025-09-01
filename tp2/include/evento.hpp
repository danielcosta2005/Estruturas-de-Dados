#ifndef EVENTO_HPP
#define EVENTO_HPP
#include <string>

using namespace std;

enum TipoEvento {
    TRANSPORTE,
    CHEGADA_PACOTE
};

struct Evento {
    double tempo;
    TipoEvento tipo;
    int id_pacote;
    int armazemOrigem;
    int armazemDestino;
    string chave;

    Evento();  // construtor padrão
    Evento(double t, TipoEvento tp, int id, int origem, int destino);

    // Operadores para fila de prioridade (min-heap)
    bool operator<(const Evento& outro) const;
    bool operator>(const Evento& outro) const;
    void gerarChave();
};

#endif
