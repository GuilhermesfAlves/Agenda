#ifndef AGENDA_LIB
#define AGENDA_LIB

#include <stdlib.h>
#include <time.h>
#include <stdio.h>
#include "libagenda.h"
#define JAN 1
#define DEZ 12
#define num_func 30
#define num_taref 100

/*tipo funcionario que possui liderança e experiencia
* associada para cada*/
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

void marca_reunioes(func_t funcionarios[], taref_t tarefas[]);



#endif