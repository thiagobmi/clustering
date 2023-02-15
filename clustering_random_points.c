#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
// Definição de estruturas
struct ponto
{
    int *X;
    int *Y;
};

typedef struct ponto Ponto;

struct centroF
{
    float *X;
    float *Y;
};

typedef struct centroF CentroF;

// Verificações de memória
int verificaMemCentroF(CentroF *centro)
{
    if (centro == NULL)
    {
        printf("ERRO\n");
        exit(0);
        return 0;
    }
}

int verificaMemPonto(Ponto *pontos)
{
    if (pontos == NULL)
    {
        printf("ERRO\n");
        exit(0);
        return 0;
    }
}

int verificaMemint(int *arr)
{
    if (arr == NULL)
    {
        printf("ERRO\n");
        exit(0);
        return 0;
    }
}

int verificaMemfloat(float *arr)
{
    if (arr == NULL)
    {
        printf("ERRO\n");
        exit(0);
        return 0;
    }
}

int verificaMemFloatP(float **arr)
{

    if (arr == NULL)
    {
        printf("ERRO\n");
        exit(0);
        return 0;
    }
}

int verificaMemIntP(int **arr)
{

    if (arr == NULL)
    {
        printf("ERRO\n");
        exit(0);
        return 0;
    }
}

// Alocação de memória
Ponto *alocamemoria(int n)
{

    Ponto *pontos = (Ponto *)malloc(sizeof(Ponto) * n);
    verificaMemPonto(pontos);

    for (int i = 0; i < n; i++)
    {
        pontos[i].X = (int *)malloc(sizeof(int));
        verificaMemint(pontos[i].X);
    }
    for (int i = 0; i < n; i++)
    {
        pontos[i].Y = (int *)malloc(sizeof(int));
        verificaMemint(pontos[i].Y);
    }
    return pontos;
}

CentroF *alocaMemCentroF(int k)
{

    CentroF *centroF = malloc(sizeof(float) * k * 5);
    verificaMemCentroF(centroF);

    for (int i = 0; i < k; i++)
    {
        centroF[i].X = (float *)malloc(sizeof(float));
        verificaMemfloat(centroF[i].X);
    }
    for (int i = 0; i < k; i++)
    {
        centroF[i].Y = (float *)malloc(sizeof(float));
        verificaMemfloat(centroF[i].Y);
    }
    return centroF;
}

Ponto *realocaMemoria(Ponto *pontos, int vart, int n)
{

    pontos = realloc(pontos, (sizeof(Ponto) * n));
    verificaMemPonto(pontos);

    for (int i = vart; i < n; i++)
    {
        pontos[i].X = (int *)malloc(sizeof(int));
        verificaMemint(pontos[i].X);
        pontos[i].Y = (int *)malloc(sizeof(int));
        verificaMemint(pontos[i].Y);
    }

    return pontos;
}

// Liberação de memória;
void liberamemoria(float *menordistancia, float **distancias, int k)
{

    for (int i = 0; i < k; i++)
        free(distancias[i]);

    free(menordistancia);
    free(distancias);
}

// Atribuição dos valores como pontos
Ponto *geraPontos(Ponto *pontos, int n, int nsoma)
{

    // for (n; n < nsoma; n++)
    // {
    //     scanf("%d %d", pontos[n].X, pontos[n].Y);
    // }

    for (n; n < nsoma; n++)
    {

        *pontos[n].X = -2000 + rand() % 5000;
        *pontos[n].Y = -2000 + rand() % 5000;
    }

    return pontos;
}

// Randomiza os centros em algum ponto
int randomizaCentros(int pontoaleatorio, int *vetrand, int contrand, int n)
{
    pontoaleatorio = rand() % n;

    for (int j = 0; j < contrand; j++)
        while (pontoaleatorio == vetrand[j])
            pontoaleatorio = rand() % n;

    return pontoaleatorio;
}

