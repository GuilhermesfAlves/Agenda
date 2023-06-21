#include "libagenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define days 30
#define JAN 1
#define DEZ 12
#define num_func 30
#define num_taref 30


int inicia_agendas(agenda_t *agenda){
    mes_t *mes;

    if (!(mes = malloc(sizeof(mes_t)))){
        printf("erro alocação primeiro mes\n");
        return 0;
    }

    agenda -> ptr_mes_atual = mes;
    agenda -> ptr_mes_atual -> ant = agenda -> ptr_mes_atual;
    agenda -> ptr_mes_atual -> prox = agenda -> ptr_mes_atual;
    agenda -> ptr_mes_atual -> dias = NULL;
    agenda -> ptr_mes_atual -> mes = JAN;
    agenda -> mes_atual = JAN;

    return 1;
}


int ALEAT(int min, int max){

    if (max + 1 - min == 0)
        return rand() + min;

    return (rand() % (max + 1 - min)) + min;
}

int testa_insere(agenda_t *agenda, char *vet[], int dias[], compromisso_t *compromisso[]){
    horario_compromisso_t hc_compr;
    int id, flag;

    for (int i=0;i < num_taref; i++){
        hc_compr.ini_h = ALEAT(8,12);
        hc_compr.ini_m = ALEAT(0,3) * 15;
        hc_compr.fim_h = hc_compr.ini_h + ALEAT (1,4);
        hc_compr.fim_m = hc_compr.ini_m;
        id = i;

        printf("inserindo %d elem. ", id);
        if (!(compromisso[i] = malloc(sizeof(compromisso_t))))
            return 0;

        compromisso[i] = cria_compromisso(hc_compr, id, vet[i]);

        if (!compromisso[i]){
            printf("erro criação compromisso");
        }
        flag = marca_compromisso_agenda(agenda, dias[i], compromisso[i]);
        if (!flag){
            printf("compromisso não inserido");
            return 0;
        }
        else if (flag == -1){
            desmarca_compromisso_agenda(agenda, dias[i], compromisso[i]);
        }
        printf("inserido\n");
    }
    return 1;
}

int testa_remove(agenda_t *agenda, int dias[], compromisso_t *compromisso[]){

    for (int i=0;i < num_taref; i++){
        if (compromisso[i] != NULL){
            printf("removendo id: %d\n", id_compr(compromisso[i]));
            if (!desmarca_compromisso_agenda(agenda, dias[i], compromisso[i])){
                printf("erro remove\n");
                return 0;
            }
        }
    }
    return 1;
}

void set_element(char *vet[], int dias[]){

    srand((unsigned)time(0));
    for (int i=0;i < num_taref; i++){
        if (!(vet[i] = malloc(6*sizeof(char))))
            return;

        sprintf(vet[i], "D%.2d", rand() % 200);
        printf("elemento %.2d setado: %s\n", i, vet[i]);
    }

    for (int i=0; i < days; i++) {
        dias[i] = rand() % 30;
        printf("dia %d setado: %d\n", i, dias[i]);
    }
    printf("sim set_element\n");
}

void tenta_encher_agenda(agenda_t *agenda, int d){
    horario_compromisso_t hc;
    compromisso_t *aux_compr;

    for (int i=0; i< 30; i++){
        hc.ini_h = i;
        hc.ini_m = 0;
        hc.fim_h = i+1;
        hc.fim_m = 0;
        marca_compromisso_agenda(agenda, d, cria_compromisso(hc, i, NULL));
        aux_compr = agenda -> ptr_mes_atual -> dias -> comprs;
        do {
            printf("ID: %.2d, hc ini: %.3d, hc fim %.3d\n", id_compr(aux_compr), aux_compr -> inicio, aux_compr -> fim);
            aux_compr = aux_compr -> prox;
        } while (aux_compr);
        printf("\n");
    }
    printf("\n");
}

int main(){
    agenda_t ag, *agenda;
    compromisso_t *compromisso[num_taref];
    char *vet[num_taref];
    int dias[days];

    printf("tamanho de blocos: compr:%ld, dia:%ld, mes:%ld, agenda:%ld\n", sizeof(compromisso_t), sizeof(dia_t), sizeof(mes_t), sizeof(agenda_t));


    agenda = &ag;
    //set_element(vet, dias);
 
    if (!inicia_agendas(agenda))
        printf("inicia a agenda errado");
    printf("iniciou agenda\n");

    for (int d=0; d<30; d++){
        tenta_encher_agenda(agenda,d);
    }
    imprime_agenda_mes(agenda);

/*
    if (!testa_insere(agenda, vet, dias, compromisso)){
        printf("problema testa_insere\n");
        return 1;
    }

    imprime_agenda_mes(agenda);

    if (!testa_remove(agenda, dias, compromisso)){
        printf("problema testa_remove\n");
        return 1;
    }
*/
    printf ("tudo certo\n");
    destroi_agenda(agenda);
    return 0;
}
