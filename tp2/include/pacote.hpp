#ifndef PACOTE_HPP
#define PACOTE_HPP

#include "listaencadeada.hpp"
#include <string>

enum EstadoPacote {
    NAO_POSTADO,
    ARMAZENADO,
    EM_TRANSPORTE,
    ENTREGUE
};

class Pacote {
private:
    double tempo_postagem;
    int idPacote;
    int origem;
    int destino;
    
    double tempo_armazenado;
    double tempo_transporte;
    double tempo_ultimo_estado;
    double tempo_entrega;
    EstadoPacote estado_atual;
    int armazemAtual;
    ListaEncadeada<int> rota;

public:
    Pacote(double tempoPostagem, int id, int origem, int destino);

    void definirRota(const ListaEncadeada<int>& r);
    void atualizarEstado(EstadoPacote novo, double tempo);
    void avancarRota();
    bool chegouAoDestino() const;
    int getProximoArmazem() const;

    // Getters
    int getId() const;
    int getDestino() const;
    int getOrigem() const;
    int getOrigemAtual() const;
    double getTempoArmazenado() const;
    double getTempoTransporte() const;
    EstadoPacote getEstado() const;

    void setArmazemAtual(int id);
};

#endif