float **calculadistancias(float **distancias, Ponto *pontos, Ponto *centros, int n, int k)
{

    for (int j = 0; j < k; j++)
    {
        for (int i = 0; i < n; i++)
            distancias[j][i] = sqrt(pow(((float)*pontos[i].X - (float)*centros[j].X), 2) + pow(((float)*pontos[i].Y - (float)*centros[j].Y), 2));
    }

    return distancias;
}

float **calculadistanciasFloat(float **distancias, Ponto *pontos, CentroF *centroF, int n, int k)
{

    for (int j = 0; j < k; j++)
    {
        for (int i = 0; i < n; i++)
        {

            distancias[j][i] = sqrt(pow((*pontos[i].X - *centroF[j].X), 2) + pow((*pontos[i].Y - *centroF[j].Y), 2));
        }
    }
    return distancias;
}

float *calculaMenorDistancia(float **distancias, float *menordistancia, int n, int k)
{

    int menor = 999999;
    for (int i = 0; i < n; i++)
    {
        menor = 999999;
        for (int j = 0; j < k; j++)
        {
            if (distancias[j][i] < menor)
            {
                menordistancia[i] = distancias[j][i];
                menor = distancias[j][i];
            }
        }
    }
    return menordistancia;
}

void calculaMedia(float *mediaX, float *mediaY, Ponto *pontos, int **gruposR, int *contador, CentroF *centroF, CentroF *centroF2, int k, Ponto *centrosmain)
{

    for (int i = 0; i < k; i++)
        for (int j = 0; j < contador[i]; j++)
        {
            mediaX[i] += (float)*pontos[gruposR[i][j]].X;
            mediaY[i] += (float)*pontos[gruposR[i][j]].Y;
        }

    for (int i = 0; i < k; i++)
    {
        *centroF[i].X = (mediaX[i] / (float)contador[i]);
        *centroF[i].Y = (mediaY[i] / (float)contador[i]);
        if (contador[i] == 0)
        {
            *centroF[i].X = *centrosmain[i].X;
            *centroF[i].Y = *centrosmain[i].Y;
        }
    }
}

void zeraMedia(float *mediaX, float *mediaY, int k)
{
    for (int i = 0; i < k; i++)
    {
        mediaX[i] = 0;
        mediaY[i] = 0;
    }
}

int **atribuipontos(float **distancias, float *menordistancia, int *contador, int **arrponto, int n, int k)
{
    for (int j = 0; j < k; j++)
        for (int i = 0; i < n; i++)
        {

            if (distancias[j][i] == menordistancia[i])
            {
                contador[j]++;
                arrponto[j][i] = i;
            }
            else
                arrponto[j][i] = -20;
        }

    return arrponto;
}

int **agrupaPontos(Ponto *pontos, int n, int k, int *contador, Ponto *centrosmain)
{
    int i, j, pontoaleatorio, vetrand[k], contrand = 0;
    float menor;

    float *menordistancia = (float *)malloc(sizeof(float) * n);
    verificaMemfloat(menordistancia);

    Ponto *centros = alocamemoria(k);

    float **distancias = (float **)malloc(sizeof(float) * n);
    verificaMemFloatP(distancias);

    int **arrponto = (int **)malloc(sizeof(int) * k * 2);
    verificaMemIntP(arrponto);

    for (i = 0; i < k; i++)
    {
        arrponto[i] = (int *)malloc(sizeof(int) * n);
        verificaMemint(arrponto[i]);
    }

    for (i = 0; i < k; i++)
    {
        distancias[i] = (float *)malloc(sizeof(float) * n);
        verificaMemfloat(distancias[i]);
    }

    for (i = 0; i < k; i++)
    {
        pontoaleatorio = randomizaCentros(pontoaleatorio, vetrand, contrand, n);
        contrand++;
        vetrand[i] = pontoaleatorio;
        *centros[i].X = *pontos[pontoaleatorio].X;
        *centrosmain[i].X = *pontos[pontoaleatorio].X;
        *centros[i].Y = *pontos[pontoaleatorio].Y;
        *centrosmain[i].Y = *pontos[pontoaleatorio].Y;
    }

    distancias = calculadistancias(distancias, pontos, centros, n, k);

    menordistancia = calculaMenorDistancia(distancias, menordistancia, n, k);

    for (i = 0; i < k; i++)
        contador[i] = 0;

    for (j = 0; j < k; j++)
        for (i = 0; i < n; i++)
        {

            if (distancias[j][i] == menordistancia[i])
            {
                contador[j]++;
                arrponto[j][i] = i;
            }
            else
                arrponto[j][i] = -20;
        }

    liberamemoria(menordistancia, distancias, k);

    return arrponto;
}

