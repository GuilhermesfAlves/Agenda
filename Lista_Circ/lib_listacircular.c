#include <stdlib.h>
#include <stdio.h>
#include "lib_listacircular.h"

/* Cria uma Lista vazia */
lista_t *lista_cria (){
    lista_t *l;

    if (!(l = malloc(sizeof(nodo_t))))
        return NULL;

    l -> ini = NULL;
    return l;
}

/* Destroi a Lista e a aponta para NULL */ 
void lista_destroi (lista_t **l){
    lista_t *lista;
    nodo_t *aux;

    lista = *l;
    aux = lista -> ini -> prox;
    while (aux != lista -> ini){
        aux -> prev -> prox = aux -> prox;
        free(aux);
        aux = lista -> ini -> prox;
    }
    free(lista -> ini);
    free (lista);
    l = NULL;
}

/* Adiciona um elemento em ordem de acordo com o valor elemento->chave na Lista. 
 * Retorna 1 em caso de sucesso e 0 caso contrario. */
int lista_insere_ordenado (lista_t *l, elemento_t *elemento){
    nodo_t *aux, *novo;

    if (!(novo = malloc(sizeof(nodo_t))))
        return 0;

    aux = l -> ini;
    novo -> elemento = elemento;
    if (lista_vazia(l)){
        l -> ini = novo;
        novo -> prox = l -> ini;
        novo -> prev = l -> ini;
    }
    else {
        while ((aux -> prox -> elemento -> chave < elemento -> chave) && (aux -> prox != l -> ini))
            aux = aux -> prox;
        if (l -> ini -> elemento -> chave > elemento -> chave){
            aux = aux -> prev;
            l -> ini = novo;
        }
        novo -> prox = aux -> prox;
        novo -> prev = aux;
        aux -> prox = novo;
        novo -> prox -> prev = novo;
    }
    return 1;
}

/* Retira o elemento da Lista e a mantem em ordem.
 * Retorna 1 em caso de sucesso e 0 caso elemento nao esteja na Lista. */
int lista_remove_ordenado (lista_t *l, elemento_t *elemento){
    nodo_t *aux;

    aux = l -> ini;
    if (!lista_vazia(l)){
        while ((aux -> prox != l -> ini) && (aux -> elemento -> chave != elemento -> chave))
            aux = aux -> prox;

        if (aux -> elemento -> chave == elemento -> chave){
            /*caso onde o elemento esta presente*/
            if (aux == l -> ini)
                l -> ini = l -> ini -> prox;       /*caso onde se quer retirar o inicio*/
            
            if (l -> ini -> prox == l -> ini)
                l -> ini = NULL;                   /*tira o ultimo elemento*/
            else { 
                aux -> prox -> prev = aux -> prev; /*não é o ultimo elemento da lista*/
                aux -> prev -> prox = aux -> prox;
            }
            free(aux);
            return 1;
        }
    }
    return 0;
}

/* Retorna 1 se a lista esta vazia e 0 caso contrario */
int lista_vazia (lista_t *l){

    if (!l -> ini)
        return 1;
    return 0;
}