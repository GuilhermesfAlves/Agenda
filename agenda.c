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
    agenda_t *agenda;
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

void imprime_status(func_t funcionarios[], taref_t tarefas[]);

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
    imprime_status(funcionarios, tarefas);
    marca_reunioes(funcionarios, tarefas);

    reunioes_realizadas = trabalha(funcionarios, tarefas);
    printf("NUMERO DE REUNIOES: %d\n", reunioes_realizadas);
    while (i<num_taref){
        if (tarefas[i].tempo_conclusao <= 0)
            tarefas_conc++;
        else 
            printf("tarefa %.2d nao cocluida, %.3d minutos restantes\n", i, tarefas[i].tempo_conclusao);
        i++;
    }
    printf("TAREFAS CONCLUIDAS %d\n", tarefas_conc);

    i = 0;
    /*destruição de todas as agendas*/
    while (i < num_func){
        destroi_agenda(funcionarios[i].agenda);
        i++;
    }
    return 0;
}



/*função que aleatoriza numeros entre um minimo e máximo*/
int ALEAT(int min, int max){

    return (rand() % (max + 1 - min)) + min;
}

void imprime_status(func_t funcionarios[], taref_t tarefas[]){
    int i; 
    i = 0;
    while (i < num_func){
        printf("funcionario %.2d lider: %.3d, exp: %.3d\n", i, funcionarios[i].lideranca, funcionarios[i].experiencia);
        i++;
    }
    printf("\n");
    i = 0;
    while (i < num_taref){
        printf("tarefa %d dificuldade %.2d tempo de conclusao: %.2d\n", i, tarefas[i].dificuldade, tarefas[i].tempo_conclusao);
        i++;
    }
    printf("\n");
}

