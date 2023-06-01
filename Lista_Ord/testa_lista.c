#include "lib_listaordenada.h"
#include <stdio.h>
#include <stdlib.h>
#define max 9

lista_t *testa_cria(){
    lista_t *l;
    if (!(l = lista_cria())){
        printf("erro criacao\n");
        return NULL;
    }
    
    if (!(l -> ini))
        printf("cria certo\n");
    return l;
}

void printa_ini_fim(lista_t *lista){
    nodo_t *aux;
    
    aux = lista -> ini;
    if (!aux)
        printf("sem cabeca\n ");
    else
        do {
            printf("%d - ", aux->elemento->chave);
            aux = aux -> prox;
        } while (aux);
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

int testa_remove(lista_t *lista, elemento_t vet[]){
    int i=0;

    /*if (!lista_remove_ordenado(lista, &elem))
        printf("tudo certo, tentou remover o que nao existia\n");
    */
    while(i < max){
        printf("removendo %d\n", vet[i].chave);
        if (!lista_remove_ordenado(lista, &vet[i])){
            printf("erro remove\n");
            return 0;
        };
        i++;
    };
    return 1;
}

void set_element(elemento_t vet[]){
    int i=0;

    while (i < max){
        vet[i].chave = rand() % 10;
        printf("elemento %d setado: %d\n", i, vet[i].chave);
        i++;
    }
}

void tamanho_lista(lista_t *l){
    nodo_t *aux;
    int cont=0;
    
    aux = l -> ini;
    while (aux != NULL){
        aux = aux -> prox;
        cont++;
    };
    printf("lista com %d elementos\n", cont);
}

void imprim_lista(lista_t *l){
    nodo_t *aux;

    aux = l -> ini;
    printf("inicio: %d\n", aux -> elemento -> chave);
    printf("imprimindo lista:\n");
    while (aux != NULL){
        printf("item: %d\t", aux -> elemento -> chave);
        aux = aux -> prox;
    } 
    printf("tudo impresso\n");
}

int main(){
    lista_t *l;
    elemento_t v[max];

    set_element(v);

    if (!(l = testa_cria())){
        printf("problema testa_cria\n");
        return 0;
    }

    if (!testa_insere(l,v)){
        printf("problema testa_insere\n");
        return 0;
    }
    tamanho_lista(l);
    imprim_lista(l);
    if (!testa_remove(l,v)){
        printf("problema testa_remove\n");
        return 0;
    }

    printf ("tudo certo\n");
    lista_destroi(&l);
    return 1;
}