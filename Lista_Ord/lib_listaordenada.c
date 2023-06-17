/* 
 * Implementa o TAD Lista Ordenada
 * Feito em C para a disciplina CI1001 - Programacao 1 
 *
 * Versao 1.0.0 23/05/2023
 */

/*
 * A  Lista ordenada eh uma lista que armazena dados ordenados pelo membro
 * chave do tipo ponteiro para elemento_t. 
 * A diferenca para a implementacao da Pilha e da Fila eh que ao invez
 * do nodo conter um int, ele contem um apontador para uma struct
 * que contem um int.
*/

#include "lib_listaordenada.h"
#include <stdlib.h>
#include <stdio.h>

/*  Cria uma Lista vazia */
lista_t *lista_cria (){
    lista_t *l;

    if (!(l = malloc(sizeof(lista_t))))
        return NULL;
    
    l -> ini = NULL;
    return l;
}

/*  Destroi a Lista e a aponta para NULL */ 
void lista_destroi (lista_t **l){
    lista_t *lista;
    nodo_t *aux;

    lista = *l;
    aux = lista -> ini;
    while (aux){
        lista -> ini = lista -> ini -> prox; 
        /*free(aux -> elemento);*/
        free(aux);
        aux = lista -> ini;
    }

    free(*l);
    *l = NULL;
}

/* Adiciona um elemento em ordem de acordo com o valor elemento->chave na Lista. 
 * Retorna 1 em caso de sucesso e 0 caso contrario.(erro de malloc) */
int lista_insere_ordenado (lista_t *l, elemento_t *elemento){
    nodo_t *aux, *novo;

    if (!(novo = malloc(sizeof(nodo_t))))
        return 0;

    novo -> elemento = elemento;

    aux = l -> ini;
   
    if ((!aux) || (aux -> elemento -> chave > elemento -> chave)){
        novo -> prox = aux;
        l -> ini = novo;
    }

    else {
        while ((aux -> prox) && (aux -> prox -> elemento -> chave < elemento -> chave))
            aux = aux -> prox;
            
        novo -> prox = aux -> prox;
        aux -> prox = novo; 
    }
    return 1;
}

/* Retira o elemento da Lista e a mantem em ordem.
 * Retorna 1 em caso de sucesso e 0 caso elemento nao esteja na Lista. */
int lista_remove_ordenado (lista_t *l, elemento_t *elemento){
    nodo_t *aux, *aux2;

    aux = l -> ini;
    if (!aux)
        return 0;

    /*caso onde não é a primeira posição da lista*/
    if (aux -> elemento -> chave != elemento -> chave){
        /*o auxiliar anda ate achar o elemento ou o fim*/
        while ((aux -> prox) && (aux -> prox -> elemento -> chave != elemento -> chave))
            aux = aux -> prox;

        if (!aux -> prox) 
            return 0; /*caso onde nao se acha o elemento*/
        
        aux2 = aux -> prox -> prox;
        /*free(aux -> elemento);*/
        free(aux -> prox);
        aux -> prox = aux2;
    }
    /*caso onde é a primeira posição da lista*/
    else {
        aux2 = aux -> prox;
        /*free(aux -> elemento);*/
        free(aux);
        l -> ini = aux2;
    }
    return 1;
}