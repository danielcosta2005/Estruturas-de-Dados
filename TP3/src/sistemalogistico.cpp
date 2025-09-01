#include "sistemalogistico.hpp"
#include <iostream>
#include <string>
#include <iomanip>
#include <sstream> 

using namespace std;

SistemaLogistico::SistemaLogistico() {
    // A raiz das AVLs é inicializada como nullptr no construtor padrão da ArvoreAVL.
    // A ListaEncadeada é inicializada como vazia.
}

SistemaLogistico::~SistemaLogistico() {
    limparIndices();
}

void SistemaLogistico::limparIndices() {
    // Liberar PacoteInfo* alocados e armazenados em indicePacotes
    ListaEncadeada<PacoteInfo*> pacotes_para_deletar;
    indicePacotes.inOrderCollectValues(pacotes_para_deletar); // Coleta todos os ponteiros para PacoteInfo

    Node<PacoteInfo*>* currentP = pacotes_para_deletar.getHead();
    while (currentP != nullptr) {
        delete currentP->dado; // Libera o objeto PacoteInfo
        currentP = currentP->next;
    }

    // Liberar ClienteInfo* alocados e armazenados em indiceClientes
    ListaEncadeada<ClienteInfo*> clientes_para_deletar;
    indiceClientes.inOrderCollectValues(clientes_para_deletar); // Coleta todos os ponteiros para ClienteInfo

    Node<ClienteInfo*>* currentC = clientes_para_deletar.getHead();
    while (currentC != nullptr) {
        delete currentC->dado; // Libera o objeto ClienteInfo (que por sua vez liberará sua ArvoreAVL interna)
        currentC = currentC->next;
    }
}

void SistemaLogistico::processarEvento(const Evento& evento) {
    Node<Evento>* novo_evento_node = eventosBase.pushBackAndReturnNode(evento);

    // O método buscar retorna Valor*
    // Para ArvoreAVL<int, PacoteInfo*>, Valor é PacoteInfo*
    // A versão não-const de buscar retorna PacoteInfo**
    PacoteInfo** pacoteInfoPtrPtr = indicePacotes.buscar(evento.getIdPacote());
    PacoteInfo* pacoteInfo = nullptr;
    if (pacoteInfoPtrPtr != nullptr) {
        pacoteInfo = *pacoteInfoPtrPtr;
    }

    if (pacoteInfo == nullptr) {
        if (evento.isRG()) {
            pacoteInfo = new PacoteInfo(evento.getIdPacote(), evento.getRemetente(), evento.getDestinatario(),
                                        evento.getDataHora(), evento.getArmazemOrigem(), evento.getArmazemDestino());
            indicePacotes.inserir(evento.getIdPacote(), pacoteInfo);

            ClienteInfo** clienteRemetentePtrPtr = indiceClientes.buscar(evento.getRemetente());
            ClienteInfo* clienteRemetente = nullptr;
            if (clienteRemetentePtrPtr != nullptr) {
                clienteRemetente = *clienteRemetentePtrPtr;
            }

            if (clienteRemetente == nullptr) {
                clienteRemetente = new ClienteInfo(evento.getRemetente());
                indiceClientes.inserir(evento.getRemetente(), clienteRemetente);
            }
            clienteRemetente->adicionarOuAtualizarPacote(pacoteInfo);

            ClienteInfo** clienteDestinatarioPtrPtr = indiceClientes.buscar(evento.getDestinatario());
            ClienteInfo* clienteDestinatario = nullptr;
            if (clienteDestinatarioPtrPtr != nullptr) {
                clienteDestinatario = *clienteDestinatarioPtrPtr;
            }

            if (clienteDestinatario == nullptr) {
                clienteDestinatario = new ClienteInfo(evento.getDestinatario());
                indiceClientes.inserir(evento.getDestinatario(), clienteDestinatario);
            }
            clienteDestinatario->adicionarOuAtualizarPacote(pacoteInfo);

        } else {
            cerr << "Erro: Evento (Tipo: " << evento.getTipoEvento() << ") para pacote "
                      << evento.getIdPacote() << " nao registrado previamente. Ignorando." << endl;
            return;
        }
    }
    pacoteInfo->atualizarEstado(evento);

    stringstream ssChave;
    ssChave << setw(7) << setfill('0') << static_cast<long long>(evento.getDataHora()) // DH com 7 digitos
        << "_" << setw(3) << setfill('0') << evento.getIdPacote() // ID com 3 digitos
        << "_" << std::setfill('0') << std::setw(1) << evento.getTipoEventoPrioridade(); // Prioridade do Tipo Evento (1 digito)
    string chaveComposta = ssChave.str();
    indicePacoteTempo.inserir(chaveComposta, novo_evento_node);
}

