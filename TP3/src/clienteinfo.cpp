#include "clienteinfo.hpp"

using namespace std;

ClienteInfo::ClienteInfo(const string& nome) : nome_cliente(nome) {
    // A ArvoreAVL 'pacotesDoCliente' é inicializada automaticamente
}

void ClienteInfo::adicionarOuAtualizarPacote(PacoteInfo* pacote) {
    pacotes_cliente.inserir(pacote->getIdPacote(), pacote);
}

string ClienteInfo::getNomeCliente() const {
    return nome_cliente;
}

const ArvoreAVL<int, PacoteInfo*>& ClienteInfo::getPacotesCliente() const {
    return pacotes_cliente;
}