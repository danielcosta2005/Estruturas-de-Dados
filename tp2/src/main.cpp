#include <iostream>
#include "grafo.hpp"
#include "simulador.hpp"

using namespace std;

int main(int argc, char** argv) {

    const int capacidadeEventos = 10000;

    Simulador simulador(capacidadeEventos);

    string nomeArquivo = argv[1];

    simulador.carregarEntrada(nomeArquivo);

    simulador.executarSimulacao();

}



    

    









