#include "lib_listaordenada.h"
#include <stdio.h>

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

int testa_insere(lista_t *lista){
    elemento_t elem;
    int vet[5]={2,4,3,5,1};
    int i=0;

    while (i < 5){
        elem.chave = vet[i];
        printf("inserindo %d\n", vet[i]);
        if (!lista_insere_ordenado(lista, &elem)){
            printf("erro insere\n");
            return 0;
        };
        i++;
    };
    return 1;
}

int testa_remove(lista_t *lista){
    elemento_t elem;
    int vet[5]={2,4,3,5,1};
    int i=0;

    elem.chave = 7;
    if (!lista_remove_ordenado(lista, &elem))
        printf("tudo certo, tentou remover o que nao existia\n");
    
    while(i < 5){
        elem.chave = vet[i];
        printf("removendo %d\n", vet[i]);
        if (!lista_remove_ordenado(lista, &elem)){
            printf("erro remove\n");
            return 0;
        };
        i++;
    };
    return 1;
}

void imprim_lista(lista_t *l){
    nodo_t *aux;

    aux = l -> ini;
    printf("inicio: %d\n", l -> ini -> elemento -> chave);
    printf("imprimindo lista:\n");
    while (aux != NULL){
        printf("\t item: %d ", aux -> elemento -> chave);
        aux = aux -> prox;
    } 
    printf("tudo impresso\n");
}

int main(){
    lista_t *l;

    if (!(l = testa_cria())){
        printf("problema testa_cria\n");
        return 0;
    }

    if (!testa_insere(l)){
        printf("problema testa_insere\n");
        return 0;
    }
    imprim_lista(l);
    if (!testa_remove(l)){
        printf("problema testa_remove\n");
        return 0;
    }

    printf ("tudo certo\n");
    lista_destroi(&l);
    return 1;
}