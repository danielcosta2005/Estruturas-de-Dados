#ifndef ORDENADORUNIVERSAL_HPP
#define ORDENADORUNIVERSAL_HPP
#include <string>

class ordenadorUniversal{
    private:
    
    //passados como parametro
    double a;//coef de cmps
    double b;//coef de moves
    double c;//coef de calls
    double limiar_custo;
    long seed;

    //limiares a serem calculados
    int min_tam_particao;
    int limiar_quebras;

    //stats de ordenação
    long cmps;
    long moves;
    long calls;

    //metodos privados para determinar limiares 
    int determinarLimiarQuebras(int* v, int tam);
    void shuffleVector(int* v, int tam, int num_shuffle);
    int determinarTamParticao(int* v, int tam);
    void calcularNovaFaixa(int min_tam_particao_idx, int& min_MPS, int& max_MPS, int& passo_MPS, int* mps_testados, float& diff_custo, double* custos, int num_MPS);
    int menorCusto(double *custos, int num_custos);

    //calcula custo baseado nas stats de ordenação
    double calcularCusto();

    //para manipulaçao dos stats 
    void resetarEstatisticas();
    void registrarEstatisticas(double& custo);
    void imprimirEstatisticas(double custo, int mps, std::string algoritmo);

    //metodos de ordenacao
    void insertionSort(int* v, int l, int r);
    void quickSort3Ins(int *v, int l, int r);
    //auxiliares
    int median(int p, int q, int r);
    void partition3(int* v, int l, int r, int* i, int* j);
    void swap(int *xp, int *yp);

    void copiarVetor(int* v, int* copia, int tam);



    public:

    ordenadorUniversal(long seed_, double limiar_custo_, double a_, double b_, double c_);

    void ordenarUniversal(int* v, int tam, int min_tam_particao, int limiar_quebras);

    void calibra(int* v, int tam);

    double get_limiar_quebras() const;
    int get_min_tam_particao() const;

    //metodo para calculo de quebras
    int determinarNumeroQuebras(int* v, int tam);
};

#endif