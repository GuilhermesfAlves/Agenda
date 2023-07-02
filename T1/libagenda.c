#include "libagenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define JAN 1
#define DEZ 12
#define num_func 30
#define num_taref 100

/* Cria uma agenda vazia:
*  O mes_atual deve ser inicializado com 1; ptr_mes_atual deve ser definido. */
agenda_t* cria_agenda(){
    agenda_t *agenda;
    mes_t *mes;

    if (!(agenda = malloc(sizeof(agenda_t)))){
        printf("erro alocação agenda");
        return NULL;
    }

    if (!(mes = malloc(sizeof(mes_t)))){
        printf("erro alocação primeiro mes\n");
        return NULL;
    }

    agenda -> ptr_mes_atual = mes;
    agenda -> ptr_mes_atual -> ant = agenda -> ptr_mes_atual;
    agenda -> ptr_mes_atual -> prox = agenda -> ptr_mes_atual;
    agenda -> ptr_mes_atual -> dias = NULL;
    agenda -> ptr_mes_atual -> mes = JAN;
    agenda -> mes_atual = JAN;

    return agenda;
}

/* Cria um compromisso:
   Retorna um compromisso com as informacoes de data de hc, um identificador
   id e uma string de descricao. A funcao deve alocar um novo espaco de 
   armazenamento para receber a string descricao. */ 
compromisso_t* cria_compromisso (horario_compromisso_t hc, int id,  char* descricao){
    compromisso_t *compr;

    if (!(compr = malloc(sizeof(compromisso_t))))
        return NULL;
    
    compr -> id = id;
    compr -> descricao = descricao;
    compr -> inicio = hc.ini_h*60 + hc.ini_m;
    compr -> fim = hc.fim_h*60 + hc.fim_m;
    compr -> prox = NULL;

    return compr;
}

/* destroi a descricao de um compromisso */
void destroi_descricao_compromisso(compromisso_t* compr){

    free(compr -> descricao);
}

/* destroi um compromisso */
void destroi_compromisso(compromisso_t* compr){

    free(compr);
}


/* Libera toda memoria associado a agenda. */
void destroi_agenda(agenda_t* agenda){
    mes_t *aux_mes;
    dia_t *aux_dia;
    compromisso_t *aux_compr;
    
    aux_mes = agenda -> ptr_mes_atual;
   
   /*exclui todos os compromissos para cada mes*/
    while (aux_mes -> dias) {
        aux_dia = aux_mes -> dias;
        
        while (aux_dia){
            aux_compr = aux_dia -> comprs;
        
            while (aux_compr){
                destroi_compromisso(prox_compr(aux_compr));
            }
        
            aux_mes -> dias = aux_dia -> prox;
            free(aux_dia);
            aux_dia = aux_mes -> dias;
        }

        aux_mes = aux_mes -> prox;
    }
    
    /*exclui todos os meses*/
    while (aux_mes -> prox != aux_mes){
        agenda -> ptr_mes_atual = aux_mes -> prox;
        aux_mes -> ant -> prox = aux_mes -> prox;
        aux_mes -> prox -> ant = aux_mes -> ant;
        free(aux_mes);
        aux_mes = agenda -> ptr_mes_atual;
    }

    free(aux_mes);
    free(agenda);
    agenda = NULL;

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
    dia_t *aux_dia, *novo_dia;
    compromisso_t *aux_compr;

    if (!(novo_dia = malloc(sizeof(dia_t))))
        return 0;

    novo_dia -> comprs = compr;
    novo_dia -> dia = dia;
    aux_dia = agenda -> ptr_mes_atual -> dias;
   
   /*caso onde se coloca na primeira posição*/
    if ((!aux_dia) || (aux_dia -> dia > novo_dia -> dia)){
        novo_dia -> prox = aux_dia;
        agenda -> ptr_mes_atual -> dias = novo_dia;
    }

    else {
        if (aux_dia -> dia != novo_dia -> dia){
            /*corredor de dias*/
            while ((aux_dia -> prox) && (aux_dia -> prox -> dia <= novo_dia -> dia))
                aux_dia = aux_dia -> prox;
        }

        /*novo compromisso em um dia ja alocado*/
        if (aux_dia -> dia == novo_dia -> dia){    
            free(novo_dia);
            aux_compr = aux_dia -> comprs;

            /*caso onde o compromisso é antes de qualquer um*/
            if ((!aux_compr) || (compr -> inicio < aux_compr -> inicio)){
                compr -> prox = aux_compr;
                aux_dia -> comprs = compr; 
            }

            else {
                /*corredor de compromissos*/
                while ((aux_compr -> prox) && (compr -> inicio > aux_compr -> prox -> inicio))
                    aux_compr = aux_compr -> prox;

                compr -> prox = aux_compr -> prox;
                aux_compr -> prox = compr;
            }

            aux_compr = aux_dia -> comprs;
            while (aux_compr){
                printf("(%d)",aux_compr -> id);
                aux_compr = aux_compr -> prox;
            }
            
            /*confere intersecçao*/
            aux_compr = aux_dia -> comprs;
            while (aux_compr -> prox) {
                if (aux_compr -> fim > aux_compr -> prox -> inicio)
                    return -1;
                aux_compr = aux_compr -> prox;    
            }
        }
        else {
            /*compromisso em um dia ainda nao alocado*/
            novo_dia -> prox = aux_dia -> prox;
            aux_dia -> prox = novo_dia;
        } 
    }
    return 1;
}