int **reagrupapontos(CentroF *centroF, Ponto *pontos, int k, int n, int *contador, int *contVerifica)
{

    int i, j, menor = 9999;

    float *menordistancia = (float *)malloc(sizeof(float) * n);
    verificaMemfloat(menordistancia);

    float **distancias = (float **)malloc(sizeof(float) * n);
    verificaMemFloatP(distancias);

    int **arrponto = (int **)malloc(sizeof(int) * k * 2);
    verificaMemIntP(arrponto);

    for (i = 0; i < k; i++)
    {
        arrponto[i] = (int *)malloc(sizeof(int) * n);
        verificaMemint(arrponto[i]);
    }

    for (i = 0; i < k; i++)
    {
        distancias[i] = (float *)malloc(sizeof(float) * n);
        verificaMemfloat(distancias[i]);
    }

    distancias = calculadistanciasFloat(distancias, pontos, centroF, n, k);

    menordistancia = calculaMenorDistancia(distancias, menordistancia, n, k);

    for (i = 0; i < k; i++)
    {
        contVerifica[i] = contador[i];
        contador[i] = 0;
    }
    arrponto = atribuipontos(distancias, menordistancia, contador, arrponto, n, k);

    liberamemoria(menordistancia, distancias, k);

    return arrponto;
}

int **atribuiVetores(int **gruposR, int **grupos, int *contador, int n, int k)
{
    int contapontos = 0;

    for (int i = 0; i < k; i++)
    {
        contapontos = 0;
        while (contapontos < contador[i])
            for (int j = 0; j < n; j++)
            {
                if (grupos[i][j] != -20)
                {
                    gruposR[i][contapontos] = grupos[i][j];
                    contapontos++;
                }
            }
    }

    return gruposR;
}

Ponto *adicionapontos(Ponto *pontos, int n, int nplus)
{

    int nsoma = n + nplus;

    pontos = realloc(pontos, sizeof(Ponto) * ((nsoma)));
    verificaMemPonto(pontos);

    for (int nlocal = n; nlocal < nsoma; nlocal++)
    {
        pontos[nlocal].X = (int *)malloc(sizeof(int));
        verificaMemint(pontos[nlocal].X);
        pontos[nlocal].Y = (int *)malloc(sizeof(int));
        verificaMemint(pontos[nlocal].Y);
    }

    geraPontos(pontos, n, nsoma);

    return pontos;
}

void liberamemoriaGrupos(int **gruposR, int **grupos, int k)
{
    for (int i = 0; i < k; i++)
    {
        free(grupos[i]);
        free(gruposR[i]);
    }
}

