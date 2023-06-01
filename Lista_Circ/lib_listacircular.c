#include <stdlib.h>
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

}

/* Retira o elemento da Lista e a mantem em ordem.
 * Retorna 1 em caso de sucesso e 0 caso elemento nao esteja na Lista. */
int lista_remove_ordenado (lista_t *l, elemento_t *elemento){

}

/* Retorna 1 se a lista esta vazia e 0 caso contrario */
int lista_vazia (lista_t *l){

    if (!l -> ini)
        return 1;
    return 0;
}