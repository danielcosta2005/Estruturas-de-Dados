#ifndef EVENTO_HPP
#define EVENTO_HPP

#include <string> 

using namespace std;

enum TipoEvento {
    RG, 
    AR, 
    RM, 
    UR, 
    TR, 
    EN  
};

class Evento {
private:
    double data_hora;          
    TipoEvento tipo_evento;    
    int idPacote;             
    string remetente;     
    string destinatario;  
    int armazem_origem;         
    int armazem_destino;        
    int secao_destino;          

public:
    // Construtor para eventos RG 
    Evento(double dh, TipoEvento te, int id, const string& rem, const string& dest, int armOrig, int armDest);

    // Construtor para eventos AR, RM, UR, TR 
    Evento(double dh, TipoEvento te, int id, int val1, int val2);

    // Construtor para eventos EN 
    Evento(double dh, TipoEvento te, int id, int armDest);


    // Getters para os atributos
    double getDataHora() const;
    TipoEvento getTipoEvento() const;
    int getIdPacote() const;
    string getRemetente() const;
    string getDestinatario() const;
    int getArmazemOrigem() const;
    int getArmazemDestino() const;
    int getSecaoDestino() const;
    int getTipoEventoPrioridade() const;

    // Métodos para verificar o tipo de evento (utilitários)
    bool isRG() const;
    bool isAR() const;
    bool isRM() const;
    bool isUR() const;
    bool isTR() const;
    bool isEN() const;
};

#endif 