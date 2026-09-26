#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//Numero de baldes e tamanho de baldes
#define tam_bucket 1000
#define num_bucket 100

//valores de comparacoes e trocas em long long
//devido a ordenacoes que fazem muitas comparacoes ou/e trocas
long long comparacoes = 0, trocas = 0;

//struct de bucketsort
typedef struct bucket{
    int *balde;
    int top;
}Bucket;

//Gera o vetor com n valores
int *geraVet(int n){
    int *vetor = malloc(n * sizeof(int));

    if(vetor == NULL){
        printf("Error!\n");
        return NULL;
    }

    return vetor;
}

//gera n numeros em ordem aleatoria, crescente e decrescente
void geraNum(int *vetor, int n){
    int opc;
    
    do{
        printf("\n0 - aleatoria\t1 - crescente\t 2 - descrecente\nEscolha um metodo de geracao de valores: ");
        scanf("%d", &opc);
        if(opc != 0 && opc != 1 && opc != 2)
            printf("\nDigite uma opcao valida!\n");
    }while(opc != 0 && opc != 1 && opc != 2);

    printf("\n");
    switch(opc){
        //gera em ordem aleatoria
        case 0:
            srand(time(NULL));
            for(int i = 0; i < n; i++)
                vetor[i] = rand();
            break;
        //gera em ordem crescente
        case 1:
            for(int i = 0; i < n; i++)
                vetor[i] = i;
            break;
        //gera em ordem decrescente
        case 2:
            for(int i = n; i > 0; i--)
                vetor[n-i] = i-1;
            break;
    }
    for(int i = 0; i < n; i++)
        printf("%d\n", vetor[i]);
}

//ALGORITMOS DE ORDENACAO :
//Bolha
void bolha(int *vetor, int n) {
    int aux;
    
    for(int i = (n - 1); i >= 1; i--){
        for(int j = 0; j < i; j++){
            comparacoes++;
            if(vetor[j] > vetor[j+1]){
                trocas++;
                aux = vetor[j];
                vetor[j] = vetor[j+1];
                vetor[j+1] = aux;   
            }
        }
    }
}

//Bolha com Criterio de Parada
void bolhaCP(int *vetor, int n) {
    int aux, j;
    int x = 1;
    int indice = n-1;

    while(x){
        j = 1;
        x = 0;
        while(j < n){
            comparacoes++;
            if(vetor[j-1] > vetor[j]){
                trocas++;
                aux = vetor[j-1];
                vetor[j-1] = vetor[j];
                vetor[j] = aux;
                x = 1;
            }
            indice = j;
            j = j+1;
        }
        n = indice;
    }
}

//Insercao Direta
void insercaoDireta(int *vetor, int n) {
    int aux, j;
    
    for(int i = 1; i < n; i++){
        aux = vetor[i];
        j = i - 1;
        while((j >= 0)){
            comparacoes++;
            if(aux < vetor[j]){
                vetor[j+1] = vetor[j];
                trocas++;
                j = j-1;
            }
            else
                break;
        }
        if(j != (i-1)){
            trocas++;
            vetor[j+1] = aux;
        }
    }
}

//Insercao Binaria
void insercaoBinaria(int *vetor, int n){
    int aux;
    int esq, dir, meio;

    for(int i = 0; i < n; i++){
        aux = vetor[i];
        esq = 0;
        dir = i;
        while(esq < dir){
            meio = (esq + dir) / 2;
            comparacoes++;
            if(vetor[meio] <= aux)
                esq = meio + 1;
            else
                dir = meio;
        }
        if (esq != i) {
            for(int j = i; j > esq; j--){
                vetor[j] = vetor[j-1];
                trocas++;
            }
            vetor[esq] = aux;
            trocas++;
        }
    }
}

//Insercao Ternaria
void insercaoTernaria(int *vetor, int n){
    int aux;
    int esq, dir, m1, m2;

    for(int i = 0; i < n ; i++){
        aux = vetor[i];
        esq = 0;
        dir = i;
        while(esq < dir){
            int terc = (dir - esq) / 3;
            m1 = esq + terc;
            m2 = dir - terc;
            comparacoes++;
            if(vetor[m1] > aux){
                dir = m1;
            }else {
                comparacoes++;
                if(vetor[m2] < aux)
                    esq = m2 + 1;
                else{
                    esq = m1 + 1;
                    dir = m2;
                }
            }
        }
        if (esq != i) {
            for(int j = i; j > esq; j--){
                vetor[j] = vetor[j-1];
                trocas++;
            }
        vetor[esq] = aux;
        trocas++;
        }
    }
}

