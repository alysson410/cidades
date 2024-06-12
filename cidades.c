#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "cidades.h"

// Função para ordenar as cidades por posição ao longo da estrada
int compare(const void *a, const void *b) {
    return ((Cidade *)a)->Posicao - ((Cidade *)b)->Posicao;
}

// Função para iniciar a estrada
Estrada *getEstrada(const char *nomeArquivo) {
    FILE *file = fopen(nomeArquivo, "r");
    if (!file) return NULL;

    Estrada *estrada = (Estrada *)malloc(sizeof(Estrada));
    if (!estrada) {
        fclose(file);
        return NULL;
    }

    fscanf(file, "%d", &estrada->T);
    fscanf(file, "%d", &estrada->N);

    estrada->C = (Cidade *)malloc(estrada->N * sizeof(Cidade));
    if (!estrada->C) {
        free(estrada);
        fclose(file);
        return NULL;
    }

    for (int i = 0; i < estrada->N; i++) {
        fscanf(file, "%d %s", &estrada->C[i].Posicao, estrada->C[i].Nome);
    }

    fclose(file);

    // Ordenar as cidades por posição na estrada
    qsort(estrada->C, estrada->N, sizeof(Cidade), compare);

    return estrada;
}


// Função para calcular a menor vizinhança
double calcularMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return -1.0; 

    double menorVizinhanca = estrada->T; 

    for (int i = 1; i < estrada->N; i++) {
        double vizinhanca = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
        }
    }

    free(estrada->C);
    free(estrada);

    return menorVizinhanca;
}


// Função para encontrar a cidade com a menor vizinhança
char *cidadeMenorVizinhanca(const char *nomeArquivo) {
    Estrada *estrada = getEstrada(nomeArquivo);
    if (!estrada) return NULL;

    double menorVizinhanca = estrada->T;
    char *cidadeMenor = NULL;

    for (int i = 1; i < estrada->N; i++) {
        double vizinhanca = (estrada->C[i].Posicao - estrada->C[i - 1].Posicao) / 2.0;
        if (vizinhanca < menorVizinhanca) {
            menorVizinhanca = vizinhanca;
            
            cidadeMenor = (char *)malloc((strlen(estrada->C[i].Nome) + 1) * sizeof(char));
            if (!cidadeMenor) {
                
                free(estrada->C);
                free(estrada);
                return NULL;
            }
          
            strcpy(cidadeMenor, estrada->C[i].Nome);
        }
    }

    free(estrada->C);
    free(estrada);

    return cidadeMenor;
}

