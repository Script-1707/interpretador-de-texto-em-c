#ifndef DOUBLE_LINKIDLIST
#define DOUBLE_LINKIDLIST

#define MAX             80

#define NO_SPACE       -1

#define OK                      0
#define INSERIR                 1
#define REMOVER                 2
#define LINHA                   3
#define LOCALIZAR               4
#define ALTERAR                 5
#define ULTIMO                  6
#define IMPRIMIR                7  
#define FIM                     8
#define CLEAR                   9
#define PRNVENV                 10
#define VOLTAR                  11
#define DELETAR                 12 

#define INVALID_COMMAND         0
#define NO_CIFRAO               1
#define NO_VIRGULA              2
#define NO_N_MENOR              3
#define IS_MISSING_NUMBER       4
#define NO_M_MENOR              5              
#define MAIOR_LIMHA             6
#define M_MAIOR                 7
#define NO_NUMBER               8
#define WORD_NOT_FOUND          9
#define LIST_EMPTY              10
#define NO_DEMI                 11
#define N_MAOIR                 12
#define M_N_MAOIR               13
#define NO_DEMI_2               14


//----------------------------TIPO DE DADO ESXPORTADA
typedef struct TListaDuplamenteLigada listaduplamenteligada;
typedef struct TNo no;
typedef struct Tinfo info;

typedef struct Tpilha pilha;
typedef struct apontador TAtomo;


typedef enum { FALSE =0, TRUE=1 } Boolean;

//----------------------------------------------------------------- Protótipos das Funções
// Funções exportadas


//--------------------------------- funcoes da pilha

//iniciliza a pilha
void inicio_pilha(pilha *stack);
//aloca novo item na pilha
TAtomo *alocar_atomo();
 //cerifica se a pilha essta vazia
Boolean vazia_pilha(pilha *stack);
//inserir atomo na pilha
int empilhar(pilha *stack,no *_no,info *informacao,int op);
//remover atomo
TAtomo *desempilhar(pilha *stack);
//alterar o conteudo de uma linha x por y
int deletar(listaduplamenteligada *li,char *x,char *y,pilha *stack);

//-----------------------------------fim pilha

//Inicializa a lista
void inicLista(listaduplamenteligada *li);

//verifica se a lista esta vazia
Boolean  isEmpty(listaduplamenteligada *li);

//aloca um atomo 
no *aloca();

//Insere a frase na lista duplamente ligada
int inserir(listaduplamenteligada *li,char *palavra,pilha *stack);

//remove uma texto dado um intervalo de n a m
int remover(listaduplamenteligada *li, int m, int n);

//renumera o numero de linhas do texto
int renumerar(listaduplamenteligada *li, int m, int x);

//Ordena o numero de linhas do texto
void ordenarLinhas(listaduplamenteligada *li);

//Imprimi todo o texto em um intervalo de n a m
int imprimirLista(listaduplamenteligada *li,int m, int n);

//Bold
void bold(int status);

//imprimir o texto, com todas as ocorrencoas de x em bold
int localizar(listaduplamenteligada *li, char *x);

//alterar o conteudo de uma linha x por y
int alterar(listaduplamenteligada *li,char *x,char *y,pilha *stack);

//Interpretação dos comandos
int inter(listaduplamenteligada *li, char *str,pilha *stack);

//verifica o comando
int comandos(char *comandos);

//verificação das operação de cada comando
int operacoes(listaduplamenteligada *li,char *cmd, char *num1, char *num2,char *st4,pilha *stack);

//Mensagens de erros
void errorMessage(int codigo,char *cmd);

//torna uma linha corrente
no *linhaCorrente(listaduplamenteligada *li, int n_linha);

//Ultimo numero de linha do texto
int ultimo(listaduplamenteligada *li);

// servem para copiar os parametros de alguns comandos
int copiar2(listaduplamenteligada *li, no *paux, int i, int t, char *y);

int copiar(listaduplamenteligada *li,no *paux,int i,int t,char *y,char *x);

char * gets (char * string);





#endif