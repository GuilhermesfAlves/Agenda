TIPOS DE DADOS:

- horario_compr_t
    - hora inicial
    - minuto inicial    
    - hora final
    - minuto final

- agenda_t  
    - ponteiro mes_t atual
        - int mes
        - ponteiro dia _t dias
        - ponteiro mes_t proximo
        - ponteiro mes_t anterior
    - int mes atual

- mes_t -> lista circular
    - int mes
    - ponteiro dia _t dias
    - ponteiro mes_t proximo
    - ponteiro mes_t anterior

- dia_t lista simples ordenada pelo dia
    - int dia 
    - ponteiro compromisso_t compromisso (ini)
    - ponteiro dia_t prox 

- compromisso_t -> lista de compromissos simples ordenada pelo tempo
    - int ID
    - ponteiro char descrição
    - int inicio (minutos desde 00:00)
    - int fim (minutos desde 00:00)
    - ponteiro compromisso_t proximo