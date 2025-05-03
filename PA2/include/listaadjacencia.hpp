#ifndef LISTAADJACENCIA_HPP
#define LISTAADJACENCIA_HPP

struct Vizinho {
    int id;
    Vizinho* next;
};

struct Vertice {
    int id;
    Vizinho* headListaVizinhos; 
    Vizinho* tailListaVizinhos; 
    Vertice* next;
};


class ListaAdjacencia {
public:
    ListaAdjacencia();
    ~ListaAdjacencia();

    void insereVertice();
    void insereAresta(int v, int w);
    void adicionaVizinho(Vertice *vertice, int idVizinho);
    void imprimeVizinhos(int v);
    int quantidadeVertices();
    int quantidadeArestas();
    int grauMinimo();
    int grauMaximo();
    int nVizinhos(Vertice *vertice);
    Vertice* buscaVertice(int v);
    

private:
    Vertice* head;
    Vertice* tail;
    int nArestas;
    int nVertices;
};

#endif
