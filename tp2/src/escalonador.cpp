#include "escalonador.hpp"
#include <stdexcept>

Escalonador::Escalonador(int capacidade) : heap(capacidade) {}

void Escalonador::inserirEvento(const Evento& e) {
    heap.inserir(e);
}

Evento Escalonador::proximoEvento() {
    if (!temEventos()) {
        throw std::runtime_error("Tentativa de retirar evento de um escalonador vazio.");
    }
    return heap.removerMinimo();
}

bool Escalonador::temEventos() const {
    return !heap.estaVazio();
}

Evento Escalonador::getProximoEvento(){
    return heap.consultarMinimo();
}
