#include "libfuncs.h"

/*função que aleatoriza numeros entre um minimo e máximo*/
int ALEAT(int min, int max){

    srand((unsigned)time(0));
    return (rand() % (max + 1)) + min;
}

/*função de inicialização aleatória de cada funcionario e tarefa*/
void set_func_e_taref(func_t funcionarios[], taref_t tarefas[]){
    
    for (int i=0; i<num_func; i++){
        funcionarios[i].lideranca = ALEAT(0,100);
        funcionarios[i].experiencia = ALEAT(20,100);
    }
    for (int i=0; i<num_taref; i++){
        tarefas[i].tempo_conclusao = ALEAT(600,800);
        tarefas[i].dificuldade = ALEAT(30,80);
    }
}

void marca_reunioes(func_t funcionarios[], taref_t tarefas[]){
    int lider_num, dia, id, flag, qtd_func, func_num, cont;
    horario_compromisso_t hc_compr;
    compromisso_t *compr;
    char descricao;

    for (int mes=JAN; mes<=DEZ; mes++){
        for (int reun=0;reun<num_taref;reun++){
            do {
                lider_num = ALEAT(0, num_func);
            } while((funcionarios[lider_num].lideranca > 30) && (funcionarios[lider_num].lideranca < 70));
            
            hc_compr.ini_h = ALEAT(8,12);
            hc_compr.ini_m = ALEAT(0,3) * 15;
            hc_compr.fim_h = hc_compr.ini_h + ALEAT (1,4);
            hc_compr.fim_m = hc_compr.ini_m;
            dia = ALEAT(1,31);
            id = ALEAT(0,reun-1);
            sprintf(descricao, "REUNIR L %.2d %.2d/%.2d %.2d:%.2d %.2d:%.2d T %.2d", lider_num, dia, mes, hc_compr.ini_h, hc_compr.ini_m, hc_compr.fim_h, hc_compr.fim_m, reun);

            compr = cria_compromisso(hc_compr,id,descricao);
            if (!compr){
                printf("erro malloc compr");
                return;
            }

            flag = marca_compromisso_agenda(&funcionarios[lider_num].agenda, dia, compr);
            if (!flag){
                printf("\nerro de alocacao de novo compromisso em agenda: erro de malloc\n");
                return;
            }
            else if (flag == -1){
                printf("erro de intersecção para o lider");
                break;
            }

            qtd_func = ALEAT(2,6);
            cont = 0;
            for (int i=0; i<qtd_func; i++){
                do {
                    func_num = ALEAT(0,num_func);
                } while(func_num != lider_num);

                if (funcionarios[lider_num].lideranca > (funcionarios[func_num].lideranca + ALEAT(-20,10))){
                    if (!marca_compromisso_agenda(&funcionarios[func_num].agenda, dia, compr)){
                        printf("\nerro de alocacao de novo compromisso em agenda: erro de malloc\n");
                        return;
                    }
                    cont++;
                }
            }
            if (!cont)
                desmarca_compromisso_agenda(&funcionarios[lider_num].agenda, dia, compr);
        }
    }
}
