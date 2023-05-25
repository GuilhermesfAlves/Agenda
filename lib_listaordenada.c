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
    if (aux)
        while (aux -> prox){
            lista -> ini = lista -> ini -> prox;
            free(aux -> elemento);
            free(aux);
        }
    free(lista -> ini);
    free(*l);
    *l = NULL;
}

/* Adiciona um elemento em ordem de acordo com o valor elemento->chave na Lista. 
 * Retorna 1 em caso de sucesso e 0 caso contrario.(erro de malloc) */
int lista_insere_ordenado (lista_t *l, elemento_t *elemento){
    nodo_t *aux;

    aux = l -> ini;
    if (!aux){
        aux -> elemento = elemento;
        aux -> prox = NULL;
        return 1;
    }
    while ((aux -> prox) && (aux -> elemento < elemento)){
        aux = aux -> prox;
    }
}

/* Retira o elemento da Lista e a mantem em ordem.
 * Retorna 1 em caso de sucesso e 0 caso elemento nao esteja na Lista. */
int lista_remove_ordenado (lista_t *l, elemento_t *elemento){

}
