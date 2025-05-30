#include <iostream>
#include "ordenadoruniversal.hpp"
#include <fstream>

using namespace std;

int main (int argc, char** argv){
    if (argc < 2){
        cout << "erro: parametros insuficientes";
        exit(1);
    }

    string nome_arquivo = argv[1];

    ifstream arquivo(nome_arquivo);
    if(!arquivo.is_open()){
        cerr << "erro na abertura do arquivo";
        exit(1);
    }

    int* v;
    long seed;
    double limiar_custo;
    double a;
    double b;
    double c;
    int tam;

    arquivo >> seed >> limiar_custo >> a >> b >> c >> tam;

    v = new int [tam];

    for (int i = 0; i < tam; i++){
        arquivo >> v[i];
    }

    ordenadorUniversal ordenadorUniversal(seed, limiar_custo, a,b,c);
    cout<< "size "<< tam<< " seed "<< seed<< " breaks "<< ordenadorUniversal.determinarNumeroQuebras(v, tam)<< endl;

    ordenadorUniversal.calibra(v, tam);
    
    int min_tam_particao = ordenadorUniversal.get_min_tam_particao();
    double limiar_quebras = ordenadorUniversal.get_limiar_quebras();
    ordenadorUniversal.ordenarUniversal(v, tam, min_tam_particao, limiar_quebras);
    
    delete[] v;
}