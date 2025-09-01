#include "evento.hpp"
#include <iostream> 
#include <stdexcept>

using namespace std;

// Construtor para eventos RG (Registro)
Evento::Evento(double dh, TipoEvento te, int id, const string& rem, const string& dest, int armOrig, int armDest)
    : data_hora(dh), tipo_evento(te), idPacote(id),
      remetente(rem), destinatario(dest), armazem_origem(armOrig), armazem_destino(armDest),
      secao_destino(-1) { 
}

// Construtor para eventos AR, RM, UR, TR 
Evento::Evento(double dh, TipoEvento te, int id, int val1, int val2)
    : data_hora(dh), tipo_evento(te), idPacote(id),
      remetente(""), destinatario("") { 

    armazem_origem = -1;
    armazem_destino = -1;
    secao_destino = -1;

    switch (tipo_evento) {
        case AR:
            armazem_destino = val1;   
            secao_destino = val2;     
            break;
        case RM:
            armazem_destino = val1;   
            secao_destino = val2;     
            break;
        case UR:
            armazem_destino = val1; 
            secao_destino = val2;     
            break;
        case TR:
            armazem_origem = val1;    
            armazem_destino = val2;   
            break;
        default:
            throw std::runtime_error("Erro: Construtor de 2 ints chamado para tipo de evento incorreto");
            break;
    }
}

// Construtor para eventos EN (Entrega)
Evento::Evento(double dh, TipoEvento te, int id, int armDest)
    : data_hora(dh), tipo_evento(te), idPacote(id),
      remetente(""), destinatario(""), armazem_origem(-1), armazem_destino(armDest), secao_destino(-1) {
}

// Getters
double Evento::getDataHora() const {
    return data_hora;
}

TipoEvento Evento::getTipoEvento() const {
    return tipo_evento;
}

int Evento::getIdPacote() const {
    return idPacote;
}

string Evento::getRemetente() const {
    return remetente;
}

string Evento::getDestinatario() const {
    return destinatario;
}

int Evento::getArmazemOrigem() const {
    return armazem_origem;
}

int Evento::getArmazemDestino() const {
    return armazem_destino;
}

int Evento::getSecaoDestino() const {
    return secao_destino;
}

int Evento::getTipoEventoPrioridade() const {
    switch (tipo_evento) {
        case RG: return 0; 
        case AR: return 1; 
        case RM: return 2; 
        case UR: return 3; 
        case TR: return 4; 
        case EN: return 5; 
        default: return -1; 
    }
}

// Métodos utilitários para verificar tipo de evento
bool Evento::isRG() const {
    return tipo_evento == RG;
}

bool Evento::isAR() const {
    return tipo_evento == AR;
}

bool Evento::isRM() const {
    return tipo_evento == RM;
}

bool Evento::isUR() const {
    return tipo_evento == UR;
}

bool Evento::isTR() const {
    return tipo_evento == TR;
}

bool Evento::isEN() const {
    return tipo_evento == EN;
}