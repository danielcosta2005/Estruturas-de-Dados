#ifndef GRAFO_HPP
#define GRAFO_HPP

#include "armazem.hpp"
#include "listaencadeada.hpp"

class Grafo {
public:
    struct Vertice {
        Armazem* armazem;
        ListaEncadeada<int> vizinhos;
    };
    void adicionarArmazem(int idArmazem);
    void adicionarConexao(int id1, int id2);
    void adicionaVizinho(Armazem* armazem, int idVizinho);
    Armazem* buscaArmazem(int id);
    ListaEncadeada<int> menorRota(int origem, int destino);
    ~Grafo(); // para liberar memória dos armazéns
    ListaEncadeada<Vertice>& getVertices();

private:
    ListaEncadeada<Vertice> vertices;
};

#endif

