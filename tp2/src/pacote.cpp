#include "pacote.hpp"
#include <iostream>

Pacote::Pacote(double tempoPostagem, int id, int origem, int destino)
    : tempo_postagem(tempoPostagem), idPacote(id), origem(origem), destino(destino),
      tempo_armazenado(0), tempo_transporte(0), tempo_ultimo_estado(tempoPostagem),
      tempo_entrega(-1), estado_atual(NAO_POSTADO), armazemAtual(origem) {}

void Pacote::definirRota(const ListaEncadeada<int>& r) {
    rota = r;
}

void Pacote::atualizarEstado(EstadoPacote novo, double tempo) {
    double delta = tempo - tempo_ultimo_estado;

    if (estado_atual == ARMAZENADO) tempo_armazenado += delta;
    if (estado_atual == EM_TRANSPORTE) tempo_transporte += delta;

    tempo_ultimo_estado = tempo;
    estado_atual = novo;

    if (novo == ENTREGUE) tempo_entrega = tempo;

}

void Pacote::avancarRota() {
    if (rota.getHead()) {
        int atual = rota.getHead()->dado;
        rota.pop(atual);
        armazemAtual = atual; 
    }
}

bool Pacote::chegouAoDestino() const {
    return rota.getHead() && rota.getHead()->next == nullptr;
}

int Pacote::getProximoArmazem() const {
    return rota.getHead()->next->dado;
}

// Getters
int Pacote::getId() const { return idPacote; }
int Pacote::getDestino() const { return destino; }
int Pacote::getOrigem() const { return origem; }
int Pacote::getOrigemAtual() const { return armazemAtual; }
double Pacote::getTempoArmazenado() const { return tempo_armazenado; }
double Pacote::getTempoTransporte() const { return tempo_transporte; }
EstadoPacote Pacote::getEstado() const { return estado_atual; }
void Pacote::setArmazemAtual(int id) { armazemAtual = id; }