/* Desmarca o compromisso compr da agenda:
   O parametro compr eh um ponteiro para um compromisso existente da agenda.
   valores de retorno possiveis:
      1: em caso de sucesso
      0: caso nao tenha encontrado o compr */
int desmarca_compromisso_agenda(agenda_t* agenda, int dia, compromisso_t* compr){
    compromisso_t *aux_compr;
    dia_t *aux_dia, *aux2_dia;

    aux_dia = agenda -> ptr_mes_atual -> dias;
    if (!aux_dia)
        return 0;
        
    /*caso onde nao eh o primeiro dia do mes*/
    if (aux_dia -> dia != dia){
        /*corredor de dias*/
        while ((aux_dia -> prox) && (aux_dia -> prox -> dia != dia))
            aux_dia = aux_dia -> prox;
        
        /*nao achou o dia*/
        if (!aux_dia -> prox)
            return 0;
        
        /*logica para dia diferente do primeiro*/
        aux_compr = aux_dia -> prox -> comprs;
        if (!aux_compr)
            return 0;

        if (aux_compr != compr){
            while ((aux_compr -> prox) && (aux_compr -> prox != compr))
                aux_compr = aux_compr -> prox;
           
            if (!aux_compr -> prox)
                return 0;
            
            /*tira o compromisso*/
            aux_compr -> prox = aux_compr -> prox -> prox;
        }
        /*primeiro compromisso do dia*/
        else {
            /*tira o compromisso*/
            aux_dia -> prox -> comprs = aux_compr -> prox;

            /*libera o dia se todos os compromissos nele ja tiverem
            * sido liberados*/
            if (!aux_dia -> prox -> comprs){
                aux2_dia = aux_dia -> prox -> prox; 
                free(aux_dia -> prox);
                aux_dia -> prox = aux2_dia;
            }
        }
    }

    /*caso onde eh o primeiro dia do mes*/
    else {
        aux_compr = aux_dia -> comprs;
        /*caso onde nao eh o primeiro compromisso do dia*/
        if (aux_compr != compr){
            /*corredor de compromissos*/
            while ((aux_compr -> prox) && (aux_compr -> prox != compr))
                aux_compr = aux_compr -> prox;
            
            /*nao achou os compromissos*/
            if (!aux_compr -> prox)
                return 0;
            
            aux_compr -> prox = aux_compr -> prox -> prox;
        }
        /*primeiro compromisso do dia*/
        else {
            aux_dia -> comprs = aux_compr -> prox;

            if (!aux_dia -> comprs){
                agenda -> ptr_mes_atual -> dias = aux_dia -> prox;
                free(aux_dia);
            }
        }
    }
    return 1;
}

/* Imprime a agenda do mes atual (mes atual) */
void imprime_agenda_mes(agenda_t* agenda){
    dia_t *dia;
    compromisso_t *compr;

    printf("MES: %.2d\n ", agenda -> mes_atual);
    dia = agenda -> ptr_mes_atual -> dias;

    while (dia) {
        printf("DIA: %.2d\n ", dia -> dia);
        compr = dia -> comprs; 

        while (compr){
            printf("\t ID: %.2d ", id_compr(compr));
            printf("\t descricao: %s ", descricao_compr(compr));
            printf("\t dia: %2.d ", dia -> dia);
            printf("\t mes: %.2d ", agenda -> mes_atual);
            printf("\t inicio: %4d ", compr -> inicio);
            printf("\t fim: %4d ", compr -> fim);
            printf("\n");
            compr = compr -> prox;
        } 
        
        printf("-------\n");
        dia = dia -> prox;
    };
    
    printf ("**********\n");
}

