#include <iostream>
#include "ordenadoruniversal.hpp"
#include <cmath>
#include <string>
#include <iomanip>

using namespace std;

void ordenadorUniversal::swap(int *xp, int *yp){
    int temp = *xp;
    *xp = *yp;
    *yp = temp;
    moves += 3;
}

int ordenadorUniversal::median(int p, int q, int r){
    if ((p <= q) && (q <= r)) return q;  
    if ((p <= r) && (r <= q)) return r; 
    if ((q <= p) && (p <= r)) return p;  
    if ((q <= r) && (r <= p)) return r;  
    if ((r <= p) && (p <= q)) return p;  
    return q;                           
}

void ordenadorUniversal::partition3(int * v, int l, int r, int *i, int *j) {
  calls++;
  *i = l; *j = r;
  int pivot = median(v[l], v[(l+r)/2], v[r]);

  do {
      cmps++;
      while (v[*i] < pivot) {
          (*i)++;
          cmps++;
      }
      cmps++;
      while (v[*j] > pivot) {
          (*j)--;
          cmps++;
      }

      if (*i <= *j) {
          swap(&v[*i], &v[*j]);
          (*i)++;
          (*j)--;
      }
  } while (*i <= *j);
}

void ordenadorUniversal:: quickSort3Ins(int * A, int l, int r) { 
  calls++;
  int i, j;

  partition3(A, l, r, &i, &j);

  if (l < j) {
      if ((j - l) >= min_tam_particao) {
          quickSort3Ins(A, l, j);
      } else {
          insertionSort(A, l, j);
      }
  }

  if (i < r) {
      if ((r - i) >= min_tam_particao) {
          quickSort3Ins(A, i, r);
      } else {
          insertionSort(A, i, r);
      }
  }
}

void ordenadorUniversal::insertionSort(int* v, int l, int r) {
   
  calls++;
  int i, j, key;
  for (i = l + 1; i <= r; i++) {
    moves++;
      key = v[i];  
      j = i - 1;

      cmps++;
      while ((j >= l) && (key < v[j])) {
          cmps++;

          moves++;
          v[j+1]=v[j];
          j--;
      }

      moves++;
      v[j + 1] = key;
  }
  return;
}

ordenadorUniversal::ordenadorUniversal(long seed_, double limiar_custo_, double a_, double b_, double c_){
    seed = seed_;
    limiar_custo = limiar_custo_;
    a = a_;
    b = b_;
    c = c_;
    cmps = 0;
    moves = 0;
    calls = 0;
    limiar_quebras = 0;
    min_tam_particao = 0;
}

void ordenadorUniversal::ordenarUniversal(int* v, int tam, int min_tam_particao, int limiar_quebras){
    resetarEstatisticas();
    
     if (determinarNumeroQuebras(v, tam) < limiar_quebras){
        insertionSort(v, 0, tam-1);
     } 
     
     else {
        if (tam > min_tam_particao){
            quickSort3Ins(v, 0, tam-1);
        } else {
            insertionSort(v, 0, tam-1);
        }
     }
}



void ordenadorUniversal::calcularNovaFaixa(int min_tam_particao_idx, int& min_MPS, int& max_MPS, int& passo_MPS, int* mps_testados, float& diff_custo, double* custos, int num_MPS) {

    int new_min_idx = 0;
    int new_max_idx = 0;

    if (min_tam_particao_idx == 0){
        new_min_idx = 0;
        new_max_idx = 2;
    } else if (min_tam_particao_idx == num_MPS - 1){
        new_min_idx = num_MPS - 3;
        new_max_idx = num_MPS - 1;
    } else{
        new_min_idx = min_tam_particao_idx - 1;
        new_max_idx = min_tam_particao_idx + 1;
    }

    min_MPS = mps_testados[new_min_idx];
    max_MPS = mps_testados[new_max_idx];
    passo_MPS = (max_MPS - min_MPS) / 5;
    if (passo_MPS == 0) passo_MPS++;
    diff_custo = fabs(custos[new_max_idx] - custos[new_min_idx]);
}

void ordenadorUniversal::resetarEstatisticas(){
    cmps = 0;
    moves = 0;
    calls = 0;
}

void ordenadorUniversal::calibra(int* v, int tam){
    min_tam_particao = determinarTamParticao(v, tam);
    limiar_quebras = determinarLimiarQuebras(v, tam);
}

double ordenadorUniversal::calcularCusto(){
    return (a * cmps) + (b * moves) + (c * calls); 
}


void ordenadorUniversal::imprimirEstatisticas(double custo, int mps_atual, string algoritmo){
    cout << fixed << setprecision(9);
    cout << algoritmo << " " << mps_atual << " cost " << custo << " cmp " << cmps << " move " << moves << " calls " << calls << endl;
}

int ordenadorUniversal::menorCusto(double* custos, int num_custos) {
    int indice_min = 0;
    for (int i = 1; i < num_custos; ++i) {
        if (custos[i]< custos[indice_min]) {
            indice_min = i;
        }
    }
    return indice_min;
}

int ordenadorUniversal::determinarNumeroQuebras(int* v, int tam){
    int quebras = 0;

    for (int i = 1; i < tam; i++) {
        if (v[i] < v[i-1])
            quebras++;
    }
    return quebras;
}

