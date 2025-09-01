#ifndef TRANSPORTE_HPP
#define TRANSPORTE_HPP

#include "pacote.hpp"
#include <iostream>

class Transporte {
public:
    int capacidade;
    double latencia;
    double intervalo;

    inline Transporte() : capacidade(0), latencia(0), intervalo(0) {}

    inline void setParametros(int cap, double lat, double intv) {
        capacidade = cap;
        latencia = lat;
        intervalo = intv;
    }

    inline void transportar(Pacote* pacotes[], int qtd, double tempoAtual, int destino) {
        for (int i = 0; i < qtd; ++i) {
            if (pacotes[i] != nullptr) {
                pacotes[i]->atualizarEstado(EM_TRANSPORTE, tempoAtual);
            }
        }
    }
};

#endif
