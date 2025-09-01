#ifndef PACOTE_INFO_HPP
#define PACOTE_INFO_HPP

#include <string>
#include "evento.hpp" 

using namespace std;

enum EstadoPacote {
    REGISTRADO,         // RG
    ARMAZENADO,         // AR
    REMOCAO_PARA_TRANS, // RM
    REARMAZENADO,       // UR
    EM_TRANSPORTE,      // TR
    ENTREGUE            // EN
};

class PacoteInfo {
private:
    int idPacote;
    string remetente;
    string destinatario;
    EstadoPacote estado_atual;
    double data_hora_ultima_atualizacao; // Data e hora da última atualização de estado
    double data_hora_registro;

    int armazem_atual;         
    int secao_atual;           
    int armazem_origem;  
    int armazem_destino; 

public:

    PacoteInfo(int id, const string& rem, const string& dest, double dhReg, int armOrigReg, int armDestReg);

    // Atualizar o estado do pacote com base nos eventos
    void atualizarEstado(const Evento& evento);

    // Getters
    int getIdPacote() const;
    string getRemetente() const;
    string getDestinatario() const;
    EstadoPacote getEstadoAtual() const;
    double getDataHoraUltimaAtualizacao() const;
    double getDataHoraRegistro() const;
    int getArmazemAtual() const;
    int getSecaoAtual() const;
    int getArmazemOrigem() const;
    int getArmazemDestino() const;

    // Utilitários para verificar se o cliente é remetente ou destinatário
    bool isRemetente(const string& clienteNome) const;
    bool isDestinatario(const string& clienteNome) const;
};

#endif 