/* Retorna o mes atual da agenda. */
int mes_atual_agenda(agenda_t *agenda){

    return agenda -> mes_atual;
}

/* Ajusta o mes_atual para 1; caso o mes esteja alocado, ptr_mes_atual
 * apontara para o mes 1, caso contrario para NULL. */
void prim_mes_agenda(agenda_t* agenda){
    mes_t *mes;

    mes = agenda -> ptr_mes_atual;

    if (mes){ 
        while (mes -> mes != JAN){
            mes = mes -> prox;
            if (mes == agenda -> ptr_mes_atual){
                agenda -> mes_atual = 0;
                agenda -> ptr_mes_atual = NULL;
                return;
            }
        }
        agenda -> ptr_mes_atual = mes;
        agenda -> mes_atual = JAN;
    }
}

/* Avanca a agenda para o proximo mes, incrementando mes_atual.
 * O ponteiro ptr_mes_atual deve ser atualizado para apontar para o novo mes_atual.
 * Se o novo mes_atual nao existir deve ser alocado. A funcao retorna o inteiro 
 * mes_atual em caso de sucesso ou 0 caso contrario.  */ 
int prox_mes_agenda(agenda_t* agenda){
    mes_t *mes;

    if ((agenda -> ptr_mes_atual -> prox -> mes != agenda -> mes_atual + 1))
        if ((agenda -> mes_atual != DEZ) || (agenda -> ptr_mes_atual -> prox -> mes != JAN)){
            if (!(mes = malloc(sizeof(mes_t))))
                return 0;

            mes -> dias = NULL;
            mes -> mes = agenda -> mes_atual + 1;
            if (mes -> mes > DEZ)
                mes -> mes = JAN;

            mes -> prox = agenda -> ptr_mes_atual -> prox;
            mes -> ant = agenda -> ptr_mes_atual;
            agenda -> ptr_mes_atual -> prox -> ant = mes;
            agenda -> ptr_mes_atual -> prox = mes;
        }

    agenda -> ptr_mes_atual = agenda -> ptr_mes_atual -> prox;
    agenda -> mes_atual = agenda -> ptr_mes_atual -> mes;
        
    return mes_atual_agenda(agenda);
}

/* Analogo ao prox_mes_agenda porem decrementa mes_atual. */ 
int ant_mes_agenda(agenda_t* agenda){
    mes_t *mes;

    if ((agenda -> ptr_mes_atual -> ant -> mes != agenda -> mes_atual - 1))
        if ((agenda -> mes_atual != JAN) || (agenda -> ptr_mes_atual -> ant -> mes != DEZ)){
            if (!(mes = malloc(sizeof(mes_t))))
                return 0;

            mes -> dias = NULL;
            mes -> mes = agenda -> mes_atual - 1;
            if (mes -> mes < JAN)
                mes -> mes = DEZ;

            mes -> prox = agenda -> ptr_mes_atual;
            mes -> ant = agenda -> ptr_mes_atual -> ant;
            agenda -> ptr_mes_atual -> ant -> prox = mes;
            agenda -> ptr_mes_atual -> ant = mes;
        }

    agenda -> ptr_mes_atual = agenda -> ptr_mes_atual -> ant;
    agenda -> mes_atual = agenda -> ptr_mes_atual -> mes;    
        
    return mes_atual_agenda(agenda);    
}

/* Retorna um ponteiro para a lista ligada de compromissos de um dia do mes
   ou NULL se vazia. A lista de compromissos retornada pode ser percorrida
   usando-se a funcao prox_compr. */ 
compromisso_t* compr_agenda(agenda_t* agenda, int dia){
    dia_t *dia_aux;

    dia_aux = agenda -> ptr_mes_atual -> dias;
    while ((dia_aux) && (dia_aux -> dia != dia))
        dia_aux = dia_aux -> prox;

    if (!dia_aux)
        return NULL;

    return dia_aux -> comprs;
}

/* Retorna o primeiro compromisso da lista de compromissos compr e avanca
 * para o prox. Retorna NULL se a lista esta vazia, ou seja, sem compromissos.*/
compromisso_t* prox_compr(compromisso_t* compr){
    compromisso_t *atual;

    atual = compr;
    if (atual)
        compr = compr -> prox;

    return atual;
}

/* traduz os minutos desde 00:00 para horas de inicio e fim*/
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