int main(int argc, char *argv[])
{

    int n = 0, k = 0, i = 0, j = 0, x = 0, vart = 0, vart2 = 0, **grupos, contapontos = 0, verifica = 0, stopcond = 0, nplus = 0, nsoma = 0, numfile = 0, printa = 0;
    char str[5], nome[25] = "arquivo";
    Ponto *pontos;
    FILE *pont_arq;

    srand(time(NULL));

    // scanf("%d", &n);
    // k = 14;

    x = 10;
    n = atoi(argv[1]);
    k = atoi(argv[2]);

    if (n < k * 2)
    {
        Ponto *pontosmenor = alocamemoria(n);
        while (n < k * 2)
        {
            if (vart > 0)
                pontosmenor = realocaMemoria(pontosmenor, vart, n);

            pontosmenor = geraPontos(pontosmenor, vart, n);
            scanf("%d", &vart2);
            vart = n;
            n += vart2;
            printf("n=%d k=%d\n", n, k);
        }

        pontosmenor = realocaMemoria(pontosmenor, vart, n);
        pontosmenor = geraPontos(pontosmenor, vart, n);

        pontos = pontosmenor;

        printf("Criando clusters...\n");
    }
    else
        pontos = alocamemoria(n);

    int *contVerifica = malloc(sizeof(int) * k);
    int *contador = malloc(sizeof(int) * k);
    CentroF *centroF = alocaMemCentroF(k);
    CentroF *centroF2 = alocaMemCentroF(k);
    Ponto *centrosmain = alocamemoria(k);

    if (vart == 0)
        pontos = geraPontos(pontos, vart, n);

    grupos = agrupaPontos(pontos, n, k, contador, centrosmain);

    int **gruposR = (int **)malloc(sizeof(int) * k * 2);
    verificaMemIntP(gruposR);

    for (i = 0; i < k; i++)
    {
        gruposR[i] = (int *)malloc(sizeof(int) * contador[i] * 2);
        verificaMemint(gruposR[i]);
    }

    gruposR = atribuiVetores(gruposR, grupos, contador, n, k);

    float *mediaX = (float *)malloc(sizeof(double) * k * 2);
    verificaMemfloat(mediaX);

    float *mediaY = (float *)malloc(sizeof(double) * k * 2);
    verificaMemfloat(mediaY);

    calculaMedia(mediaX, mediaY, pontos, gruposR, contador, centroF, centroF2, k, centrosmain);

    liberamemoriaGrupos(gruposR, grupos, k);

    for (int l = 0; l < x; l++)
    {
        printf("\nL = %d",l);
        grupos = reagrupapontos(centroF, pontos, k, n, contador, contVerifica);

        for (i = 0; i < k; i++)
        {
            gruposR[i] = (int *)malloc(sizeof(int) * contador[i]);
            verificaMemint(gruposR[i]);
        }

        gruposR = atribuiVetores(gruposR, grupos, contador, n, k);

        zeraMedia(mediaX, mediaY, k);

        calculaMedia(mediaX, mediaY, pontos, gruposR, contador, centroF, centroF2, k, centrosmain);

        // verifica = 0;
        // for (i = 0; i < k; i++)
        //     if (contVerifica[i] != contador[i])
        //         verifica++;

        if (l == x - 1)
        {
            //if (n % 300 == 0)
            //printa = 0;

            printf("\nn =%d k =%d\n", n, k);
            scanf("%d", &nplus);
        }

        if (nplus > 0)
        {
            pontos = adicionapontos(pontos, n, nplus);
            n += nplus;
            printa++;
            nplus = 0;
            l = 0;
        }

        // if (n % 501 == 0 && printa > 0)
        // {
        //     sprintf(str, "%d", numfile);
        //     strcat(nome, str);
        //     pont_arq = fopen(nome, "w");

        //     for (i = 0; i < k; i++)
        //     {
        //         fprintf(pont_arq, "%.2f;%.2f;0\n", *centroF[i].X, *centroF[i].Y);
        //         for (j = 0; j < contador[i]; j++)
        //             fprintf(pont_arq, "%d;%d;1\n", *pontos[gruposR[i][j]].X, *pontos[gruposR[i][j]].Y);
        //     }

        //     fclose(pont_arq);
        //     numfile++;
        //     printa = 0;
        // }

        liberamemoriaGrupos(gruposR, grupos, k);
    }
}
