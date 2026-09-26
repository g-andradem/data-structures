#include <stdio.h>
#include <stdlib.h>
#include "RegistroDeHumor.h"
#include "ListaDuplamenteEnc.h"

int ContarId(NoLista** l){
    if(!estaVazia(l)){
        NoLista* p;
        for (p = *l; p->prox != NULL; p = p->prox){
        }
        return (p->info.id + 1);
    }
    else
        return 0;
}

//Le o arquivo.txt que contém os registros de humor
void lerArquivo(NoLista** l){
    FILE* arquivo = fopen("RegistrosDoPrograma.txt", "r");
    if(arquivo != NULL){
        RegistroDeHumor aux;

        char cabecalho[50];
        fgets(cabecalho, sizeof(cabecalho), arquivo);

        while(fscanf(arquivo, "%d   %d %d %d  %d      %d            %[^\n]", &aux.id, &aux.dat.Dia, &aux.dat.Mes, &aux.dat.Ano, &aux.animo, &aux.NotaDoDia, aux.Motivo) == 7){  
            insereNoFim(l, aux);
        }
        IdGlobal = ContarId(l);
        fclose(arquivo);
    }
}

//Sobrepoe o arquivo antigo pelo atualizado
void sobreporArquivo(NoLista** l){
    FILE* arquivo = fopen("RegistrosDoPrograma.txt", "w");
    if (arquivo != NULL) {
        NoLista* aux = *l;
        fprintf(arquivo, "ID: DATA:\t\tANIMO: NOTA DO DIA:\tMOTIVO:\n");
        while(aux != NULL) {
            fprintf(arquivo, "%d   %02d %02d %04d  %d      %d            %s\n", aux->info.id, aux->info.dat.Dia, aux->info.dat.Mes, aux->info.dat.Ano, aux->info.animo, aux->info.NotaDoDia, aux->info.Motivo);
            aux = aux->prox;
        }

        fclose(arquivo);
    }
    else {
        printf("Erro ao abrir o arquivo!");
    }
}

int main() {

    int opc;
    NoLista* lista;

    criarLista(&lista);

    lerArquivo(&lista);

    do{
    printf("----------------MENU------------------\n");
    printf("1 - Adicionar novo registro\n");
    printf("2 - Remover registro por id\n");
    printf("3 - Buscar por humor\n");
    printf("4 - Imprimir todos os registros\n");
    printf("5 - Mostrar media da notaDoDia\n");
    printf("6 - Mostrar humor mais frequente\n");
    printf("7 - Mostrar os motivos do humor\n");
    printf("8 - Sair\n");
    printf("Escolha uma opcao: ");
    scanf("%d", &opc);
    printf("-------------------------------------------\n\n");

    switch (opc) {
        case 1: {
            RegistroDeHumor regist = *criarRegistro();
            insereNoFim(&lista, regist);
            break;
        }
        case 2: {
            removerRegistroPorId(&lista);
            break;
        }
        case 3: {
            buscarRegistroPorHumor(&lista);
            break;
        }
        case 4: {
            imprimirTodosRegistros(&lista);
            break;
        }
        case 5: {
            mediaNotaDoDia(&lista);
            break;
        }
        case 6: {
            humorMaisFrequente(&lista);
            break;
        }
        case 7: {
            motivoDiaHumor(&lista);
            break;
        }
        case 8: {
            printf("Obrigado por utilizar de nosso programa :)");
            sobreporArquivo(&lista);
            break;
        }
        default:
        break;
    }
    }while(opc!=8);
}