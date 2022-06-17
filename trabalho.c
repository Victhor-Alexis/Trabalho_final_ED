#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"trabalho.h"

listaD *criaListaD(){
    listaD *LISTA = (listaD *)malloc(sizeof(listaD));
    if(LISTA == NULL){
        printf("Sem memória disponível!\n");
        exit(1);
    }
    else{
        LISTA->inicio = NULL;
        LISTA->final = NULL;
        LISTA->tam = 0;
        return(LISTA);
    }
}

void listar_disciplinas(listaD *LISTA){
    disciplina *aux = LISTA->inicio;

    if(LISTA->inicio != NULL){
        printf("Disciplina  Alunos\n");

        while(aux != NULL){
            printf("%-11s%2d\n", aux->nome, aux->matriculados->qtd_total_alunos);
            aux = aux->prox;
        }
    }
    else{
        printf("Sem disciplinas!\n");
    }
}

//função para adicionar elemento no inicio da lista
int adicionar_disciplina(listaD *LISTA, char *nome){
    disciplina *nova = (disciplina *)malloc(sizeof(disciplina));
    disciplina *aux = LISTA->inicio;
    // Variável aux vai servir para verificar se há disciplinas com mesmo nome

    if(!nova){
        printf("Sem memória disponível!\n");
        return 0;
    }
    else{

        while(aux != NULL){
            if(strcmp(nome, aux->nome) == 0){
                printf("Disciplina já existe!\n");
                return 0;
            }
            aux = aux->prox;
        }//Verificando se o nome da disciplina lido já existe

        strcpy(nova->nome, nome);
        nova->prox = LISTA->inicio;
        nova->matriculados = criaListaAluno();
        /*Acima, criamos espaço para inserir alunos na disciplina, pois nova->matriculados "equivale" a uma lista do tipo alunos*/
        nova->matriculados->qtd_total_alunos = 0;

        if(LISTA->inicio == NULL)
            LISTA->final = nova;

        LISTA->inicio = nova;
        ++LISTA->tam;
        return 1;
    }
}

int remover_disciplina(listaD *LISTA, char *nome){
    disciplina *aux = LISTA->inicio;
    disciplina *aux_anterior;
    disciplina *excluido;
    int pos = 0;


    if(LISTA->inicio != NULL){
        if(LISTA->inicio == LISTA->final && !strcmp(nome, aux->nome)){
            excluido = LISTA->inicio;
            LISTA->inicio = NULL;
            LISTA->final = NULL;
        }/*Caso haja 1 elemento apenas na lista e o nome inserido exista*/
        else{
            while(aux != NULL && strcmp(nome, aux->nome)){
                aux_anterior = aux;
                aux = aux->prox;
                ++pos;
            }

            if(pos == LISTA->tam){
                printf("Disciplina não encontrada!\n");
                return 0;
            }

            if(pos == 0){
                excluido = LISTA->inicio;
                LISTA->inicio = LISTA->inicio->prox;
            }
            else{
                excluido = aux;
                aux_anterior->prox = aux->prox;
            }
        }
        --LISTA->tam;
        free(excluido);
        return 1;
    }
    else{
        printf("Lista de disciplinas está vazia!\n");
    }
    return 0;
}

//ALUNOS
int adicionar_aluno(listaA *lista, char *nome, int matricula, char *curso){
    aluno *novo = (aluno *)malloc(sizeof(aluno));
    aluno *aux = lista->inicio;
    //variável aux serve para verificar se existem matrículas iguais

    if(novo != NULL){
        while(aux != NULL){
            if(matricula == aux->matricula){
                printf("matrícula já existe!\n");
                return 0;
            }
            aux = aux->prox;
        }//busca na lista de alunos sem disciplina

        strcpy(novo->nome, nome);
        novo->matricula = matricula;
        strcpy(novo->curso, curso);
        novo->prox = lista->inicio;

        if(lista->inicio == NULL){
            lista->final = novo;
        }
        lista->inicio = novo;
        ++lista->qtd_total_alunos;
        return 1;
    }
    else{
      printf("Sem memória disponível!\n");
    }
    return 0;
}

listaA *criaListaAluno(void){
    listaA *lista = (listaA *)malloc(sizeof(listaA));
    if(lista == NULL){
        printf("Sem memória disponível!\n");
        exit(1);
    }
    else{
        lista->inicio = NULL;
        lista->final = NULL;
        lista->qtd_total_alunos = 0;
    }
    return lista;
}

