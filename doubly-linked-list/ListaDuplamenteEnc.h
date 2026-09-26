#ifndef _LISTADUPLAMENTEENC_H
#define _LISTADUPLAMENTEENC_H
#include "RegistroDeHumor.h"

//Estrutura da Lista Duplamente Encadeada;
typedef struct noLista {
    struct noLista *ant;
    RegistroDeHumor info;
    struct noLista *prox;
}NoLista;

void criarLista(NoLista** l);
int estaVazia(NoLista** l);
NoLista* ultimoElemento (NoLista** l);
void insereNoFim(NoLista** l, RegistroDeHumor v);
void removerRegistroPorId(NoLista** l);
void buscarRegistroPorHumor(NoLista** l);
void imprimirTodosRegistros(NoLista** l);
void imprimirTodosRegistrosInvertido(NoLista** l);
void mediaNotaDoDia(NoLista** l);
void humorMaisFrequente(NoLista** l);
void motivoDiaHumor(NoLista** l);
void liberarRegistros (NoLista **l);

#endif