#include "pacoteinfo.hpp"
#include <iostream> 
#include <stdexcept>

using namespace std;

PacoteInfo::PacoteInfo(int id, const string& rem, const string& dest, double dhReg, int armOrigReg, int armDestReg)
    : idPacote(id), remetente(rem), destinatario(dest),
      estado_atual(REGISTRADO), data_hora_ultima_atualizacao(dhReg), data_hora_registro(dhReg),
      armazem_atual(armOrigReg), secao_atual(-1), armazem_origem(-1), armazem_destino(armDestReg) {
}


void PacoteInfo::atualizarEstado(const Evento& evento) {
    if (evento.getDataHora() < data_hora_ultima_atualizacao) {
        throw std::runtime_error("Evento desordenado detectado para pacote");
        return;
    }

    this->data_hora_ultima_atualizacao = evento.getDataHora();

    switch (evento.getTipoEvento()) {
        case RG: 
            break; // Já inicializado no construtor
        case AR:
            this->estado_atual = ARMAZENADO;
            this->armazem_atual = evento.getArmazemDestino();
            this->secao_atual = evento.getSecaoDestino();
            this->armazem_origem = -1;
            this->armazem_destino = -1;
            break;
        case RM:
            this->estado_atual = REMOCAO_PARA_TRANS;
            this->armazem_atual = evento.getArmazemOrigem(); 
            this->secao_atual = evento.getSecaoDestino();  
            this->armazem_origem = -1;
            this->armazem_destino = -1;
            break;
        case UR:
            this->estado_atual = REARMAZENADO;
            this->armazem_atual = evento.getArmazemDestino(); 
            this->secao_atual = evento.getSecaoDestino();   
            this->armazem_origem = -1;
            this->armazem_destino = -1;
            break;
        case TR:
            this->estado_atual = EM_TRANSPORTE;
            this->armazem_origem = evento.getArmazemOrigem();
            this->armazem_destino = evento.getArmazemDestino();
            this->armazem_atual = -1; 
            this->secao_atual = -1;
            break;
        case EN:
            this->estado_atual = ENTREGUE;
            this->armazem_atual = evento.getArmazemDestino();
            this->secao_atual = -1;
            this->armazem_origem = -1;
            this->armazem_destino = -1;
            break;
        default:
            throw std::runtime_error("Erro: Tipo de evento desconhecido ou nao suportado para atualizacao de PacoteInfo");
            break;
    }
}

// Getters
int PacoteInfo::getIdPacote() const {return idPacote;}
string PacoteInfo::getRemetente() const {return remetente;}
string PacoteInfo::getDestinatario() const {return destinatario;}
EstadoPacote PacoteInfo::getEstadoAtual() const {return estado_atual;}
double PacoteInfo::getDataHoraUltimaAtualizacao() const {return data_hora_ultima_atualizacao;}
double PacoteInfo::getDataHoraRegistro() const { return data_hora_registro;}
int PacoteInfo::getArmazemAtual() const {return armazem_atual;}
int PacoteInfo::getSecaoAtual() const {return secao_atual;}
int PacoteInfo::getArmazemOrigem() const {return armazem_origem;}
int PacoteInfo::getArmazemDestino() const {return armazem_destino;}

bool PacoteInfo::isRemetente(const string& clienteNome) const {return remetente == clienteNome;}
bool PacoteInfo::isDestinatario(const string& clienteNome) const {return destinatario == clienteNome;}

