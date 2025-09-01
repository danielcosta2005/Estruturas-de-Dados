#ifndef ESCALONADOR_HPP
#define ESCALONADOR_HPP

#include "minheap.hpp"

class Escalonador {
private:
    MinHeap heap;
public:
    Escalonador(int capacidade);
    void inserirEvento(const Evento& e);
    Evento proximoEvento();
    bool temEventos() const;
    Evento getProximoEvento();
};

#endif