//Shellsort
void shellsort(int *vetor, int n){
    int h = 1, j;
    int aux;

    while(h < n / 3){
        h = 3 * h + 1;
    }

    while(h >= 1){
        for(int i = h; i < n; i++){
            aux = vetor[i];
            j = i - h;
            int move = 0;
            while(j >= 0){
                comparacoes++;
                if(aux < vetor[j]){
                    trocas++;
                    vetor[j+h] = vetor[j];
                    j = j - h;
                    move = 1;
                }
                else
                    break;
            }
            if (move) {
                vetor[j+h] = aux;
                trocas++;
            }
        }
        h /= 3;
    }
}

//Selecao Direta
void selecaoDireta(int *vetor, int n){
    int menor, aux;

    for(int i = 0; i < n - 1;i++){
        menor = i;
        for(int j = i + 1; j < n; j++){
            comparacoes++;
            if(vetor[j] < vetor[menor])
                menor = j;
        }
        if(i != menor){
            trocas++;
            aux = vetor[i];
            vetor[i] = vetor[menor];
            vetor[menor] = aux;
        }
    }
}

//Heapsort
void criaHeap(int *vetor, int inicio, int final){
    int aux = vetor[inicio];
    int j = inicio * 2 + 1;
    int move = 0;
    
    while(j <= final){

        if(j < final){
            comparacoes++;
            if(vetor[j] < vetor[j+1]){
                j = j + 1;
            }
        }
        comparacoes++;
        if(aux < vetor[j]){
            vetor[inicio] = vetor[j];
            trocas++;
            inicio = j;
            j = 2 * inicio + 1;
            move = 1;
        }
        else
            j = final + 1;
    }
    if (move) {
        vetor[inicio] = aux;
        trocas++;
    }
}
void heapSort(int *vetor, int n){
    int aux;

    for(int i = (n-1)/2; i >= 0; i--){
        criaHeap(vetor, i, n-1);
    }

    for(int i = n - 1; i > 0; i--){
        trocas++;
        aux = vetor[0];
        vetor[0] = vetor[i];
        vetor[i] = aux;

        criaHeap(vetor, 0, i - 1);
    }
}

//Quicksort Centro
int particaoCentro(int *vetor, int esq, int dir){
    int i = esq, j = dir;
    int aux, pivo = vetor[(esq + dir) / 2];

    while(i <= j){

        while(i < dir){
            comparacoes++;
            if(vetor[i] < pivo)
                i++;
            else
                break;
        }
        while(j > esq){
            comparacoes++;
            if(vetor[j] > pivo)
                j--;
            else
                break;
        }
        if(i < j){
            aux = vetor[i];
            vetor[i] = vetor[j];
            vetor[j] = aux;
            trocas++;
        }
        if(i <= j){
            i++;
            j--;
        }
    }
    return i;
}
void quickSortCentro(int *vetor, int esq, int dir){
    if(esq < dir){
        int i = particaoCentro(vetor, esq, dir);
        quickSortCentro(vetor, esq, i - 1);
        quickSortCentro(vetor, i, dir);
    }
}

//Quicksort Fim
int particaoFim(int *vetor, int esq, int dir){
    int i = esq - 1;
    int aux, pivo = vetor[dir];

    for(int j = esq; j < dir; j++){
        comparacoes++;
        if(vetor[j] <= pivo){
            i++;
            if(i != j){
                aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
                trocas++;
            }
        }
    }

    if(i + 1 != dir){
        aux = vetor[i + 1];
        vetor[i + 1] = vetor[dir];
        vetor[dir] = aux;
        trocas++;
    }

    return i + 1;
}
void quickSortFim(int *vetor, int esq, int dir){
    while(esq < dir){
        int i = particaoFim(vetor, esq, dir);

        if(i - esq < dir - i){
            quickSortFim(vetor, esq, i - 1);
            esq = i + 1;
        } else {
            quickSortFim(vetor, i + 1, dir);
            dir = i - 1;
        }
    }
}

