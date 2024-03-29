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

#ifndef LISTA_ORD
#define LISTA_ORD
/*
 * elemento_t possui o campo chave, quem sabe pode ter mais coisas depois
*/
typedef struct elemento {
    int chave;  /* chave da struct */
    /* pode ter mais campos, mas a chave sera usada sempre nas operacoes */
} elemento_t;

/*
 * nodo_t eh uma estrutura interna que representa cada nodo da Lista.
 * Externamente o usuario da biblioteca nao vai poder usa-la, pois
 * nao pode ter acesso direto ao ponteiro prox.
*/
typedef struct nodo {
    elemento_t *elemento;
    struct nodo *prox;
} nodo_t;

/*
 * Representacao da Lista 
*/
typedef struct lista {
    nodo_t *ini;
} lista_t;

/* 
 * Cria uma Lista vazia 
*/
lista_t *lista_cria ();

/* 
 * Destroi a Lista e a aponta para NULL
*/ 
void lista_destroi (lista_t **l);

/* 
 * Adiciona um elemento em ordem de acordo com o valor elemento->chave na Lista. 
 * Retorna 1 em caso de sucesso e 0 caso contrario.
*/
int lista_insere_ordenado (lista_t *l, elemento_t *elemento);

/* 
 * Retira o elemento da Lista e a mantem em ordem.
 * Retorna 1 em caso de sucesso e 0 caso elemento nao esteja na Lista.
*/
int lista_remove_ordenado (lista_t *l, elemento_t *elemento);

#endif