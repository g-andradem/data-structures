#include <stdio.h>
#include <stdlib.h>
#include "RegistroDeHumor.h"

int IdGlobal = 0;

//Função para criar um novo registro de humor;
RegistroDeHumor *criarRegistro(){
    RegistroDeHumor *regist = (RegistroDeHumor*)malloc(sizeof(RegistroDeHumor));
    if(regist != NULL){
        printf("Digite a data do seu registro: (Dia / Mes / Ano)\n");
        scanf("%d %d %d", &regist->dat.Dia, &regist->dat.Mes, &regist->dat.Ano);

        printf("\nDigite o seu humor:\n0 - FELIZ\n1 - TRISTE\n2 - ANSIOSO\n3 - CANSADO\n4 - MOTIVADO\n5 - ESTRESSADO\n6 - NEUTRO\n");
        int temp;
        scanf("%d", &temp);
        regist->animo = (Humor) temp;
        getchar();

        printf("\nDigite o motivo do seu humor:\n");
        scanf("%[^\n]", regist->Motivo);

        printf("\nDigite a nota do seu dia: (De 0 a 10)\n");
        scanf("%d", &regist->NotaDoDia);

        regist->id = IdGlobal++;
    }
    else
        printf("Nao foi possivel criar o registro!\n");
    return regist;
}
//Função para imprimir um registro de humor;
void ImprimirRegistro(RegistroDeHumor *regist){
    if(regist!=NULL){
        printf("\n-------------------------------------------\n");
        printf("Id do registro: %d\n", regist->id);
        printf("Data do registro: %d/%d/%d\n", regist->dat.Dia, regist->dat.Mes, regist->dat.Ano);
        printf("Humor do registro: ");
        switch(regist->animo){
            case FELIZ: printf("FELIZ\n"); break;
            case TRISTE: printf("TRISTE\n"); break;
            case ANSIOSO: printf("ANSIOSO\n"); break;
            case CANSADO: printf("CANSADO\n"); break;
            case MOTIVADO: printf("MOTIVADO\n"); break;
            case ESTRESSADO: printf("ESTRESSADO\n"); break;
            case NEUTRO: printf("NEUTRO\n"); break;
        }
        printf("Motivo do registro: %s\n", regist->Motivo);
        printf("Nota do dia do registro: %d\n", regist->NotaDoDia);
        printf("-------------------------------------------\n");
    }
    else
        printf("Nao existem registros.\n");
}

//Função para liberar um registro de humor;
void LiberarRegistro(RegistroDeHumor *p){
    if(p != NULL) {
        free(p);
    }
}