////Quicksort Mediana
int medianaDeTres(int *vetor, int esq, int dir){
    int meio = (esq + dir) / 2;

    comparacoes++;
    if(vetor[esq] > vetor[meio]){
        int aux = vetor[esq];
        vetor[esq] = vetor[meio];
        vetor[meio] = aux;
        trocas++;
    }

    comparacoes++;
    if(vetor[esq] > vetor[dir]){
        int aux = vetor[esq];
        vetor[esq] = vetor[dir];
        vetor[dir] = aux;
        trocas++;
    }

    comparacoes++;
    if(vetor[meio] > vetor[dir]){
        int aux = vetor[meio];
        vetor[meio] = vetor[dir];
        vetor[dir] = aux;
        trocas++;
    }

    return vetor[meio];
}
int particaoMediana(int *vetor, int esq, int dir){
    int i = esq, j = dir;
    int aux, pivo = medianaDeTres(vetor, esq, dir);

    while(i <= j){

        while(i < dir){
            comparacoes++;
            if(vetor[i] < pivo)
                i++;
            else
                break;
        }
        while(j > esq){
            comparacoes++;
            if(vetor[j] > pivo)
                j--;
            else
                break;
        }
        if(i <= j){
            if(i < j){
                aux = vetor[i];
                vetor[i] = vetor[j];
                vetor[j] = aux;
                trocas++;
            }
            i++;
            j--;
        }
    }
    return i;
}
void quickSortMediana(int *vetor, int esq, int dir){
    if(esq < dir){
        int i = particaoMediana(vetor, esq, dir);
        quickSortMediana(vetor, esq, i - 1);
        quickSortMediana(vetor, i, dir);
    }
}

//Mergesort
void intercalar(int *vetor, int ini, int fim, int meio){
    int i = ini;
    int j = meio + 1;
    int k = 0;

    int aux[fim - ini + 1];

    while(i <= meio && j <= fim){
        comparacoes++;
        if (vetor[i] <= vetor[j]) {
            aux[k++] = vetor[i++];
        } else {
            aux[k++] = vetor[j++];
        }
        trocas++; 
    }

    while (i <= meio) {
        aux[k++] = vetor[i++];
        trocas++;
    }

    while(j <= fim){
        aux[k++] = vetor[j++];
        trocas++;
    }
    
    for(i = ini, k = 0; i <= fim; i++, k++){
        vetor[i] = aux[k];
        trocas++;
    }
}
void mergeSort(int *vetor, int ini, int fim){
    if(ini < fim){
        int meio = (ini + fim) / 2;
        mergeSort(vetor, ini, meio);
        mergeSort(vetor, meio + 1, fim);
        intercalar(vetor, ini, fim, meio);
    }
}

//Radixsort
void countSort(int *vetor, int n, int exp){
    int *output = malloc(n * sizeof(int));
    int i, count[10] = { 0 };

    for(i = 0; i < n; i++){
        count[(vetor[i] / exp) % 10]++;
    }

    for(i = 1; i < 10; i++){
        count[i] += count[i - 1];
    }

    for(i = n - 1; i >= 0; i--){
        output[count[(vetor[i] / exp) % 10] - 1] = vetor[i];
        count[(vetor[i] / exp) % 10]--;
        trocas++;
    }

    for(i = 0; i < n; i++){
        vetor[i] = output[i];
        trocas++;
    }
    free(output);
}
void radixSort(int *vetor, int n){
    int max = vetor[0];
    for(int i = 1; i < n; i++){
        comparacoes++;
        if(vetor[i] > max){
            max = vetor[i];
        }
    }

    for(int i = 1; max / i > 0 ; i *= 10) {
        countSort(vetor, n, i);
    }
}