void SistemaLogistico::consultarHistoricoCliente(double dhConsulta, const string& nomeCliente) const {
    cout << setfill('0') << setw(6) << static_cast<long long>(dhConsulta) << " CL " << nomeCliente << endl;

    const ClienteInfo* const* clientePtrPtr = indiceClientes.buscar(nomeCliente);
    const ClienteInfo* cliente = nullptr;
    if (clientePtrPtr != nullptr) {
        cliente = *clientePtrPtr;
    }

    if (cliente == nullptr) {
        cout << 0;
        return;
    }

    // Usaremos uma AVL temporária para coletar e ordenar as linhas de saída
    // Chave: dataHora_idPacote_sequenciaInterna (para garantir ordem única e cronológica)
    // Valor: string (a linha formatada do evento)
    ArvoreAVL<string, string> resultados_ordenados;
    int sequencia_global_resultado = 0; // Para garantir unicidade de chaves dentro da AVL temporária

    ListaEncadeada<PacoteInfo*> pacotes_cliente;
    cliente->getPacotesCliente().inOrderCollectValues(pacotes_cliente); // Coleta todos os PacoteInfo* do cliente

    Node<PacoteInfo*>* currentP = pacotes_cliente.getHead();
    while (currentP != nullptr) {
        PacoteInfo* pInfo = currentP->dado;

        // Percorre todos os eventos e pega o primeiro RG do pacote atual
        const Evento* eventoRG = nullptr;
        ListaEncadeada<Node<Evento>*> eventos_sistema;
        indicePacoteTempo.inOrderCollectValues(eventos_sistema);

        Node<Node<Evento>*>* current_evento_node = eventos_sistema.getHead();
        while (current_evento_node != nullptr) {
            const Evento& event = current_evento_node->dado->dado;

            if (event.getIdPacote() == pInfo->getIdPacote() && event.isRG()) {
                eventoRG = &event;
                break; // achou o RG, pode parar
            }
            current_evento_node = current_evento_node->next;
        }

        if (eventoRG != nullptr) {
            stringstream ss_linha_RG;
            ss_linha_RG << setfill('0') << setw(7) << static_cast<long long>(eventoRG->getDataHora()) << " EV RG "
                        << setfill('0') << setw(3) << eventoRG->getIdPacote() << " "
                        << eventoRG->getRemetente() << " " << eventoRG->getDestinatario() << " "
                        << setfill('0') << setw(3) << eventoRG->getArmazemOrigem() << " "
                        << setfill('0') << setw(3) << eventoRG->getArmazemDestino();

            stringstream key_final_RG;
            key_final_RG << setfill('0') << setw(7) << static_cast<long long>(eventoRG->getDataHora())
                         << "_" << setfill('0') << setw(3) << eventoRG->getIdPacote()
                         << "_RG_" << setfill('0') << setw(3) << sequencia_global_resultado++;

            resultados_ordenados.inserir(key_final_RG.str(), ss_linha_RG.str());
        }

        // Encontrar e adicionar o ultimo evento de estado até dhConsulta

        // Coleta todos os eventos deste pacote
        ListaEncadeada<Node<Evento>*> eventos_pacote;
        indicePacoteTempo.inOrderCollectValues(eventos_pacote); // Coleta todos os eventos de TODOS os pacotes, não apenas este

        // Precisamos de uma forma de iterar APENAS pelos eventos de um pacote.
        // Já temos o inOrderCollectValues na AVL. Para filtrar, vamos iterar a lista toda.

        const Evento* ultimoEventoDeEstado = nullptr;
        Node<Node<Evento>*>* current_eventForPacket = eventos_pacote.getHead();
        while (current_eventForPacket != nullptr) {
            const Evento& event = current_eventForPacket->dado->dado;

            if (event.getIdPacote() == pInfo->getIdPacote() && event.getDataHora() <= dhConsulta) {
                if (event.getTipoEvento() != RG) {
                    ultimoEventoDeEstado = &event;
                }
            } else if (event.getIdPacote() == pInfo->getIdPacote() && event.getDataHora() > dhConsulta) {
                // Já passou da data da consulta para este pacote
                break;
            } else if (event.getIdPacote() != pInfo->getIdPacote()) {
                // nada a fazer
            }

            current_eventForPacket = current_eventForPacket->next;
        }

        // Se encontrou um último evento de estado, formate-o e adicione
        if (ultimoEventoDeEstado != nullptr && ultimoEventoDeEstado->getTipoEvento() != RG) { // Garante que não é um RG (já adicionado)
            stringstream ssLinhaEstado;
            ssLinhaEstado << setfill('0') << setw(7) << static_cast<long long>(ultimoEventoDeEstado->getDataHora()) << " EV ";

            // Imprimir o Tipo de Evento (AR, RM, UR, TR, EN)
            switch (ultimoEventoDeEstado->getTipoEvento()) {
                case AR: ssLinhaEstado << "AR "; break;
                case RM: ssLinhaEstado << "RM "; break;
                case UR: ssLinhaEstado << "UR "; break;
                case TR: ssLinhaEstado << "TR "; break;
                case EN: ssLinhaEstado << "EN "; break;
                default: break; // RG já foi tratado
            }

            ssLinhaEstado << setfill('0') << setw(3) << ultimoEventoDeEstado->getIdPacote();

            // Adicionar campos específicos como na consulta PC
            if (ultimoEventoDeEstado->isAR() || ultimoEventoDeEstado->isUR()) {
                ssLinhaEstado << " " << setfill('0') << setw(3) << ultimoEventoDeEstado->getArmazemDestino() << " "
                              << setfill('0') << setw(3) << ultimoEventoDeEstado->getSecaoDestino();
            } else if (ultimoEventoDeEstado->isRM()) {
                ssLinhaEstado << " " << setfill('0') << setw(3) << ultimoEventoDeEstado->getArmazemDestino() << " "
                              << setfill('0') << setw(3) << ultimoEventoDeEstado->getSecaoDestino();
            } else if (ultimoEventoDeEstado->isTR()) {
                ssLinhaEstado << " " << setfill('0') << setw(3) << ultimoEventoDeEstado->getArmazemOrigem() << " "
                              << setfill('0') << setw(3) << ultimoEventoDeEstado->getArmazemDestino();
            } else if (ultimoEventoDeEstado->isEN()) {
                ssLinhaEstado << " " << setfill('0') << setw(3) << ultimoEventoDeEstado->getArmazemDestino();
            }

            // Adicionar à AVL temporária para ordenação
            stringstream ssKeyFinalEstado;
            ssKeyFinalEstado << setfill('0') << setw(7) << static_cast<long long>(ultimoEventoDeEstado->getDataHora())
                             << "_" << setfill('0') << setw(3) << ultimoEventoDeEstado->getIdPacote()
                             << "_" << ultimoEventoDeEstado->getTipoEvento() << "_" << setfill('0') << setw(3) << sequencia_global_resultado++;

            resultados_ordenados.inserir(ssKeyFinalEstado.str(), ssLinhaEstado.str());
        }

        currentP = currentP->next;
    }

    // Coletar os resultados da AVL temporária em uma ListaEncadeada final para impressão
    ListaEncadeada<string> resultadosFinais;
    resultados_ordenados.inOrderCollectValues(resultadosFinais);

    cout << resultadosFinais.size() << endl;
    Node<string>* current_line = resultadosFinais.getHead();
    while (current_line != nullptr) {
        cout << current_line->dado;
        current_line = current_line->next;
        if (current_line != nullptr) cout << endl; // endl entre as linhas
    }
}

