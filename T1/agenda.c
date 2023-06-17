#include "libagenda.h"
#include "libfuncs.h"

int main(){
    func_t funcionarios[num_func];
    taref_t tarefas[num_taref];
    int dia;

    /*Inicialização*/
    set_func_e_taref(funcionarios,tarefas);
    marca_reunioes(funcionarios, tarefas);

    /*TRABALHAR*/
    for (int i=0; i<num_func; i++){
        prim_mes_agenda(&funcionarios[i].agenda);

    return 0;
}