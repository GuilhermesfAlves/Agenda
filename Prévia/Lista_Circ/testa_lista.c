#include <stdio.h>
#include <stdlib.h>
#include "lib_listacircular.h"
#define max 9

lista_t *testa_cria(){
    lista_t *l;
    l = lista_cria();
    if (!l){
        printf("erro criacao\n");
        return NULL;
    }
    if (!l -> ini)
        printf("cria certo\n");
    return l;
}

void printa_ini_fim(lista_t *lista){
    nodo_t *aux;
    
    aux = lista -> ini;
    if (!aux)
        printf("sem cabeca\n ");
    else
        while (aux != lista -> ini){
            printf("%d - ", aux -> elemento -> chave);
            aux = aux -> prox;
        }
}

int testa_insere(lista_t *lista, elemento_t vet[]){
    int i=0;

    while (i < max){
        printf("inserindo %d\n", vet[i].chave);
        if (!lista_insere_ordenado(lista, &vet[i])){
            printf("erro insere\n");
            return 0;
        };
        printa_ini_fim(lista);
        i++;
    };
    return 1;
}

void set_element(elemento_t v[]){
    int i=0;

    while (i < max){
        v[i].chave = rand() % max;
        printf ("setado %d: %d\n", i, v[i].chave);
        i++;
    }
}

void tamanho_lista(lista_t *l){
    nodo_t *aux;
    int cont=0;
    
    aux = l -> ini;
    if (aux)
        do {
            aux = aux -> prox;
            cont++;
        } while (aux != l -> ini);
    printf("lista com %d elementos\n", cont);
}

void imprim_lista(lista_t *l){
    nodo_t *aux;

    aux = l -> ini;
    printf("inicio: %d\n", aux -> elemento -> chave);
    printf("imprimindo lista:\n");
    do {
        printf("item: %d\t", aux -> elemento -> chave);
        aux = aux -> prox;
    } while (aux != l -> ini -> prox);
    printf("tudo impresso\n");
}

void imprim_infinit(lista_t *lista){
    nodo_t *aux;
    int i=0;

    aux = lista -> ini;
    if (!lista_vazia(lista))
        do {
            printf("%d - ", aux -> elemento -> chave);
            aux = aux -> prox;
            i++;
        } while(aux != lista -> ini);
    printf("\n");
}

void imprim_prox_prev(lista_t *lista){
    nodo_t *aux, *aux2;

    aux = lista -> ini;
    aux2 = aux;
    if (!lista_vazia(lista))
        do {
            printf("%d <- %d -> %d \n", aux -> prev -> elemento -> chave, aux -> elemento -> chave, aux -> prox -> elemento -> chave);
            aux = aux -> prox;
        } while(aux != aux2);
}

int testa_remove(lista_t *lista, elemento_t vet[]){
    int i=0;

    /*if (!lista_remove_ordenado(lista, &elem))
        printf("tudo certo, tentou remover o que nao existia\n");
    */
    while(i < max){
        printf("removendo %d\n", vet[i].chave);
        imprim_infinit(lista);
        if (!lista_remove_ordenado(lista, &vet[i])){
            printf("erro remove\n");
            return 0;
        }
        imprim_prox_prev(lista);
        i++;
    };
    return 1;
}

int main(){
    lista_t *lista;
    elemento_t v[max];

    set_element(v);
    if (!(lista = lista_cria())){
        printf("problema testa_cria\n");
        return 0;
    }

    if (!testa_insere(lista,v)){
        printf("problema testa_insere\n");
        return 0;
    }
    tamanho_lista(lista);
    /*imprim_lista(lista);*/
    imprim_infinit(lista);
    imprim_prox_prev(lista);
    if (!testa_remove(lista,v)){
        printf("problema testa_remove\n");
        return 0;
    }

    printf ("tudo certo\n");
    lista_destroi(&lista);
    return 1;
}