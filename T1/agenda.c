#include "libagenda.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define JAN 1
#define DEZ 12
#define num_func 30
#define num_taref 100

/*tipo funcionario que possui liderança, experiencia
* e uma agenda associada para cada*/
typedef struct func{
    int lideranca;
    int experiencia;
    agenda_t agenda;
}func_t;

/*tipo tarefa que possui um tempo de conclusão 
* e dificuldade associada para cada*/
typedef struct taref{
    int tempo_conclusao;
    int dificuldade;
}taref_t;

/*função que aleatoriza numeros entre um minimo e máximo*/
int ALEAT(int min, int max);

/*função de inicialização aleatória de cada funcionario e tarefa*/
void set_func_e_taref(func_t funcionarios[], taref_t tarefas[]);

void imprime_status(func_t funcionarios[]);
/*função para inicializar o mes de janeiro na agenda de cada funcionario*/
int inicia_agendas(agenda_t *agenda);

/**/
void marca_reunioes(func_t funcionarios[], taref_t tarefas[]);

int trabalha(func_t funcionarios[], taref_t tarefas[]);


int main(){
    func_t funcionarios[num_func];
    taref_t tarefas[num_taref];
    int reunioes_realizadas, tarefas_conc=0,i=0;

    /*Inicialização*/
    /*srand((unsigned)time(0));*/
    set_func_e_taref(funcionarios, tarefas);
    imprime_status(funcionarios);
    marca_reunioes(funcionarios, tarefas);

    reunioes_realizadas = trabalha(funcionarios, tarefas);
    printf("NUMERO DE REUNIOES: %d\n", reunioes_realizadas);
    while (i<num_taref){
        if (tarefas[i].tempo_conclusao <= 0)
            tarefas_conc++;
        else 
            printf("tarefa %d nao cocluida: %d\n", i, tarefas[i].tempo_conclusao);
        i++;
    }
    printf("TAREFAS CONCLUIDAS %d\n", tarefas_conc);

    i = 0;
    /*destruição de todas as agendas*/
    while (i < num_func){
        destroi_agenda(&funcionarios[i].agenda);
        i++;
    }
    return 0;
}


/*função que aleatoriza numeros entre um minimo e máximo*/
int ALEAT(int min, int max){

    return (rand() % (max + 1 - min)) + min;
}

void imprime_status(func_t funcionarios[]){
    int i=0;
    while (i < num_func){
        printf("funcionario %.2d lider: %.3d, exp: %.3d\n", i, funcionarios[i].lideranca, funcionarios[i].experiencia);
        i++;
    }
}

/*função de inicialização aleatória de cada funcionario e tarefa*/
void set_func_e_taref(func_t funcionarios[], taref_t tarefas[]){
    int i=0;

    while (i<num_func){
        funcionarios[i].lideranca = ALEAT(0,100);
        funcionarios[i].experiencia = ALEAT(20,100);
        if (!inicia_agendas(&funcionarios[i].agenda)){
            printf("erro alocacao janeiro em %d", i);
            return;
        }
        i++;
    }
    i = 0;
    while (i<num_taref){
        tarefas[i].tempo_conclusao = ALEAT(600,800);
        tarefas[i].dificuldade = ALEAT(30,80);
        i++;
    }
}

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

