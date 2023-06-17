#include "libagenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define compr 42
#define days 25

int testa_insere(agenda_t *agenda, char vet[], int dias[]){
    horario_compromisso_t hc;
    int id;
    char *descricao;
    int i;

    while (i < compr){
        printf("insira o id:");
        scanf("%d", &id);

        printf("insira o inicio e fim");
        scanf("%d %d", &hc.ini_h, &hc.ini_m);
        scanf("%d %d", &hc.fim_h, &hc.fim_m);

        printf("insira a descricao");
        scanf("c", descricao);

        if (!marca_compromisso_agenda(agenda, dias[i], cria_compromisso(hc, id, descricao)))
            printf("compromisso não inserido");
        
        i++;
    }
    return 1;
}

int testa_remove(agenda_t *agenda, char vet[], int dias[]){
    int i=0;

    while(i < compr){
        printf("removendo id: %d\n", vet[i]);
        if (!lista_remove_ordenado(agenda, &vet[i])){
            printf("erro remove\n");
            return 0;
        };
        i++;
    };
    return 1;
}

void set_element(char vet[], int dias[]){
    int i=0;

    srand((unsigned)time(0));
    while (i < compr){

        vet[i] = (char)rand() % 128;
        printf("elemento %d setado: %c\n", i, vet[i]);
        i++;
    }

    while (i < days) {
        dias[i] = rand() % 30;
        printf("dia %d setado: %d\n", i, dias[i]);
        i++;
    }
    
}

int main(){
    agenda_t ag, *agenda;
    char vet[compr];
    int dias[days];

    agenda = &ag;
    set_element(vet,dias);

    if (!testa_insere(agenda,vet, dias)){
        printf("problema testa_insere\n");
        return 1;
    }

    imprime_agenda_mes(agenda);

    if (!testa_remove(agenda, vet, dias)){
        printf("problema testa_remove\n");
        return 1;
    }

    printf ("tudo certo\n");
    destroi_agenda(agenda);
    return 0;
}


