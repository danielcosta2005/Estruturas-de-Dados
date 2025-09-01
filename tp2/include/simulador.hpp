#ifndef SIMULADOR_HPP
#define SIMULADOR_HPP

#include "grafo.hpp"
#include "escalonador.hpp"
#include "pacote.hpp"
#include "transporte.hpp"
#include <fstream>

using namespace std;

class Simulador {
public:
    Grafo grafo;
    Escalonador escalonador;
    ListaEncadeada<Pacote*> pacotes;
    Transporte transporte;
    double tempoAtual;
    double custo_remocao;
    int pacotes_entregues;
    int numPacotes;

    Simulador(int capacidadeEventos): escalonador(capacidadeEventos), tempoAtual(0.0), pacotes_entregues(0), numPacotes(0) {}
    ~Simulador(){//Liberar memória dos pacotes
    Node<Pacote*>* atual = pacotes.getHead();
    while (atual) {
        delete atual->dado;
        atual = atual->next;
    }
}

    void carregarEntrada(const string& nomeArquivo){
        ifstream entrada(nomeArquivo);
    if (!entrada.is_open()) {
        cerr << "Erro ao abrir o arquivo de entrada.\n";
        return;
    }

    int numArmazens;

    // Leitura dos parâmetros globais
    int capacidade;
    double latencia, intervalo;

    entrada >> capacidade >> latencia >> intervalo >> custo_remocao;
    transporte.setParametros(capacidade, latencia, intervalo);

    entrada >> numArmazens;

    // Leitura da matriz de adjacência e criação do grafo
    for (int i = 0; i < numArmazens; ++i) {
        for (int j = 0; j < numArmazens; ++j) {
            int valor;
            entrada >> valor;
            if (valor != 0) {
                grafo.adicionarConexao(i, j);
            }
        }
    }

    // Leitura dos pacotes
    entrada >> numPacotes;

    for (int i = 0; i < numPacotes; i++) {
        double tempoChegada;
        string tagPac, tagOrg, tagDst;
        int idPac, origem, destino;

        entrada >> tempoChegada >> tagPac >> idPac >> tagOrg >> origem >> tagDst >> destino;

        // Cria e configura o pacote
        Pacote* p = new Pacote(tempoChegada, i, origem, destino);
        pacotes.pushBack(p);

        // Define rota
        ListaEncadeada<int> rota = grafo.menorRota(origem, destino);
        p->definirRota(rota);

        // Escalona chegada inicial
        Evento chegada(tempoChegada, CHEGADA_PACOTE, i, -1, origem);
        escalonador.inserirEvento(chegada);

    }

    // Escalonar transporte inicial (depois da chegada dos primeiros pacotes)
    double tempoInicialTransporte = escalonador.getProximoEvento().tempo + transporte.intervalo;

    Node<Grafo::Vertice>* v = grafo.getVertices().getHead();
    while (v) {
        int origem = v->dado.armazem->getId();
        Node<int>* vizinho = v->dado.vizinhos.getHead();
        while (vizinho) {
            int destino = vizinho->dado;
            Evento transporte(tempoInicialTransporte, TRANSPORTE, -1, origem, destino);
            escalonador.inserirEvento(transporte);
            vizinho = vizinho->next;
        }
        v = v->next;
    }

    entrada.close();
    }

    void executarSimulacao(){
        while (escalonador.temEventos() && (pacotes_entregues < numPacotes)) {
        Evento e = escalonador.proximoEvento();
        tempoAtual = e.tempo;
        processarEvento(e);
        
    }
    }
    void processarEvento(const Evento& evento){
        tempoAtual = evento.tempo;

    if (evento.tipo == CHEGADA_PACOTE) {
        // Buscar pacote
        Pacote* p = nullptr;
        Node<Pacote*>* atual = pacotes.getHead();
        while (atual) {
            if (atual->dado->getId() == evento.id_pacote) {
                p = atual->dado;
                break;
            }
            atual = atual->next;
        }

        if (!p) return;

        if (p->chegouAoDestino()) {
            printf("%07.0lf pacote %03d entregue em %03d\n",
                        tempoAtual, p->getId(), evento.armazemDestino);

            p->atualizarEstado(ENTREGUE, tempoAtual);
            pacotes_entregues++;
        }
        
    else {
        int proximo = p->getProximoArmazem();
        Armazem* a = grafo.buscaArmazem(evento.armazemDestino);

        if (a) {
            a->armazenarPacote(p, proximo);

            printf("%07.0lf pacote %03d armazenado em %03d na secao %03d\n",
            tempoAtual, p->getId(), evento.armazemDestino, proximo);

            p->atualizarEstado(ARMAZENADO, tempoAtual);
            p->avancarRota();
        }
    }

}

    else if (evento.tipo == TRANSPORTE) {
    Armazem* origem = grafo.buscaArmazem(evento.armazemOrigem);
    if (!origem) return;

    // Verifica se há pacotes para transportar
    if (!origem->temPacotePara(evento.armazemDestino)) {
        // Mesmo sem pacotes, reescalona o transporte futuro
        Evento novo(tempoAtual + transporte.intervalo,
                    TRANSPORTE, -1, evento.armazemOrigem, evento.armazemDestino);
        escalonador.inserirEvento(novo);
        return;
    }

    double tempo_remocao = tempoAtual;
    // Tirar todos os pacotes da seção
    ListaEncadeada<Pacote*> pacotesNaSecao;

    while (origem->temPacotePara(evento.armazemDestino )) {
        Pacote* p = origem->retirarPacote(evento.armazemDestino);
        tempo_remocao += custo_remocao;
        printf("%07.0lf pacote %03d removido de %03d na secao %03d\n",
                    tempo_remocao, p->getId(), evento.armazemOrigem, evento.armazemDestino);
        pacotesNaSecao.pushFront(p);  // Mantém ordem LIFO
    }

    int i = 0;
    Node<Pacote*>* atual = pacotesNaSecao.getHead();
    while (atual) {
        Pacote* p = atual->dado;

        if (i < transporte.capacidade) {
            // Pacotes em trânsito
            transporte.transportar(&p, 1, tempo_remocao, evento.armazemDestino);

            printf("%07.0lf pacote %03d em transito de %03d para %03d\n",
                        tempo_remocao, p->getId(), evento.armazemOrigem, evento.armazemDestino);

            escalonador.inserirEvento(
                Evento(tempo_remocao + transporte.latencia,
                       CHEGADA_PACOTE, p->getId(),
                       evento.armazemOrigem, evento.armazemDestino)
            );

        } else {
            // Rearmazenar o excedente
            origem->armazenarPacote(p, evento.armazemDestino);
            printf("%07.0lf pacote %03d rearmazenado em %03d na secao %03d\n",
                        tempo_remocao, p->getId(), evento.armazemOrigem, evento.armazemDestino);
        }

        atual = atual->next;
        i++;
    }

    // Sempre reescalona transporte futuro
    Evento novo(tempoAtual + transporte.intervalo,
                TRANSPORTE, -1, evento.armazemOrigem, evento.armazemDestino);
    escalonador.inserirEvento(novo);

    }

}
};


#endif
