#ifndef CLIENTE_INFO_HPP
#define CLIENTE_INFO_HPP

#include <string>
#include "pacoteinfo.hpp" 
#include "arvoreavl.hpp"   

using namespace std;

class ClienteInfo {
private:
    string nome_cliente;
    
    ArvoreAVL<int, PacoteInfo*> pacotes_cliente;

public:
    ClienteInfo(const string& nome);

    // Adiciona ou atualiza um pacote associado a este cliente
    void adicionarOuAtualizarPacote(PacoteInfo* pacote);

    // Getters
    string getNomeCliente() const;
    // Retorna a árvore de pacotes associados para permitir iteração ou busca
    const ArvoreAVL<int, PacoteInfo*>& getPacotesCliente() const;
};

#endif 