void SistemaLogistico::consultarHistoricoPacote(double dhConsulta, int idPacote) const {
    cout << setfill('0') << setw(6) << static_cast<long long>(dhConsulta) << " PC " << setfill('0') << setw(3) << idPacote << endl;

    const PacoteInfo* const* pInfoPtrPtr = indicePacotes.buscar(idPacote);
    const PacoteInfo* pInfo = nullptr;
    if (pInfoPtrPtr != nullptr) {
        pInfo = *pInfoPtrPtr;
    }

    if (pInfo == nullptr) {
        cout << 0 << endl;
        return;
    }

    ListaEncadeada<string> resultados;
    ListaEncadeada<Node<Evento>*> eventos_ordenados; 
    indicePacoteTempo.inOrderCollectValues(eventos_ordenados); // Pega todos os eventos da AVL em ordem

    // Iterar sobre a lista de eventos já ordenada e filtrar pelos critérios da consulta
    Node<Node<Evento>*>* current_evento_node_wrapper = eventos_ordenados.getHead();
    while (current_evento_node_wrapper != nullptr) {
        Node<Evento>* eventNode = current_evento_node_wrapper->dado;
        const Evento& current_event = eventNode->dado;

        if (current_event.getIdPacote() == idPacote &&
            current_event.getDataHora() <= dhConsulta &&
            current_event.getDataHora() >= pInfo->getDataHoraRegistro()) {
            
            stringstream ssLinha;
            ssLinha << setfill('0') << setw(7) << static_cast<long long>(current_event.getDataHora()) << " EV ";
            switch (current_event.getTipoEvento()) {
                case RG: ssLinha << "RG "; break;
                case AR: ssLinha << "AR "; break;
                case RM: ssLinha << "RM "; break;
                case UR: ssLinha << "UR "; break;
                case TR: ssLinha << "TR "; break;
                case EN: ssLinha << "EN "; break;
            }
            ssLinha << setfill('0') << setw(3) << current_event.getIdPacote();

            // Lógica para campos adicionais (Remetente, Destinatário, Armazéns, Seções)
            if (current_event.isRG()) {
                ssLinha << " " << current_event.getRemetente() << " " << current_event.getDestinatario() << " "
                         << setfill('0') << setw(3) << current_event.getArmazemOrigem() << " "
                         << setfill('0') << setw(3) << current_event.getArmazemDestino();
            } 
            
            else if (current_event.isAR() || current_event.isUR()) {
                ssLinha << " " << setfill('0') << setw(3) << current_event.getArmazemDestino() << " "
                         << setfill('0') << setw(3) << current_event.getSecaoDestino();
            } 
            
            else if (current_event.isRM()){
                ssLinha << " " << setfill('0') << setw(3) << current_event.getArmazemDestino() << " " 
                         << setfill('0') << setw(3) << current_event.getSecaoDestino(); 
            } 
            
            else if (current_event.isTR()) {
                ssLinha << " " << setfill('0') << setw(3) << current_event.getArmazemOrigem() << " "
                         << setfill('0') << setw(3) << current_event.getArmazemDestino();
            } 
            
            else if (current_event.isEN()) {
                ssLinha << " " << setfill('0') << setw(3) << current_event.getArmazemDestino();
            }
            resultados.pushBack(ssLinha.str());
        }
        current_evento_node_wrapper = current_evento_node_wrapper->next; // Sempre avance para o próximo nó da lista AVL
    }

    cout << resultados.size() << endl;
    Node<string>* current_line = resultados.getHead();
    while (current_line != nullptr) {
        cout << current_line->dado;
        current_line = current_line->next;
        if (current_line != nullptr) cout << endl; // endl entre as linhas
    }

}