void ordenadorUniversal::copiarVetor(int* v, int* copia, int tam){
    for (int i = 0; i < tam; i++){
        copia[i] = v[i];
    }
}

int ordenadorUniversal::determinarTamParticao(int* v, int tam){
    double custos[10]; 
    int mps_testados[10]; // Vetor para armazenar os tamanhos de partição testados
    int min_tam_particao_idx = 0;
    int min_MPS = 2;
    int max_MPS = tam;
    int passo_MPS = (max_MPS - min_MPS) / 5;
    int num_MPS = 0;
    int iter = 0;
    
    if (passo_MPS == 0) passo_MPS = 1;

    float diff_custo = 1e9; // Inicia com valor alto para entrar no while

    int* copia = new int[tam];

    while ((diff_custo > limiar_custo) && (num_MPS >= 5 || diff_custo == 1e9)) {
        cout<< endl << "iter " << iter++ << endl;
        num_MPS = 0;

        int mps_atual = min_MPS;

        for (int i = 0; i < 10 && mps_atual <= max_MPS; ++i, mps_atual += passo_MPS) {
            copiarVetor(v, copia, tam);
            min_tam_particao = mps_atual;
            ordenarUniversal(copia, tam, mps_atual, 0);
            custos[i] = calcularCusto();
            imprimirEstatisticas(custos[i], mps_atual, "mps");

            mps_testados[i] = mps_atual;

            num_MPS++;
        }

        min_tam_particao_idx = menorCusto(custos, num_MPS);
        calcularNovaFaixa(min_tam_particao_idx, min_MPS, max_MPS, passo_MPS, mps_testados, diff_custo, custos, num_MPS);
        
        cout << fixed << setprecision(6);
        cout << "nummps " << num_MPS << " limParticao " << mps_testados[min_tam_particao_idx] << " mpsdiff " << diff_custo << endl;
    }

    delete[] copia;
    return mps_testados[min_tam_particao_idx];
}

int ordenadorUniversal::determinarLimiarQuebras(int* v, int tam) {
    double custos_quickSort[10];
    double diff_custos[10];
    double custos_insertionSort [10];
    int quebras_testadas[10];
    int limiar_quebras_idx = 0;
    int min_quebra = 1;
    int max_quebra = tam/2;
    int passo_quebra = (max_quebra - min_quebra) / 5;
    int num_quebras_testadas = 0;
    int iter = 0;

    if (passo_quebra == 0) passo_quebra = 1;

    float diff_custo = 1e9;

    int* v_ordenado = new int[tam];
    copiarVetor(v, v_ordenado, tam);
    insertionSort(v_ordenado, 0, tam-1);

    int* copia = new int[tam];

    while ((diff_custo > limiar_custo) && (num_quebras_testadas >= 5 || diff_custo == 1e9)) {
        cout<< endl << "iter " << iter++ << endl;
        num_quebras_testadas = 0;
        int quebra_atual = min_quebra;

        for (int i = 0; i < 10 && quebra_atual <= max_quebra; ++i, quebra_atual += passo_quebra) {
            copiarVetor(v_ordenado, copia, tam);   
            limiar_quebras = quebra_atual; 

            srand48(seed);                    
            shuffleVector(copia, tam, quebra_atual); 

            resetarEstatisticas();
            quickSort3Ins(copia, 0, tam-1); 
            custos_quickSort[i] = calcularCusto();       
            imprimirEstatisticas(custos_quickSort[i], quebra_atual, "qs lq");

            srand48(seed);                    
            shuffleVector(copia, tam, quebra_atual);

            resetarEstatisticas();
            insertionSort(copia, 0, tam-1);
            diff_custos[i] = fabs(custos_quickSort[i] - calcularCusto());
            custos_insertionSort[i] = calcularCusto();
            imprimirEstatisticas(custos_insertionSort[i], quebra_atual, "in lq");


            quebras_testadas[i] = quebra_atual;
            num_quebras_testadas++;
        }

        limiar_quebras_idx = menorCusto(diff_custos, num_quebras_testadas);
        calcularNovaFaixa(limiar_quebras_idx, min_quebra, max_quebra, passo_quebra, quebras_testadas, diff_custo, custos_insertionSort, num_quebras_testadas);

        cout << fixed << setprecision(6);
        cout << "numlq " << num_quebras_testadas << " limQuebras " << quebras_testadas[limiar_quebras_idx]
             << " lqdiff " << diff_custo << endl;
    }

    delete[] v_ordenado;
    delete[] copia;
    return quebras_testadas[limiar_quebras_idx];
}

void ordenadorUniversal::shuffleVector(int* v, int tam, int num_shuffle){
    int p1 = 0, p2 = 0, temp;
    for (int i = 0; i < num_shuffle; i++){
        while (p1 == p2){
            p1 = (int) (drand48() * tam);
            p2 = (int) (drand48() * tam);
        }

        temp = v[p1];
        v[p1] = v[p2];
        v[p2] = temp;
        p1 = p2 = 0;
    }
    return;
}

int ordenadorUniversal::get_min_tam_particao()const{
    return min_tam_particao;
}

double ordenadorUniversal::get_limiar_quebras()const{
    return limiar_quebras;
}