void listar_alunos_sem_disciplina(listaA *lista){
    aluno *aux = lista->inicio;

    if(aux != NULL){
        printf("Alunos sem disciplina\n");
        printf("Nome                          Matricula     Curso\n");
        while(aux != NULL){
            printf("%-30s%-14d%s\n", aux->nome, aux->matricula, aux->curso);
            aux = aux->prox;
        }
    }
    else{
        printf("Lista vazia!\n");
    }
}

int remover_aluno(listaA *lista, int matricula){
    aluno *aux = lista->inicio;
    aluno *aux_ant;
    aluno *excluido = aux;
    int pos = 0;

    if(lista->inicio != NULL){
        if(lista->inicio == lista->final && aux->matricula == matricula){
            excluido = lista->inicio;
            lista->inicio = NULL;
            lista->final = NULL;
        }
        else{
            while(aux != NULL && matricula != aux->matricula){
                aux_ant = aux;
                aux = aux->prox;
                ++pos;
            }

            if(pos == lista->qtd_total_alunos){
                printf("Matrícula não encontrada!\n");
                return 0;
            }

            if(pos == 0){
                excluido = lista->inicio;
                lista->inicio = lista->inicio->prox;
            }
            else{
                excluido = aux;
                aux_ant->prox = aux->prox;
            }
        }
        --lista->qtd_total_alunos;
        free(excluido);
        return 1;
    }
    else{
        printf("Sem alunos para remover!\n");
    }
    return 0;
}

int incluir_aluno_em_disciplina(listaD *lista_disciplina, listaA *lista_aluno, int mat, char *dscp){
    disciplina *aux_dscp;
    aluno *aux_aluno;
    int pos_dscp = 0, pos_aluno = 0;

    aux_dscp = lista_disciplina->inicio;
    aux_aluno = lista_aluno->inicio;

    while(aux_dscp != NULL && strcmp(dscp, aux_dscp->nome)){
        ++pos_dscp;
        aux_dscp = aux_dscp->prox;
    }/*Buscando disciplina*/
    while(aux_aluno != NULL && mat != aux_aluno->matricula){
        ++pos_aluno;
        aux_aluno = aux_aluno->prox;
    }/*Buscando aluno na lista de alunos sem disciplina*/

    if(pos_dscp == lista_disciplina->tam || pos_aluno == lista_aluno->qtd_total_alunos){
        printf("A matrícula ou disciplina inserida não existe!\n");
        return 0;
    }
    /*Cada disciplina possui uma lista de alunos chamada matriculados. Para inserir alunos em
    uma disciplina basta que se reutilize a função adiciona_aluno passando a lista dentro
    da disciplina como parâmetro*/
    adicionar_aluno(aux_dscp->matriculados, aux_aluno->nome, aux_aluno->matricula, aux_aluno->curso);
    remover_aluno(lista_aluno, aux_aluno->matricula);
    /*Deve-se remover o aluno da lista de alunos sem disciplina quando o aluno é inserido em uma*/
    return 1;
}

