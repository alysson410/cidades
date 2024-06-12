#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cidadeteste.h"

// Função auxiliar para calcular a distância entre duas cidades
double calcularDistancia(int posicaoA, int posicaoB) {
    return abs(posicaoA - posicaoB);
}

// Função para liberar memória alocada para a estrutura Estrada
void liberarEstrada(Estrada *estrada) {
    free(estrada->C);
    free(estrada);
}

// Função para comparar distâncias para qsort
int compararDistancias(const void *a, const void *b) {
    const Cidade *cidadeA = (const Cidade *)a;
    const Cidade *cidadeB = (const Cidade *)b;
    return cidadeA->Posicao - cidadeB->Posicao;
}

// Implementação da função getEstrada
Estrada *getEstrada(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return NULL;
    }

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (estrada == NULL) {
        fclose(file);
        printf("Erro de alocação de memória.\n");
        return NULL;
    }

    // Lendo o comprimento total da estrada e o número de cidades
    fscanf(file, "%d", &estrada->T);
    fscanf(file, "%d", &estrada->N);

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (estrada->C == NULL) {
        liberarEstrada(estrada);
        fclose(file);
        printf("Erro de alocação de memória.\n");
        return NULL;
    }

    // Lendo os dados das cidades
    for (int i = 0; i < estrada->N; i++) {
        fscanf(file, "%d", &estrada->C[i].Posicao);
        fscanf(file, "%s", estrada->C[i].Nome);
    }

    fclose(file);
    return estrada;
}

// Implementação da função calcularMenorVizinhanca
double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        return -1; // Retorna -1 em caso de erro
    }

    // Ordenando as cidades pela posição na estrada
    qsort(estrada->C, estrada->N, sizeof(Cidade), compararDistancias);

    // Calculando a menor vizinhança
    double menorVizinhanca = estrada->T; // Inicializa com o comprimento total da estrada
    for (int i = 1; i < estrada->N; i++) {
        double vizinhanca = calcularDistancia(estrada->C[i].Posicao, estrada->C[i - 1].Posicao) / 2.0;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    liberarEstrada(estrada);
    return menorVizinhanca;
}

// Implementação da função cidadeMenorVizinhanca
char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (estrada == NULL) {
        return NULL;
    }

    // Calculando a menor vizinhança
    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);

    // Encontrando a cidade com a menor vizinhança
    char *cidadeMenor = NULL;
    for (int i = 1; i < estrada->N; i++) {
        double vizinhanca = calcularDistancia(estrada->C[i].Posicao, estrada->C[i - 1].Posicao) / 2.0;
        if (vizinhanca == menorVizinhanca) {
            cidadeMenor = estrada->C[i].Nome;
            break;
        }
    }

    liberarEstrada(estrada);
    return cidadeMenor;
}
