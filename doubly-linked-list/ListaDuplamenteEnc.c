#include <stdio.h>
#include <stdlib.h>
#include "ListaDuplamenteEnc.h"

//Função para criar a lista (inicializando o ponteiro com NULL);
void criarLista(NoLista** l) {
    *l = NULL;
}

//Função para verificar se a lista está vazia;
int estaVazia(NoLista** l) {
    return (*l == NULL);
}

//Função para retornar um ponteiro para o último elemento;
NoLista* ultimoElemento (NoLista** l) {
	if (!estaVazia(l)) {
        NoLista *aux = *l;
        while (aux->prox != NULL) {
            aux = aux->prox;
        }
        return aux;
    } else {
        return NULL;
    }
}

//Função para inserir um novo registro de humor no fim da lista;
void insereNoFim(NoLista** l, RegistroDeHumor v) {
    NoLista *novo = (NoLista*)malloc(sizeof(NoLista));
    if(novo != NULL){
        novo -> info = v;
        novo -> prox = NULL;
        novo -> ant = NULL;
        if(!estaVazia(l)){
            NoLista* ultimo = ultimoElemento(l);
            ultimo->prox = novo;
            novo->ant = ultimo;
        }
        else
            *l = novo;
    }
    else
        printf("Nao foi possivel criar um registro!\n\n");
}

//Função para remover um registro de humor de acordo com o seu id;
void removerRegistroPorId(NoLista** l) {
    if (!estaVazia(l)) {
        int i;
        printf("Digite o id do registro que deseja remover: \n");
        scanf("%d\n", &i);
        NoLista *aux = *l;
        while (aux != NULL && aux->info.id != i) {
            aux = aux->prox;
        }
        if (aux == NULL) {
            printf("Id nao encontrado!\n\n");
        }

        if (aux->ant == NULL) {
            (*l) = aux->prox;
        } else {
            aux->ant->prox = aux->prox;
        }
        
        if (aux->prox != NULL) {
            aux->prox->ant = aux->ant;
        }

    
        free(aux);
    }
    else {
        printf("Lista Vazia!\n\n");
    }
}

//Função que busca o registro de acordo com o humor digitado pelo usuario;
void buscarRegistroPorHumor(NoLista** l){
    if (!estaVazia(l)){
        unsigned int aux, cont = 0;
        printf("Digite o humor que deseja procurar: \n");
        printf("0 - FELIZ\n1 - TRISTE\n2 - ANSIOSO\n3 - CANSADO\n4 - MOTIVADO\n5 - ESTRESSADO\n6 - NEUTRO\n");
        scanf("%d", &aux);
        NoLista* p;
        for(p = *l; p != NULL; p = p->prox){
            if(p->info.animo == aux){
                ImprimirRegistro(&(p->info));
                printf("\n");
                cont++;
            }
        }
        if(cont==0)
            printf("Nao existe registro com esse Humor!\n\n");
    }
    else
        printf("Lista Vazia!\n\n");
}

//Função que imprime todos os registros de humor já registrados;
void imprimirTodosRegistros(NoLista** l){
    if(!estaVazia(l)){
        NoLista* p = *l;
        while(p!=NULL){
            ImprimirRegistro(&(p->info));
            p=p->prox;
            printf("\n");
        };
    }
    else
        printf("Lista Vazia!\n\n");
}

//Função que imprime todos registros começando pelo final da lista;
void imprimirTodosRegistrosInvertido(NoLista** l){
    if(!estaVazia(l)){
        NoLista* p;
        for(p = *l; p->prox!=NULL; p=p->prox){
        }
        for(; p!=NULL; p = p->ant){
            ImprimirRegistro(&(p->info));
            printf("\n");
        }
    }
    else
        printf("Lista Vazia!\n\n");
}


//Função que mostra a média da nota do dia dos últimos x dias (x informado pelo usuário);
void mediaNotaDoDia(NoLista** l){
    if(!estaVazia(l)){
        int v, z = 0;
        float media = 0;
        printf("Digite o numero de dias para a média de Nota do Dia:\n");
        scanf("%d", &v);
        printf("\n");
        NoLista* ultimo = ultimoElemento(l);
        for(; ultimo!=NULL && z < v; ultimo  = ultimo->ant){
            media = media + ultimo->info.NotaDoDia;
            z++;
        }
        media = media/v;
        printf("A media dos ultimos %d dias foram: %.2f\n\n", z, media);
    }
    else
        printf("Lista Vazia!\n\n");
}


//Função que mostra o humor mais frequente do usuário dos últimos x dias (x informado pelo usuário);
void humorMaisFrequente(NoLista** l) {
    if(!estaVazia(l)){
        int v, z = 0;
        int contador[7] = {0};
        printf("Digite o numero de dias para mostrar o humor mais frequente:\n");
        scanf("%d", &v);
        printf("\n");
        NoLista *ultimo = ultimoElemento(l);
        for(; ultimo!=NULL && z < v; ultimo  = ultimo->ant) {
            contador[ultimo->info.animo]++;
            z++;
        }
        int HumorMaisFrequente=0;
        for(int i = 1; i < 7; i++){
                if(contador[i] > contador[HumorMaisFrequente])
                    HumorMaisFrequente = i;
        }
            printf("O humor mais frequente nos ultimos %d foi :\n", v);
                switch(HumorMaisFrequente){
                    case FELIZ: printf("FELIZ\n\n"); break;
                    case TRISTE: printf("TRISTE\n\n"); break;
                    case ANSIOSO: printf("ANSIOSO\n\n"); break;
                    case CANSADO: printf("CANSADO\n\n"); break;
                    case MOTIVADO:printf("MOTIVADO\n\n"); break;
                    case ESTRESSADO: printf("ESTRESSADO\n\n"); break;
                    case NEUTRO: printf("NEUTRO\n\n"); break;
                }
    }
    else
        printf("Lista Vazia!\n\n");
}

//Função que mostra os motivos de um determinado humor x (x informado pelo usuário);
void motivoDiaHumor(NoLista** l) {
    if(!estaVazia(l)) {
        unsigned int aux, v = 0;
        NoLista *p;
        printf("Digite o numero do humor para mostrar os motivos dele:\n");
        printf("0 - FELIZ\n1 - TRISTE\n2 - ANSIOSO\n3 - CANSADO\n4 - MOTIVADO\n5 - ESTRESSADO\n6 - NEUTRO\n");
        scanf("%d", &aux);
        printf("\n");
        for (p = *l; p != NULL; p = p->prox) {
            if(p->info.animo == aux) {
                printf("%s\n\n", p->info.Motivo);
                v++;
            }
        }
        if(v == 0) {
            printf("Nao foi possivel achar motivos para este humor!\n\n");
        }
        
    }
    else
        printf("Lista Vazia!\n\n");
}

//Função que libera todos os registros de humor;
void liberarRegistros (NoLista **l) {
    NoLista *aux, *aux2;
    for(aux = *l; aux != NULL; aux = aux2) {
        aux2 = aux->prox;
        free(aux);
    }
}