disciplina* gerenciar_disciplina(char *nome_disciplina, listaD *lista_disciplina){
    disciplina *aux = lista_disciplina->inicio;

    while(aux != NULL){
        if(!strcmp(nome_disciplina, aux->nome)){
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

void listar_alunos_da_disciplina(disciplina *DISCIPLINA){
    if(DISCIPLINA->matriculados->inicio == NULL){
          printf("Sem alunos nesta disciplina!\n");
          return;
    }
    aluno *aux = DISCIPLINA->matriculados->inicio;
    while(aux != NULL){
        printf("%-11d%-30s%.0f%%     %.2f%5s\n", aux->matricula, aux->nome, aux->faltas, aux->nota, aux->mencao);
        aux = aux->prox;
    }
}
int remover_aluno_da_disciplina(disciplina *DISCIPLINA, listaA *lista_aluno, int mat){
    listaA *aux = DISCIPLINA->matriculados;
    aluno *excluido = DISCIPLINA->matriculados->inicio;
    int pos = 0;

    while(excluido != NULL && mat != excluido->matricula){
        ++pos;
        excluido = excluido->prox;
    }

    if(pos == aux->qtd_total_alunos){
        printf("Matrícula inserida não foi encontrada!\n");
        return 0;
    }
    else{
        adicionar_aluno(lista_aluno, excluido->nome, excluido->matricula, excluido->curso);
        /*adicionando o aluno removido da disciplina na lista de alunos sem disciplina
        Para não retirar o aluno do sistema*/
        remover_aluno(aux, mat);
    }
    return 0;
}

aluno* busca_aluno_na_disciplina(disciplina *DISCIPLINA, int matricula){
    aluno *aux = DISCIPLINA->matriculados->inicio;
    int pos = 0;

    if(DISCIPLINA->matriculados->inicio == NULL){
        printf("Lista de alunos da disciplina está vazia!\n");
        return 0;
    }
    else{
        while(aux != NULL && matricula != aux->matricula){
            aux = aux->prox;
            ++pos;
        }

        if(pos == DISCIPLINA->matriculados->qtd_total_alunos){
            printf("Matricula inserida não existe!\n");
            return NULL;
        }

        return aux;
    }
}

void atribuir_nota_a_aluno(disciplina *DISCIPLINA, float nota, int matricula){
    aluno *aux = busca_aluno_na_disciplina(DISCIPLINA, matricula);
    if(aux != NULL){
        aux->nota = nota;
        atribuir_mencao_a_aluno(aux->nota, aux->faltas, aux);
    }
}

void atribuir_faltas_a_aluno(disciplina *DISCIPLINA, float faltas, int matricula){
    aluno *aux = busca_aluno_na_disciplina(DISCIPLINA, matricula);
    if(aux != NULL){
        aux->faltas = faltas*100;
        atribuir_mencao_a_aluno(aux->nota, aux->faltas, aux);
    }
}

void atribuir_mencao_a_aluno(float nota, float faltas, aluno *semluz){
    if((nota >= 1 && nota <= 2.9) && faltas < 25)
        strcpy(semluz->mencao, "II");
    else if((nota >= 3 && nota <= 4.9) && faltas < 25)
        strcpy(semluz->mencao, "MI");
    else if((nota >= 5 && nota <= 6.9) && faltas < 25)
        strcpy(semluz->mencao, "MM");
    else if((nota >= 7 && nota <= 8.9) && faltas < 25)
        strcpy(semluz->mencao, "MS");
    else if((nota >= 9 && nota <= 10) && faltas < 25)
        strcpy(semluz->mencao, "SS");
    else{
        strcpy(semluz->mencao, "SR");
    }
}

void processar_turma(listaA *lista_alunos){

    listaA *apenas_cursos_diferentes = (listaA *)malloc(sizeof(listaA));
    aluno *aux = lista_alunos->inicio;
    aluno *tmp;
    curso *CURSO;
    listaC *lista_cursos;
    /*Uma nova lista para os cursos é criada. cada Curso da lista possui uma lista de alunos*/
    if(aux == NULL){
        printf("Sem alunos na lista!\n");
        return;
    }
    else{
        /*criando lista de cursos*/
        lista_cursos = (listaC *)malloc(sizeof(listaC));

        if(lista_cursos != NULL){
            lista_cursos->inicio = NULL;
            lista_cursos->tam = 0;
        }
        else{
            printf("Sem memória!\n");
            return;
        }

        void adicionar_curso(listaC *lista_cursos, char *nome_curso){
            curso *novo = (curso *)malloc(sizeof(curso));
            int i;

            if(novo != NULL){
                strcpy(novo->nome_curso, nome_curso);
                novo->alunos_do_curso = criaListaAluno();
                novo->aprovados = 0;

                for(i = 0; i < 6; ++i)
                    novo->mencao[i] = 0;
                /*inicializando contadores para menções*/
                novo->prox = lista_cursos->inicio;
                lista_cursos->inicio = novo;
            }
            else{
                printf("Sem memória!\n");
                return;
            }
        }
        while(aux != NULL){
            adicionar_aluno(apenas_cursos_diferentes, aux->nome, aux->matricula, aux->curso);
            aux = aux->prox;
        }/*Armazenamos os alunos de uma disciplina em outra lista de alunos para que
        possamos alterar os dados sem modificá-los permanentemente na lista principal(a da disciplina)*/

        aux = apenas_cursos_diferentes->inicio;

        //Logo abaixo, ocorre a adição de nomes de cursos não repetidos
        while(aux != NULL){
            adicionar_curso(lista_cursos, aux->curso);
            tmp = aux->prox;
            while(tmp != NULL){
                if(!strcmp(aux->curso, tmp->curso)){
                    remover_aluno(apenas_cursos_diferentes, tmp->matricula);
                    /*acima, um dos alunos com o mesmo nome de curso é removido Para
                    que os nomes armazenados na lista de cursos não sejam repetidos*/
                }
                tmp = tmp->prox;
            }
            aux = aux->prox;
        }

        CURSO = lista_cursos->inicio;
        while(CURSO != NULL){
            aux = lista_alunos->inicio;
            /*lista_alunos é a lista que não foi alterada*/
            while(aux != NULL){
                if(!strcmp(aux->curso, CURSO->nome_curso)){
                    adicionar_aluno(CURSO->alunos_do_curso, aux->nome, aux->matricula, aux->curso);
                    CURSO->alunos_do_curso->inicio->nota = aux->nota;
                    CURSO->alunos_do_curso->inicio->faltas = aux->faltas;
                    strcpy(CURSO->alunos_do_curso->inicio->mencao, aux->mencao);
                    /*se o nome de um curso é igual ao curso de um aluno da disciplina
                    "(aux->curso) == (CURSO->nome_curso)" o aluno é adicionado no curso homônimo
                    da lista_cursos*/
                }
                aux = aux->prox;
            }
            CURSO = CURSO->prox;
        }

        CURSO = lista_cursos->inicio;

        printf("Curso Matriculados Aprovados Reprovados\n");
        while(CURSO != NULL){
            aux = CURSO->alunos_do_curso->inicio;
            CURSO->aprovados = 0;
            while(aux != NULL){
                if(aux->nota >= 5.00)
                    ++CURSO->aprovados;

                if(!strcmp(aux->mencao, "SS"))
                    ++CURSO->mencao[0];
                if(!strcmp(aux->mencao, "MS"))
                    ++CURSO->mencao[1];
                if(!strcmp(aux->mencao, "MM"))
                    ++CURSO->mencao[2];
                if(!strcmp(aux->mencao, "MI"))
                    ++CURSO->mencao[3];
                if(!strcmp(aux->mencao, "II"))
                    ++CURSO->mencao[4];
                if(!strcmp(aux->mencao, "SR"))
                    ++CURSO->mencao[5];

                aux = aux->prox;
            }

            CURSO->taxa_aprovados = (float)CURSO->aprovados/(float)CURSO->alunos_do_curso->qtd_total_alunos*100;
            CURSO->taxa_reprovados = 100 - CURSO->taxa_aprovados;
            CURSO->reprovados = CURSO->alunos_do_curso->qtd_total_alunos - CURSO->aprovados;

            printf("%-6s%-13d%.0f%%(%d)     %.0f%%(%d)\n", CURSO->nome_curso, CURSO->alunos_do_curso->qtd_total_alunos, CURSO->taxa_aprovados, CURSO->aprovados, CURSO->taxa_reprovados,CURSO->reprovados);

            CURSO = CURSO->prox;
        }
        CURSO = lista_cursos->inicio;
        printf("\n\n\n");
        printf("Mencao\n");
        printf("Curso SS MS MM MI II SR\n");
        while(CURSO != NULL){
            printf("%-6s%d  %d  %d  %d  %d  %d\n", CURSO->nome_curso, CURSO->mencao[0], CURSO->mencao[1], CURSO->mencao[2], CURSO->mencao[3], CURSO->mencao[4], CURSO->mencao[5]);
            CURSO = CURSO->prox;
        }
    }
    //liberando memória alocada:
    aluno *aux_ant;
    if(lista_cursos != NULL){
        CURSO = lista_cursos->inicio;
        curso *CURSO_ant;
        while(CURSO != NULL){
            aux = CURSO->alunos_do_curso->inicio;
            while(aux != NULL){
                aux_ant = aux;
                aux = aux->prox;
                free(aux_ant);
            }
            CURSO_ant = CURSO;
            CURSO = CURSO->prox;
            free(CURSO_ant);
        }
    }
    /*lista de alunos alterada*/
    if(apenas_cursos_diferentes != NULL){
        aux = apenas_cursos_diferentes->inicio;
        while(aux != NULL){
            aux_ant = aux;
            aux = aux->prox;
            free(aux_ant);
        }
        free(apenas_cursos_diferentes);
    }
}

void liberaMemoria(listaA *alunos_sem_dscp, listaD *disciplinas){
    aluno *aux;
    aluno *aux_ant;
    disciplina *dscp;
    disciplina *dscp_ant;

    if(alunos_sem_dscp != NULL){
        aux = alunos_sem_dscp->inicio;
        while(aux != NULL){
            aux_ant = aux;
            aux = aux->prox;
            free(aux_ant);
        }
        free(alunos_sem_dscp);
    }
    if(disciplinas != NULL){
        dscp = disciplinas->inicio;

        while(dscp != NULL){
            aux = dscp->matriculados->inicio;
            while(aux != NULL){
                aux_ant = aux;
                aux = aux->prox;
                free(aux_ant);
            }/*desalocando espaço utilizados nas listas de alunos matriculados nas disciplinas*/
            dscp_ant = dscp;
            dscp = dscp->prox;
            free(dscp_ant);
        }
        free(disciplinas);
    }
}