//Bucketsort
void insertion(int v[], int tam){
    int i, j, chave;

    for (i = 1; i < tam; i++) {
        chave = v[i];
        j = i - 1;

        while (j >= 0) {
            comparacoes++;
            if (v[j] > chave) {
                v[j + 1] = v[j];
                trocas++;
                j--;
            } else {
                break;
            }
        }

        v[j + 1] = chave;
        trocas++;
    }
}
void bucketSort(int v[], int tam){
    Bucket bucket[num_bucket];
    int j, i, k;

    int min = v[0], max = v[0];

    for(i = 1; i < tam; i++){
        comparacoes++;
        if(v[i] < min) min = v[i];
        comparacoes++;
        if(v[i] > max) max = v[i]; 
    }

    if( max == min) return;

    for (i = 0; i < num_bucket; i++) {
        bucket[i].top = 0;
        bucket[i].balde = malloc(sizeof(int) * tam);
    }

    for (i = 0; i < tam; i++) {
        int indice = (v[i] - min) * num_bucket / (max - min + 1);
        bucket[indice].balde[bucket[indice].top++] = v[i];
        trocas++;
    }

    for(i = 0; i < num_bucket; i++){
        if(bucket[i].top > 1)
            insertion(bucket[i].balde, bucket[i].top);
    }

    k = 0;
    for(i = 0; i < num_bucket; i++){
        for(j = 0; j < bucket[i].top; j++){
            v[k++] = bucket[i].balde[j];
            trocas++;
        }
        free(bucket[i].balde);
    }
}

//roda o algoritmo escolhido
void umAlgoritmo(int *vetor, int n){
    clock_t start, end;
    int opc;
    printf("\n0 - Bolha\n1 - Bolha com Criterio de Parada\n2 - Insercao Direta\n3 - Insercao Binaria\n4 - Insercao Ternaria\n5 - Shellsort\n6 - Selecao Direta\n7 - Heapsort\n8 - Quicksort Centro\n9 - Quicksort Fim\n10 - Quicksort Mediana\n11 - Mergesort\n12 - Radixsort\n13 - Bucketsort");
    do{
        printf("\nEscolha qual algoritmo de ordenacao vai ser utilizado: ");
        scanf("%d", &opc);
        if(opc < 0 || opc > 13)
            printf("\nDigite uma opcao valida!\n");
    }while(opc < 0 || opc > 13);

    start = clock();

    switch(opc){
        case 0: bolha(vetor, n); break;
        case 1: bolhaCP(vetor, n); break;
        case 2: insercaoDireta(vetor, n); break;
        case 3: insercaoBinaria(vetor, n); break;
        case 4: insercaoTernaria(vetor, n); break;
        case 5: shellsort(vetor, n); break;
        case 6: selecaoDireta(vetor, n); break;
        case 7: heapSort(vetor, n); break;
        case 8: quickSortCentro(vetor, 0, n-1); break;
        case 9: quickSortFim(vetor, 0, n-1); break;
        case 10: quickSortMediana(vetor, 0, n-1); break;
        case 11: mergeSort(vetor, 0, n-1); break;
        case 12: radixSort(vetor, n); break;
        case 13: bucketSort(vetor, n); break;
    }
    end = clock();
    //printf do tempo de execucao da ordenacao escolhida
    printf("\n\n  %6.8f seg.\n\n", ((double) (end - start)) / CLOCKS_PER_SEC);
}

//Abre o arquivo e escreve a saida do vetor nele
void escreveSaida(int *vetor, int n){
    FILE* arquivo;
    arquivo = fopen("saida.txt", "w");

    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivo.\n");
    }

    for(int i = 0; i < n; i++)
        fprintf(arquivo, "%d\n", vetor[i]);
    fclose(arquivo);
}

//Funcao principal
int main(){
    int n;

    //Escolher o tamanho do vetor
    printf("Escolha o tamanho do vetor: ");
    scanf("%d", &n);
    int *vetor = geraVet(n);

    //Escolher a forma que o vetor vai ser preenchido
    geraNum(vetor, n);

    //Escolhe qual algoritmo de ordenacao vai ser utilizado
    umAlgoritmo(vetor, n);

    //Escreve a saida do vetor no arquivo txt
    escreveSaida(vetor, n);

    //Printa o numero de comparacoes e trocas
    printf("Numero de comparacoes : %lld \nNumero de trocas: %lld\n", comparacoes, trocas);

    //Libera o vetor
    free(vetor);
    return 0;
}