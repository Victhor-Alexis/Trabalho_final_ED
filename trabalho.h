typedef struct _aluno{
    char nome[51];
    int matricula;
    char curso[3];
    float nota;
    float faltas;
    char mencao[3];
    struct _aluno *prox;
}aluno;

typedef struct _listaA{
    int qtd_total_alunos;
    aluno *inicio;
    aluno *final;
}listaA;

typedef struct _disciplina{
    char nome[4];
    listaA *matriculados;
    struct _disciplina *prox;
}disciplina;

/*Como a struct disciplina acima contendo um tipo de dado listaA *matriculados sugere, cada mat possui
sua própria lista de alunos com a finalidade de se facilitar a inserção de alunos em uma disciplina*/

typedef struct _listaD{
    int tam;
    disciplina *inicio;
    disciplina *final;
}listaD;

typedef struct curso{
    listaA *alunos_do_curso;
    char nome_curso[3];
    int aprovados;
    int reprovados;
    int mencao[6];
    float taxa_aprovados;
    float taxa_reprovados;
    struct curso *prox;
}curso;

typedef struct listaC{
    int tam;
    curso *inicio;
}listaC;

/*funções para manipular as disciplinas*/
int adicionar_disciplina(listaD *LISTA, char *nome);
listaD *criaListaD();
void listar_disciplinas(listaD *LISTA);
int remover_disciplina(listaD *LISTA, char *nome);

/*funções para manipular lista de alunos*/
listaA *criaListaAluno(void);
int adicionar_aluno(listaA *lista, char *nome, int matricula, char *curso);
void listar_alunos_sem_disciplina(listaA *lista);
int remover_aluno(listaA *lista, int matricula);

/*alunos e disciplinas*/
int incluir_aluno_em_disciplina(listaD *listar_disciplina, listaA *lista_aluno, int mat, char *dscp);
disciplina* gerenciar_disciplina(char *nome_disciplina, listaD *lista_disciplina);
void listar_alunos_da_disciplina(disciplina *DISCIPLINA);
int remover_aluno_da_disciplina(disciplina *DISCIPLINA, listaA *lista_aluno, int mat);
void atribuir_nota_a_aluno(disciplina *DISCIPLINA, float nota, int matricula);
void atribuir_faltas_a_aluno(disciplina *DISCIPLINA, float faltas, int matricula);
void atribuir_mencao_a_aluno(float nota, float faltas, aluno *semluz);
void processar_turma(listaA *lista_alunos);
void liberaMemoria(listaA *alunos_sem_dscp, listaD *disciplinas);
