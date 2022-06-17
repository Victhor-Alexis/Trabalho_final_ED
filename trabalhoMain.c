#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"trabalho.h"

//Parte I
int menu(void);
void opcao(int opt, listaD *LISTA, listaA *lista_alunos);

//Parte II
int menu_gerenciamento_aluno(disciplina *DISCIPLINA, char *nome_dscp);
void opcao_gerenciamento_aluno(int opt, listaD *LISTA, listaA *lista_alunos, char *nome_dscp);

int main(void){

    listaD *LISTA = criaListaD();
    listaA *lista_alunos = criaListaAluno();
    int option;

    lista_alunos->qtd_total_alunos = 0;

    do{
        option = menu();
        opcao(option, LISTA, lista_alunos);

    }while(option);

    return 0;
}

int menu(void){

    int opt;

    printf("O que deseja fazer:\n");
    printf("1 Listar disciplinas\n");
    printf("2 Adicionar disciplina\n");
    printf("3 Remover disciplina\n");
    printf("4 Listar alunos sem disciplina\n");
    printf("5 Adicionar aluno\n");
    printf("6 Remover aluno\n");
    printf("7 Incluir aluno em disciplina\n");
    printf("8 Gerenciar disciplina\n");
    printf("9 Sair\n");
    printf("Digite a opção: ");
    scanf("%d", &opt);

    if(opt == 9)
        return 0;

    return opt;

}

void opcao(int opt, listaD *LISTA, listaA *lista_alunos){

    char nome_dscp[4];
    char nome_aluno[51];
    int matricula;
    char curso[3];
    int opcao;

    switch(opt){

        case 1:
            system("clear");
            listar_disciplinas(LISTA);
            printf("Pressione enter para voltar.");
            getchar();
            getchar();
            system("clear");
            break;

        case 2:
            system("clear");
            printf("Adicionar disciplina\n");
            printf("Digite a sigla: ");
            scanf("%s", nome_dscp);
            adicionar_disciplina(LISTA, nome_dscp);
            printf("Pressione enter para voltar.");
            getchar();
            getchar();
            system("clear");
            break;

        case 3:
            system("clear");
            if(LISTA->inicio != NULL){
                printf("Remover disciplina\n");
                printf("Digite a sigla: ");
                scanf("%s", nome_dscp);
            }
            remover_disciplina(LISTA, nome_dscp);
            printf("Pressione enter para voltar.");
            getchar();
            getchar();
            system("clear");
            break;

        case 4:
            system("clear");
            listar_alunos_sem_disciplina(lista_alunos);
            printf("Pressione enter para voltar.");
            getchar();
            getchar();
            system("clear");
            break;

        case 5:
            system("clear");
            printf("Adicionar aluno:\n");
            printf("Nome: ");
            scanf("%s", nome_aluno);
            printf("Matricula: ");
            scanf("%d", &matricula);
            printf("Curso: ");
            scanf("%s", curso);
            adicionar_aluno(lista_alunos, nome_aluno, matricula, curso);
            printf("Pressione enter para voltar.");
            getchar();
            getchar();
            system("clear");
            break;

        case 6:
            system("clear");
            if(lista_alunos->inicio != NULL){
                printf("Remover aluno\n");
                printf("Digite a matricula: ");
                scanf("%d", &matricula);
            }
            remover_aluno(lista_alunos, matricula);
            printf("Pressione enter para voltar.");
            getchar();
            getchar();
            system("clear");
            break;

        case 7:
            system("clear");
            printf("incluir aluno:\n");
            printf("Matricula: ");
            scanf("%d", &matricula);
            printf("Disciplina: ");
            scanf("%s", nome_dscp);
            incluir_aluno_em_disciplina(LISTA, lista_alunos, matricula, nome_dscp);
            printf("Pressione enter para voltar.");
            getchar();
            getchar();
            system("clear");
            break;

        case 8:
            system("clear");
            printf("Gerenciar disciplina: ");
            scanf("%s", nome_dscp);
            if(gerenciar_disciplina(nome_dscp, LISTA)){
                do{
                    opcao = menu_gerenciamento_aluno(gerenciar_disciplina(nome_dscp, LISTA), nome_dscp);
                    opcao_gerenciamento_aluno(opcao, LISTA, lista_alunos, nome_dscp);
                }while(opcao);
            }
            else{
                printf("Disciplina inserida não existe!\n");
            }
            printf("Pressione enter para voltar.");
            getchar();
            getchar();
            system("clear");
            break;

        case 0:
            liberaMemoria(lista_alunos, LISTA);
            break;

        default:
            printf("Comando inválido!\n\n");
    }
}

int menu_gerenciamento_aluno(disciplina *DISCIPLINA, char *nome_dscp){

    int opt;

    printf("Gerenciando disciplina %s\n", nome_dscp);
    printf("Quantidade de alunos: %d\n", DISCIPLINA->matriculados->qtd_total_alunos);
    printf("Opcoes:\n");
    printf("1 Listar alunos\n");
    printf("2 Remover aluno da disciplina\n");
    printf("3 Atribuir nota a aluno\n");
    printf("4 Atribuir faltas a aluno\n");
    printf("5 Processar turma\n");
    printf("6 Voltar\n");
    printf("Escolha uma opção: ");
    scanf("%d", &opt);

    if(opt == 6)
        return 0;

    return opt;
}

void opcao_gerenciamento_aluno(int opt, listaD *LISTA, listaA *lista_alunos, char *nome_dscp){

    int matricula;
    float nota;
    float faltas;
    disciplina *dscp;

    switch(opt){

        case 1:
            system("clear");
            printf("Matricula |           Nome           | Faltas | Nota | Mencao\n");
            listar_alunos_da_disciplina(gerenciar_disciplina(nome_dscp, LISTA));//retorna a disciplina inserida
            printf("Pressione enter para voltar.");
            getchar();
            getchar();
            system("clear");
            break;

        case 2:
            system("clear");
            printf("Digite a matricula do aluno a ser removido de %s\n", nome_dscp);
            scanf("%d", &matricula);
            remover_aluno_da_disciplina(gerenciar_disciplina(nome_dscp, LISTA), lista_alunos, matricula);
            printf("Pressione enter para voltar.");
            getchar();
            getchar();
            system("clear");
            break;

        case 3:
            system("clear");
            printf("Atribuir nota a aluno de ED\n");
            printf("Matricula: ");
            scanf("%d", &matricula);
            printf("Nota: ");
            scanf("%f", &nota);
            atribuir_nota_a_aluno(gerenciar_disciplina(nome_dscp, LISTA), nota, matricula);
            printf("Pressione enter para voltar.");
            getchar();
            getchar();
            system("clear");
            break;

        case 4:
            system("clear");
            printf("Atribuir faltas a aluno de ED\n");
            printf("Matricula: ");
            scanf("%d", &matricula);
            printf("Faltas: ");
            scanf("%f", &faltas);
            atribuir_faltas_a_aluno(gerenciar_disciplina(nome_dscp, LISTA), faltas, matricula);
            printf("Pressione enter para voltar.");
            getchar();
            getchar();
            system("clear");
            break;

        case 5:
            dscp = gerenciar_disciplina(nome_dscp, LISTA);
            system("clear");
            printf("Informações de %s\n", nome_dscp);
            processar_turma(dscp->matriculados);
            printf("Pressione enter para voltar.");
            getchar();
            getchar();
            system("clear");
            break;

        case 0:
            break;

        default:
            printf("Comando inválido!\n\n");

    }
}
