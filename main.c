#include <stdio.h>
#include "cidades.h"

int main() {
    const char *nomeArquivo = "teste01.txt";

    double menorVizinhanca = calcularMenorVizinhanca(nomeArquivo);
    printf("Menor vizinhanca: %.2lf\n", menorVizinhanca);

    char *cidadeMenor = cidadeMenorVizinhanca(nomeArquivo);
    printf("Cidade com menor vizinhanca: %s\n", cidadeMenor);

    return 0;
}
