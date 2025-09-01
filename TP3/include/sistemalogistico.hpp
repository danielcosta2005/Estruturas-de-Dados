#ifndef SISTEMA_LOGISTICO_HPP
#define SISTEMA_LOGISTICO_HPP

#include "evento.hpp"
#include "listaencadeada.hpp" 
#include "pacoteinfo.hpp"     
#include "clienteinfo.hpp"    
#include "arvoreavl.hpp"      
#include <sstream>            
#include <iomanip> 

using namespace std;

class SistemaLogistico {
private:
    // Estrutura para todos os eventos em ordem cronológica
    ListaEncadeada<Evento> eventosBase;

    // Índice de Pacotes: Mapeia ID do pacote para seu estado atual (PacoteInfo)
    // Este PacoteInfo* será alocado dinamicamente e gerenciado pelo SistemaLogistico.
    ArvoreAVL<int, PacoteInfo*> indicePacotes;

    // Índice de Clientes: Mapeia nome do cliente para seus pacotes associados
    // ClienteInfo* será alocado dinamicamente e gerenciado pelo SistemaLogistico.
    ArvoreAVL<string, ClienteInfo*> indiceClientes;

    ArvoreAVL<string, Node<Evento>*> indicePacoteTempo;

    void limparIndices(); // Chamada pelo destrutor

public:
    SistemaLogistico();
    ~SistemaLogistico();

    // Processa um evento lido da entrada
    void processarEvento(const Evento& evento);

    // Processa uma consulta CL 
    void consultarHistoricoCliente(double dhConsulta, const string& nomeCliente) const;

    // Processa uma consulta PC 
    void consultarHistoricoPacote(double dhConsulta, int idPacote) const;
};

#endif 