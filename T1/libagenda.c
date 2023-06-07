#include <stdio.h>
#include <stdlib.h>
#include "libagenda.h"

/* Cria um compromisso:
   Retorna um compromisso com as informacoes de data de hc, um identificador
   id e uma string de descricao. A funcao deve alocar um novo espaco de 
   armazenamento para receber a string descricao. */ 
compromisso_t* cria_compromisso (horario_compromisso_t hc, int id,  char* descricao){

}

/* Libera toda memoria associado a agenda. */
void destroi_agenda(agenda_t* agenda){

}

/* Marca um compromisso na agenda:
   valores de retorno possiveis:
    -1: compromisso tem interseccao com outro
     0: erro de alocacao de memoria
     1: sucesso

    A lista de compromisso eh ordenada pelo horario de inicio. Eh necessario
    testar a interseccao entre horarios de inicio e de fim no compromisso novo
    considerando o  compromisso anterior e o proximo, caso existam. */
int marca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr){

}

/* Desmarca o compromisso compr da agenda:
   O parametro compr eh um ponteiro para um compromisso existente da agenda.
   valores de retorno possiveis:
    1: em caso de sucesso
    0: caso nao tenha encontrado o compr */
int desmarca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr){

}

/* Imprime a agenda do mes atual (mes atual) */
void imprime_agenda_mes(agenda_t* agenda){
    compromisso_t *compr;

    do {
        printf("DIA: %d, ", agenda -> ptr_mes_atual -> dias -> dia);
        compr = agenda -> ptr_mes_atual -> dias -> comprs; 
        while (compr){
            printf("ID: %d \t", id_compr(compr));
            printf("descricao: %c \t", descricao_compr(compr));
            printf("\n");
            prox_compr(compr);
        } 
        printf("-------\n");
    } while (agenda -> ptr_mes_atual -> dias -> prox != NULL);
    printf ("**********\n");
}

/* Retorna o mes atual da agenda. */
int mes_atual_agenda(agenda_t *agenda){

    return agenda -> mes_atual;
}

/* Ajusta o mes_atual para 1; caso o mes esteja alocado, ptr_mes_atual
 * apontara para o mes 1, caso contrario para NULL. */
void prim_mes_agenda(agenda_t* agenda){
    
    while (prox_mes_agenda(agenda) != 1){}
}

/* Avanca a agenda para o proximo mes, incrementando mes_atual.
 * O ponteiro ptr_mes_atual deve ser atualizado para apontar para o novo mes_atual.
 * Se o novo mes_atual nao existir deve ser alocado. A funcao retorna o inteiro 
 * mes_atual em caso de sucesso ou 0 caso contrario.  */ 
int prox_mes_agenda(agenda_t* agenda){
    mes_t *mes;

    if (!agenda -> ptr_mes_atual -> prox)
        if (!(mes = malloc(sizeof(mes_t))))
            return 0;

    agenda -> ptr_mes_atual = agenda -> ptr_mes_atual -> prox;
    agenda -> mes_atual = agenda -> ptr_mes_atual -> mes;
    return 1;
}

/* Analogo ao prox_mes_agenda porem decrementa mes_atual. */ 
int ant_mes_agenda(agenda_t* agenda){
    mes_t *mes;

    if (!agenda -> ptr_mes_atual -> ant)
        if (!(mes = malloc(sizeof(mes_t))))
            return 0;
    
    agenda -> ptr_mes_atual = agenda -> ptr_mes_atual -> ant;
    agenda -> mes_atual = agenda -> ptr_mes_atual -> mes;
    return 1;    
}

/* Retorna um ponteiro para a lista ligada de compromissos de um dia do mes
   ou NULL se vazia. A lista de compromissos retornada pode ser percorrida
   usando-se a funcao prox_compr. */ 
compromisso_t* compr_agenda(agenda_t* agenda, int dia){
    mes_t *mes;
    dia_t *dia_aux;

    mes = mes_atual_agenda(agenda);
    dia_aux = mes -> dias;
    while (dia_aux -> dia != dia)
        dia_aux = dia_aux -> prox;

    return dia_aux -> comprs;
}

/* Retorna o primeiro compromisso da lista de compromissos compr e avanca
 * para o prox. Retorna NULL se a lista esta vazia, ou seja, sem compromissos.*/
compromisso_t* prox_compr(compromisso_t* compr){
    compromisso_t *atual;

    atual = compr;
    compr = compr -> prox;
    return atual;
}

/* funcoes getters */
horario_compromisso_t hc_compr(compromisso_t* compr){
    horario_compromisso_t horas;

    horas.ini_h = compr -> inicio / 60;
    horas.ini_m = compr -> inicio - horas.ini_h*60; 
    horas.fim_h = compr -> fim / 60;
    horas.fim_m = compr -> fim - horas.fim_h*60;
    return horas;
} 

int id_compr(compromisso_t* compr){
    return compr -> id;
}

char* descricao_compr(compromisso_t* compr){
    return compr -> descricao;
} 

/* Essa funcao nao eh extritamente necessaria, o objetivo e' que o programa
principal apresente os dados. Porem pode ser util para voces durante o desenvolvimento */ 
void imprime_agenda_mes(agenda_t* agenda){
    horario_compromisso_t hora_compr;

    prim_mes_agenda(agenda);
    do {
        printf("MES: %d\n ", mes_atual_agenda(agenda));
        imprime_agenda_mes(agenda);
        prox_mes_agenda(agenda);
    } while (mes_atual_agenda(agenda) != 1);
}