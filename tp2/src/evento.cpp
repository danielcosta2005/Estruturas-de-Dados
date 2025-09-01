#include "evento.hpp"
#include <sstream>
#include <iomanip>

using namespace std;

Evento::Evento() 
    : tempo(0), tipo(CHEGADA_PACOTE), id_pacote(-1), armazemOrigem(-1), armazemDestino(-1) {gerarChave();}


Evento::Evento(double t, TipoEvento tp, int id, int origem, int destino)
    : tempo(t), tipo(tp), id_pacote(id), armazemOrigem(origem), armazemDestino(destino) {gerarChave();}

// Operações para min-heap
bool Evento::operator<(const Evento& outro) const {

    return chave < outro.chave;
    
}

bool Evento::operator>(const Evento& outro) const {
    
    return chave > outro.chave;
}

void Evento::gerarChave() {
    ostringstream oss;

    // Tempo com 6 dígitos 
    oss << setw(6) << setfill('0') << static_cast<int>(tempo);

    if (tipo == CHEGADA_PACOTE) {
        // ID do pacote com 6 dígitos + digito 1
        oss << setw(6) << setfill('0') << id_pacote;
        oss << '1';
    } else if (tipo == TRANSPORTE) {
        // Origem e destino com 3 dígitos + digito 2
        oss << setw(3) << setfill('0') << armazemOrigem;
        oss << setw(3) << setfill('0') << armazemDestino;
        oss << '2';
    } else {
        oss << "XXXXXXXXXXXXX"; 
    }

    chave = oss.str();
}