/*função de inicialização aleatória de cada funcionario e tarefa*/
void set_func_e_taref(func_t funcionarios[], taref_t tarefas[]){
    int i=0;

    while (i<num_func){
        funcionarios[i].lideranca = ALEAT(0,100);
        funcionarios[i].experiencia = ALEAT(20,100);
        if (!(funcionarios[i].agenda = cria_agenda())){
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

compromisso_t *define_compromisso(int dia, int mes, int i_func, compromisso_t *compr_lider){
    horario_compromisso_t hora_compr;
    compromisso_t *compr;
    char *descricao;
    int id;

    if (!(descricao = malloc(35*sizeof(char)))){
        printf("erro malloc descricao lider");
        return NULL;
    }
    
    /*criação de compromisso para lider*/
    if (compr_lider == NULL){
        hora_compr.ini_h = ALEAT(8, 12);
        hora_compr.ini_m = ALEAT(0, 3) * 15;
        hora_compr.fim_h = hora_compr.ini_h + ALEAT(1, 4);
        hora_compr.fim_m = hora_compr.ini_m;
        id = ALEAT(0, num_taref - 1);
        sprintf(descricao, "REUNIR L %.2d %.2d/%.2d %.2d:%.2d %.2d:%.2d T %.2d", i_func, dia, mes, hora_compr.ini_h, hora_compr.ini_m, hora_compr.fim_h, hora_compr.fim_m, id);
        
        printf("%s", descricao);
    }

    /*replicacao de compromisso para membro da reuniao*/
    else {
        id = id_compr(compr_lider);
        hora_compr = hc_compr(compr_lider);
        sprintf(descricao, "%s", descricao_compr(compr_lider));
    }

    if (!(compr = cria_compromisso(hora_compr, id, descricao))){
        printf("erro malloc compr\n");
        return NULL;
    }

    return compr;
}


/*nesta função tentam ser marcadas 100 reuniões por mes*/
void marca_reunioes(func_t funcionarios[], taref_t tarefas[]){
    int i_lider, mes, dia, flag, qtd_func, i_func, cont_func, reun;
    compromisso_t *compr_lider, *compr_func;

    mes = JAN;
    while (mes <= DEZ){

        printf("M %.2d\n", mes);
        reun=0;
        while (reun < num_taref){

            do {
                i_lider = ALEAT(0, num_func - 1);
            } while ((funcionarios[i_lider].lideranca < 30) || (funcionarios[i_lider].lideranca > 70));

            dia = ALEAT(1, 31);
            compr_lider = define_compromisso(dia, mes, i_lider, NULL);
            flag = marca_compromisso_agenda(funcionarios[i_lider].agenda, dia, compr_lider);
            if (flag == 0){
                printf("erro malloc novo compromisso em agenda\n");
                return;
            }
            
            /*caso o lider nao possa marcar essa reunião*/
            else if (flag == -1){
                printf("\tLIDER INDISPONIVEL");
                desmarca_compromisso_agenda(funcionarios[i_lider].agenda, dia, compr_lider);
                destroi_descricao_compromisso(compr_lider);
                destroi_compromisso(compr_lider);
            }

            /*flag == 1*/
            /*sucesso em marcar o compromisso para o lider*/
            else {

                printf("\tMEMBROS ");
                qtd_func = ALEAT(2,6);
                cont_func = 0;
                while (0 < qtd_func){
                    i_func = ALEAT(0, num_func - 1);

                    if (funcionarios[i_lider].lideranca > (funcionarios[i_func].lideranca + ALEAT(-20,10))){
                        printf(" %.2d:", i_func);

                        compr_func = define_compromisso(dia, mes, i_func, compr_lider);
                        flag = marca_compromisso_agenda(funcionarios[i_func].agenda, dia, compr_func);
                        switch (flag) {
                        case -1:
                            printf("IN");
                            desmarca_compromisso_agenda(funcionarios[i_func].agenda, dia, compr_func);
                            destroi_descricao_compromisso(compr_func);
                            destroi_compromisso(compr_func);
                            break;
                        
                        case 1:
                            /*cont_func para verificar se pelo menos 1 pessoa pode ir à reunião*/
                            cont_func++;
                            printf("OK");
                            break;

                        default:
                            printf("erro malloc novo compromisso em agenda\n");
                            return;
                        }
                    }
                    qtd_func--;
                }
                /*caso nenhum funcionario se apresente disponivel para a reunião, o lider
                * desmarca esta reunião*/
                if (!cont_func){
                    printf(" VAZIA");
                    if (!desmarca_compromisso_agenda(funcionarios[i_lider].agenda, dia, compr_lider))
                        printf("not found - lider func vazia\n");
                    destroi_descricao_compromisso(compr_lider);
                    destroi_compromisso(compr_lider);
                }
            }      
            printf("\n");
            reun++;
        }

        /* este while acerta o mes de cada funcionario para próximo*/
        i_func = 0;
        while (i_func < num_func){
            prox_mes_agenda(funcionarios[i_func].agenda);
            i_func++;
        }
        mes++;
    }
}

/*procura em cada funcionario qual tem o compromisso mais recente*/
/*func == i para i o funcionario com o compromisso mais proximo
* func == -1 para não existe funcionario com compromisso neste dia*/
int encontra_menor_compr(func_t funcionarios[], int dia){
    compromisso_t *m_loc, *m_glo=NULL;
    int func=-1, i=0;

    while (i<num_func){
        if (funcionarios[i].agenda -> ptr_mes_atual -> dias)
           if (funcionarios[i].agenda -> ptr_mes_atual -> dias -> dia == dia){
                m_loc = funcionarios[i].agenda -> ptr_mes_atual -> dias -> comprs;
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
    compromisso_t *compr;
    int id, func, min_trab, cont, i, mes, dia;

    /*coloca todas as agendas no mes 1*/
    i = 0;
    while(i<num_func){
        prim_mes_agenda(funcionarios[i].agenda);
        i++;
    }

    mes = JAN;
    cont = 0;
    /*roda todas os meses em todas as agendas*/
    while (mes <= DEZ){
        /*roda todas os dias em todas os meses*/
        dia = 1;
        while (dia <= 31){
            func = encontra_menor_compr(funcionarios, dia);

            /*dentro do while rodam todos os compromissos para o dia tal*/
            while (func != -1){
                compr = funcionarios[func].agenda -> ptr_mes_atual -> dias -> comprs;
                id = id_compr(compr);

                printf("%.2d/%.2d F %.2d: %s \n",  dia, mes, func, descricao_compr(compr));
                printf("\tT %.2d D %.2d", id, tarefas[id].dificuldade);
                
                if (tarefas[id].tempo_conclusao > 0){
                    min_trab = compr -> fim - compr -> inicio;
                    tarefas[id].tempo_conclusao -= min_trab * (funcionarios[func].experiencia / 100.0) * ((100 - tarefas[id].dificuldade) / 100.0);
                    if (tarefas[id].tempo_conclusao <= 0)
                        tarefas[id].tempo_conclusao = 0;

                    printf(" TCR %.3d\n", tarefas[id].tempo_conclusao);
                    /*cont é o contador de quantas reunioes que foram marcadas foram realizadas, ou seja,
                    * tinham tarefas para se fazer nelas*/
                    cont++;
                }
                else 
                    printf(" CONCLUIDA\n");

                if (funcionarios[func].experiencia < 100)
                    funcionarios[func].experiencia++;

                desmarca_compromisso_agenda(funcionarios[func].agenda, dia, compr);
                destroi_descricao_compromisso(compr);
                destroi_compromisso(compr);
                func = encontra_menor_compr(funcionarios, dia);
            }
            dia++;
        }

        i = 0;
        /*acerta todas as agendas para o proximo mes*/
        while (i<num_func){
            prox_mes_agenda(funcionarios[i].agenda);
            i++;    
        }
        mes++;
    }
    return cont;
}