/*nesta função tentam ser marcadas 100 reuniões por mes*/
void marca_reunioes(func_t funcionarios[], taref_t tarefas[]){
    int i,i_lider, mes = JAN, dia, id, flag, qtd_func, i_func, cont_func, cont_reun=0, cont_indisp=0, reun;
    horario_compromisso_t hc_compr;
    compromisso_t *compr_lider, *compr_func;
    char *descr_lider, *descr_func;

    /*srand((unsigned)time(0));*/
    while (mes<=DEZ){

        printf("M %.2d\n", mes);
        reun=0;
        while (reun<num_taref){

            do {
                i_lider = ALEAT(0, num_func - 1);
            } while((funcionarios[i_lider].lideranca < 30) || (funcionarios[i_lider].lideranca > 70));

            if (!(descr_lider = malloc(51*sizeof(char))))
                return;

            hc_compr.ini_h = ALEAT(8, 12);
            hc_compr.ini_m = ALEAT(0, 3) * 15;
            hc_compr.fim_h = hc_compr.ini_h + ALEAT(1, 4);
            hc_compr.fim_m = hc_compr.ini_m;
            dia = ALEAT(1, 31);
            id = ALEAT(0, num_taref - 1);
            sprintf(descr_lider, "REUNIR L %.2d %.2d/%.2d %.2d:%.2d %.2d:%.2d T %.2d", i_lider, dia, mes, hc_compr.ini_h, hc_compr.ini_m, hc_compr.fim_h, hc_compr.fim_m, id);

            printf("%s", descr_lider);

            if (!(compr_lider = cria_compromisso(hc_compr, id, descr_lider))){
                printf("erro malloc compr\n");
                return;
            }

            while (mes != funcionarios[i_lider].agenda.mes_atual){
                if (!prox_mes_agenda(&funcionarios[i_lider].agenda)){
                    printf("erro malloc proximo mes lider\n");
                    break;
                }   
            }

            flag = marca_compromisso_agenda(&funcionarios[i_lider].agenda, dia, compr_lider);
            if (flag == 0){
                printf("erro malloc novo compromisso em agenda\n");
                return;
            }

            else if (flag == 1){

                qtd_func = ALEAT(2,6);
                cont_func = 0;
                printf("\tMEMBROS ");
                i = 0;    
                while (i<qtd_func){

                    i_func = ALEAT(0, num_func-1);

                    if (funcionarios[i_lider].lideranca > (funcionarios[i_func].lideranca + ALEAT(-20,10))){
                        printf(" %.2d:", i_func);

                        if (!(descr_func = malloc(51*sizeof(char))))
                            printf("erro malloc descricao func");

                        sprintf(descr_func, "%s", descr_lider);

                        compr_func = cria_compromisso(hc_compr, id, descr_func);

                        /*caso o funcionario esteja com a agenda ainda apontando para outro mes anterior,
                        * este while acertaria o mes certo do compromisso*/
                        while (mes != funcionarios[i_func].agenda.mes_atual){
                            if (!prox_mes_agenda(&funcionarios[i_func].agenda)){
                                printf("erro malloc proximo mes func\n");
                                return;
                            }
                        }

                        flag = marca_compromisso_agenda(&funcionarios[i_func].agenda, dia, compr_func);
                        /*caso o retorno de marca_compromisso_agenda seja -1, ou seja uma intersecção
                        * o compromisso não sera marcado com este funcionario*/    
                        if (flag == 0){
                            printf("erro malloc novo compromisso em agenda\n");
                            return;
                        }
                        /*cont para verificar se pelo menos 1 pessoa pode ir à reunião*/
                        if (flag == 1){
                            cont_func++;
                            printf(" OK");
                        }
                        else {
                            printf(" IN");
                            if (!desmarca_compromisso_agenda(&funcionarios[i_func].agenda, dia, compr_func))
                                printf("not found - i func\n");
                        }
                    }
                    i++;
                }
                /*caso nenhum funcionario se apresente disponivel para a reunião, o lider
                * desmarca esta reunião*/
                if (!cont_func){
                    printf(" VAZIA");
                    if (!desmarca_compromisso_agenda(&funcionarios[i_lider].agenda, dia, compr_lider))
                        printf("not found - lider func vazia\n");
                }
                else 
                    cont_reun++;
            }
            /*flag == -1*/
            /*caso o lider nao possa marcar essa reunião*/
            else {
                printf("\tLIDER INDISPONIVEL");
                cont_indisp++;
                if (!desmarca_compromisso_agenda(&funcionarios[i_lider].agenda, dia, compr_lider))
                    printf("not found - lider func indisponivel");
            }
            printf("\n");
            reun++;
        }
        mes++;
    }
    printf("indisponiveis: %d\n", cont_indisp);
}

/*procura em cada funcionario qual tem o compromisso mais recente*/
int encontra_menor_compr(func_t funcionarios[], int day){
    compromisso_t *m_loc=NULL, *m_glo=NULL;
    int func=-1, i=0;

    while (i<num_func){
        if (funcionarios[i].agenda.ptr_mes_atual -> dias)
           if (funcionarios[i].agenda.ptr_mes_atual -> dias -> dia == day){
                m_loc = funcionarios[i].agenda.ptr_mes_atual -> dias -> comprs;
                if ((!m_glo) || ((m_loc -> inicio) < (m_glo -> inicio))){
                    m_glo = m_loc;
                    func = i;
                }
            }
        i++;
    }
    return func;
}

/*em trabalha os compromissos marcados nas agendas dos funcionarios
* são seguidos em ordem cronológica e então faz o decréscimo de tempo
* necessário para realizar a tarefa*/
int trabalha(func_t funcionarios[], taref_t tarefas[]){
    compromisso_t *aux_compr;
    int id, func, min_trab, cont=0, i=0, mes=JAN, dia=1;

    /*coloca todas as agendas no mes 1*/
    while(i<num_func){
        prim_mes_agenda(&funcionarios[i].agenda);
        i++;
    }

    /*roda todas os meses em todas as agendas*/
    while (mes<=DEZ){
        /*roda todas os dias em todas os meses*/
        dia = 0;
        while (dia<=31){
            func = encontra_menor_compr(funcionarios, dia);

            /*dentro do while rodam todos os compromissos para o dia tal*/
            while (func != -1){
                aux_compr = funcionarios[func].agenda.ptr_mes_atual -> dias -> comprs;
                id = id_compr(aux_compr);

                printf("%.2d/%.2d F %.2d: %s \n",  dia, mes, func, descricao_compr(aux_compr));
                printf("\tT %.2d D %.2d", id, tarefas[id].dificuldade);
                
                if (tarefas[id].tempo_conclusao > 0){
                    min_trab = aux_compr -> fim - aux_compr -> inicio;
                    printf(" TCR %.3d\n", tarefas[id].tempo_conclusao);
                    tarefas[id].tempo_conclusao -= min_trab * (funcionarios[func].experiencia / 100.0) * ((100 - tarefas[id].dificuldade) / 100.0);

                    cont++;
                }
                else
                    printf(" CONCLUIDA\n");

                if (funcionarios[func].experiencia < 100)
                    funcionarios[func].experiencia++;

                desmarca_compromisso_agenda(&funcionarios[func].agenda, dia, aux_compr);
                func = encontra_menor_compr(funcionarios, dia);
            }
            dia++;
        }

        i = 0;
        /*acerta todas as agendas para o proximo mes*/
        while (i<num_func){
            prox_mes_agenda(&funcionarios[i].agenda);
            i++;    
        }
        mes++;
    }
    return cont;
}