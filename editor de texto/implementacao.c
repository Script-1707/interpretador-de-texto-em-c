#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include"std.c"
#include"extensao.h"
 
typedef struct Tinfo
{
    char palavra[MAX];
    int linha;
} info;

typedef struct TNo{
    info info;
    struct TNo *prox, *pant;
}no;

typedef struct TListaDuplamenteLigada {
    no *prim;
    no *ult;
    no *pactual;
    int nElem;
} listaduplamenteligada;


//  pilha
typedef struct apontador{
        info info;
        struct apontador *proximo;
        no *no_lista;
        int operacao;
}TAtomo;

typedef struct Tpilha{
    TAtomo *topo;
    
}pilha;   

////////////// operacoes pilha /////////

/*---------------------------------------------------------------------------------------------------------------
Objectivo: inicializar pilha
Parâmetro Entrada: pilha
Retorno da Função: 
--------------------------------------------------------------------------------------------------------------*/
void inicio_pilha(pilha *stack){
    stack->topo=NULL;
    
}

/*---------------------------------------------------------------------------------------------------------------
Objectivo: alocar atomo na memoria
Parâmetro Entrada: 
Retorno da Função: atomo
--------------------------------------------------------------------------------------------------------------*/
TAtomo *alocar_atomo(){
    TAtomo *paux = (TAtomo *) malloc(sizeof(TAtomo));
    return paux;
}


/*---------------------------------------------------------------------------------------------------------------
Objectivo: verificar se a pilha esta fazia
Parâmetro Entrada: pilha
Retorno da Função: TRUE OU FALSE
--------------------------------------------------------------------------------------------------------------*/
Boolean vazia_pilha(pilha *stack){
    return (stack->topo==NULL) ;
}

void imprimir (pilha *stack){

    TAtomo *atomo=stack->topo;

    printf("tenho: %s",atomo->info.palavra);
}


/*---------------------------------------------------------------------------------------------------------------
Objectivo: inserir informacao na pilha
Parâmetro Entrada: pilha,ponteiro do no,informaca,e operacao
Retorno da Função: TRUE OU FALSE
--------------------------------------------------------------------------------------------------------------*/
int empilhar(pilha *stack,no *_no,info *informacao,int op){
    
    TAtomo *pnovo = alocar_atomo();
    
    if(pnovo == NULL)
    {
            free(pnovo);
            return NO_SPACE;
    }
    
    //pnovo->info=informacao;
    strcpy(pnovo->info.palavra,informacao->palavra);
    pnovo->info.linha=informacao->linha;
    pnovo->operacao=op;
    pnovo->no_lista=_no;
 
    if(vazia_pilha(stack))
    {       
        pnovo->proximo=NULL;
        stack->topo=pnovo;
    }
    else
    { 
        pnovo->proximo=stack->topo;
        stack->topo=pnovo;    
    }

    return OK;

}

/*---------------------------------------------------------------------------------------------------------------
Objectivo: remover atomo da pilha
Parâmetro Entrada: pilha
Retorno da Função: Topo da pilha
--------------------------------------------------------------------------------------------------------------*/
TAtomo *desempilhar(pilha *stack){
    info *saida= (info *) malloc(sizeof(info));
    TAtomo *aux=stack->topo;
    strcpy(aux->info.palavra,stack->topo->info.palavra);
    aux->info.linha,stack->topo->info.linha;
    //saida->linha=stack->topo->info.linha;
    //saida =stack->topo->info;
    stack->topo=stack->topo->proximo;
   //free(aux);
    return aux;
}

/*---------------------------------------------------------------------------------------------------------------
Objectivo: recupera frase ou palavra apagado 
Parâmetro Entrada: Lista duplamente ligada,pilha
--------------------------------------------------------------------------------------------------------------*/
int undo(listaduplamenteligada *li,pilha *stack){

        TAtomo *saida=desempilhar(stack);
        no *paux = li->prim;
        int i=0;

      
            for(; paux != NULL; paux = paux->prox)
            {   

                if(paux ==saida->no_lista)
                { 
                   if(saida->operacao==0){
                       strcpy(paux->info.palavra,saida->info.palavra);
                   }else if(saida->operacao==-1){
                       remover_undo(li,saida->no_lista);
                       saida->no_lista=NULL;
                   }
                   
                    break;  
                }
            }
                    free(saida);

      
    return OK;

}

int remover_undo(listaduplamenteligada *li,no *atomo){

        

    if(ultimo(li)==1){
       inicLista(li);
        
    }else if(li->prim==atomo){
        li->prim=li->prim->prox;
    }else if(li->ult==atomo){
        li->prim=li->prim->pant;
    }
    else{
        no *paux = li->prim;
        no *anterior=paux;
        for(; paux != NULL; paux = paux->prox)
            {   
                if(paux==atomo){

                    anterior->prox=atomo->prox;
                    atomo->prox->pant=anterior;
                    
                }

                anterior=paux;
            }
    
    }

    free(atomo);
    return OK;
}

/*---------------------------------------------------------------------------------------------------------------
Objectivo: Alterar uma porção de texto
Parâmetro Entrada: Lista duplamente ligada,valores de x e y
Retorno da Função: TRUE OU FALSE
--------------------------------------------------------------------------------------------------------------*/
int deletar(listaduplamenteligada *li,char *x,char *y,pilha *stack){
    no *paux = li->pactual;
    int tam2 = strlen(li->pactual->info.palavra),t=0,j=0, cont = 0,k=0;
    int certo;
    if(isEmpty(li))
        return LIST_EMPTY;
    
    int tam = strlen(x);
   
    info *saida= (info *) malloc(sizeof(info));
    strcpy(saida->palavra,li->pactual->info.palavra);
    saida->linha=li->pactual->info.linha;


    for(int i = 0; i < tam2; i++)
        {
            t = i;
            for(int z = 1; z < tam;z++){
               if(x[z] == paux->info.palavra[t])
                {  
                    j++;
                    t++;
                }
                if(j == tam-1){
                    if(y[k] =='%' && y[k+1] == '%' || y[k] =='#' && y[k+1] == '#')
                        {
                            copiar2(li,paux,i,t,y);
                        }
                    else
                    {
                       copiar(li,paux,i,t,y,x);
                    }
                    cont++;
                }
            }
            j = 0;
        }
        if(cont > 0){
            certo=empilhar(stack,paux,saida,0);
            return OK;
        }    
    return WORD_NOT_FOUND;
}


///////////////////////////////////////
/*--------------------------------------------------------------------------------------------------------------
Objectivo: Inicializar uma lista duplamente ligada.
Parâmetro Entrada: Uma lista duplamente ligada.
Parâmetro de Saída: Lista encadeada com o ponteiro de controlo actualizado.
-------------------------------------------------------------------------------------------------------------- */
void inicLista(listaduplamenteligada *li){
    li->prim = NULL;
    li->ult = NULL;
    li->pactual =  NULL;
    li->nElem=0;
}
/*---------------------------------------------------------------------------------------------------------------
Objectivo: Verificar se a lista está vazia
Parâmetro Entrada: Lista lista duplamente ligada
Retorno da Função: Verdadeiro ou Falso
--------------------------------------------------------------------------------------------------------------*/
Boolean  isEmpty(listaduplamenteligada *li){
    return (li->prim == NULL);
}
/*---------------------------------------------------------------------------------------------------------------
Objectivo: Verificar se a lista está vazia
Parâmetro Entrada: Lista lista duplamente ligada
Retorno da Função: Verdadeiro ou Falso
--------------------------------------------------------------------------------------------------------------*/
no *aloca(){
    no *paux = (no *) malloc(sizeof(no));
    return paux;
}
/*---------------------------------------------------------------------------------------------------------------
Objectivo: Inserir a palavra na lista
Parâmetro Entrada: Lista lista duplamente ligada
Retorno da Função: Codigo de erro
--------------------------------------------------------------------------------------------------------------*/
int inserir(listaduplamenteligada *li,char *palavra,pilha *stack)
{
    no *pnovo = aloca();
    if(pnovo == NULL)
        {
            free(pnovo);
            return NO_SPACE;
        }
    if(li->pactual == NULL || li->ult == li->pactual)
    {
        strcpy(pnovo->info.palavra,palavra);
        pnovo->prox = NULL;
        if(isEmpty(li))
        {
            li->prim = pnovo;
            li->ult = pnovo;
            li->pactual = pnovo;
            li->nElem++;
        }
        else
        { 
            li->ult->prox = pnovo;
            pnovo->pant = li->ult;
            li->ult = pnovo;
            li->pactual = pnovo;
            li->nElem++;
            
        }
        pnovo->info.linha = li->nElem;
          if(li->nElem > 1)
       ordenarLinhas(li); 
        //return OK;
    }
    else
    {
        strcpy(pnovo->info.palavra,palavra);
        pnovo->info.linha = li->nElem;
    
        no *proxActual = li->pactual->prox;
        no * paux = li->prim;

        li->pactual->prox = pnovo;
        pnovo->prox = proxActual;
        proxActual->pant = pnovo;
        pnovo->pant = li->pactual;
        li->pactual = pnovo;
        li->nElem++;
        li->ult->info.linha++;
          if(li->nElem > 1)
       ordenarLinhas(li); 
    }
            info *saida= (info *) malloc(sizeof(info));
            strcpy(saida->palavra,palavra);
            saida->linha=pnovo->info.linha;
    
    return OK;
}
/*---------------------------------------------------------------------------------------------------------------
Objectivo: Inserir informação no inicio
Parâmetro Entrada: Lista duplamente ligada ,info
Retorno da Função: codigo de erro
--------------------------------------------------------------------------------------------------------------*/
int inserAux(listaduplamenteligada *li, char *palavra)
{
    no *pnovo = aloca();
    if(pnovo == NULL)
    {
        free(pnovo);
        return NO_SPACE;
    }
    
    strcpy(pnovo->info.palavra,palavra);

    if(isEmpty(li))
    {
        li->prim = pnovo;
        li->ult = pnovo;
        li->pactual = pnovo;
        li->nElem++;
    }
    else
    {
        pnovo->prox = li->prim;
        li->prim->pant = pnovo;
        li->prim = pnovo;
        li->nElem++;
        li->pactual = pnovo;
    }
    pnovo->info.linha = li->nElem;
    return OK;  
}


/*---------------------------------------------------------------------------------------------------------------
Objectivo: verificar se e um numero
Parâmetro Entrada: Lista duplamente ligada circular valor de c
Retorno da Função: TRUE OU FALSE
--------------------------------------------------------------------------------------------------------------*/
Boolean eh_numero(char c){
     char simb[] = {'0','1','2','3','4','5','6','7','8','9'};
     for(int i=0; i < 11; i++)
     if(c == simb[i])
        return TRUE;
    return FALSE;
}
/**---------------------------------------------------------------------------------------------------------------
Objectivo: remove informação 
Parâmetro Entrada: Lista duplamente ligada, valor de m e de n
Retorno da Função: codigo de erro
--------------------------------------------------------------------------------------------------------------*/
int remover(listaduplamenteligada *li, int m, int n){
     no *ptemp = li->prim;
     no *paux=NULL;
     int y = m, flag = 0;
  
     if(isEmpty(li)) return LIST_EMPTY;

     if(m == 1 && n == ultimo(li))
     {
       
            inicLista(li);
            return OK;
    }
        
      else if(m == 1 && n==1){
            paux = li->prim;
            li->prim = li->prim->prox;
            
            if(paux==li->pactual)
                li->pactual=li->prim;
            free(paux);
            
            li->nElem--;
            renumerar(li,y,flag);
           /* printf(" por aqui= %s ",li->prim->info.palavra);
            printf("o num=%d ",li->prim->info.linha);*/

     }
     else if(m == 1)
     {
        while(m <= n)
        { 
             
            paux = li->prim;
            li->prim = li->prim->prox;
            free(paux);
            linhaCorrente(li,m+1);
            li->nElem--;
            
            m++;
        }
        return renumerar(li,y,flag);
     }
     else if(m == ultimo(li))
     {
        while(m <= n)
        { 
            while(ptemp != NULL)
            {
                if(ptemp->info.linha == m)
                {
                    paux = ptemp;
                    li->ult = li->ult->pant;
                    free(paux);
                
                    linhaCorrente(li,m-1);
                    li->nElem--;
                    break;
                }
            ptemp = ptemp->prox;
            }
            m++;
        }
        return OK;
     }
     else if(n==ultimo(li)){
         int index=m;

                paux=li->prim;
                for(; paux != NULL; paux = paux->prox){
                    if(paux->info.linha == index)
                    {     
                        break;  
                    }
                }    
            li->ult=paux->pant;
            paux->prox=NULL;
           
           while(n>=m){
               li->nElem=li->nElem-1;
               n--;
           }

          
                   // return renumerar(li,y,1); 

                    if(li->pactual!=paux){
                        li->pactual=paux->pant;}
                    

     }
     else
     {
        linhaCorrente(li,m-1);
        while(m <= n)
        { 
           
            while(ptemp->prox != NULL)
            {   

                if(ptemp->info.linha == m)
                {
                    paux = ptemp;
                    ptemp->pant->prox = ptemp->prox;
                    ptemp->prox->pant = ptemp->pant;
                    if(paux==li->ult)
                        li->ult=ptemp->pant;
                    free(paux);
                    li->nElem--;
                    break;

                }
            ptemp = ptemp->prox;
            }
            m++;
            flag = 1;  
        }
        return renumerar(li,y,flag); 
     }
}

/*---------------------------------------------------------------------------------------------------------------
Objectivo: Renumera o numero de linhas apois a remoção  de linhas
Parâmetro Entrada: Lista duplamente ligada  
Retorno da Função: codigo de erro
--------------------------------------------------------------------------------------------------------------*/
int renumerar(listaduplamenteligada *li, int m, int x){
    int flag =0;
    int i = 1;
    no *paux = li->pactual, *paux2 = li->prim;
    if(m == 1)
    {
        while(paux2 != NULL)
         {   paux2->info.linha = i;
            i++;
            paux2 = paux2->prox;
        }
        return OK;
    }
    else if(m == ultimo(li) && x == 0)
    {
        no *p = li->ult;
        li->ult = li->ult->pant;

        free(p);
        li->nElem--;
         
    }
    while( paux != NULL) 
      {
          if(flag == 0)
              {
                  paux->info.linha = li->pactual->info.linha + 0; 
                  flag = 1;
              }
            else{
                paux->info.linha = paux->pant->info.linha + 1;
            }  
            paux = paux->prox;
        }
        
    return OK;
}
/*---------------------------------------------------------------------------------------------------------------
Objectivo: Ordenar o numero de linhas
Parâmetro Entrada: Lista duplamente ligada 
Retorno da Função: nada
Devolve: numero de linhas ordenadas
--------------------------------------------------------------------------------------------------------------*/
void ordenarLinhas(listaduplamenteligada *li){
    int aux=0;
    no *paux = li->prim;
    for( ; paux != NULL; paux = paux->prox)
    {
        for(no *paux2 = paux->prox ; paux2 != NULL; paux2 = paux2->prox)
            if(paux->info.linha > paux2->info.linha)
                {
                    aux = paux2->info.linha;
                    paux2->info.linha = paux->info.linha;
                    paux->info.linha = aux;
                }
    }  
}
/*---------------------------------------------------------------------------------------------------------------
Objectivo: Imprimir texto
Parâmetro Entrada: Lista duplamente ligada, m e n
Retorno da Função: codigo de erro
--------------------------------------------------------------------------------------------------------------*/
int imprimirLista(listaduplamenteligada *li,int m, int n){
    no *paux = li->prim;
    if(isEmpty(li)) return LIST_EMPTY;
    printf("\n ------------------------------------------ \n"); 
    if(li->nElem > 1)
       ordenarLinhas(li); 
   for(; m <= n; m++)
   { 
    for(; paux != NULL; paux = paux->prox)
            {
                if(paux->info.linha == m)
                { 
                        printf("\n %d- %s \n",paux->info.linha,paux->info.palavra);
                    break;  
                }
            }
                
    }
   printf("\n ------------------------------------------ \n"); 
   return OK;
}
/*---------------------------------------------------------------------------------------------------------------
Objectivo: Imprimir texto ordem inversa
Parâmetro Entrada: Lista duplamente ligada, m e n
Retorno da Função: codigo de erro
--------------------------------------------------------------------------------------------------------------*/
int imprimirEnv(listaduplamenteligada *li,int m, int n)
{
    no *paux = li->ult;
    int i = 0;
    if(isEmpty(li)) return LIST_EMPTY;
    printf("\n ------------------------------------------ \n"); 
    if(li->nElem > 1)
       ordenarLinhas(li); 

    for(; paux != NULL; paux = paux->pant)
        {
            if(n != i)
            {
                if(paux->info.linha == m)
                { 
                    printf("\n %d- %s \n",paux->info.linha,paux->info.palavra);
                    i++;
                    m--;
                }
            }
            else
                break;
        }
                
   printf("\n ------------------------------------------ \n"); 
   return OK;
}
/*---------------------------------------------------------------------------------------------------------------
Objectivo: verificar se é um simbolo
Parâmetro Entrada: valor de c
Retorno da Função: TRUE OU FALSE
--------------------------------------------------------------------------------------------------------------*/
Boolean eh_simbolo(char c){
    char simb[] = {'%','#'};
    for(int i=0; i < 11; i++)
     if(c == simb[i])
        return TRUE;
    return FALSE;
}
/*---------------------------------------------------------------------------------------------------------------
Objectivo: transformar em bold
Parâmetro Entrada: um estado
Retorno da Função: NADA
--------------------------------------------------------------------------------------------------------------*/
void bold(int status) 
{
    static const char *seq[] = {"\x1b[0m", "\x1b[1m"};
    printf("%s", seq[!!status]);
} 
/*---------------------------------------------------------------------------------------------------------------
Objectivo: transformar em bold
Parâmetro Entrada: um estado
Retorno da Função: NADA
--------------------------------------------------------------------------------------------------------------*/
int localizar(listaduplamenteligada *li, char *trecho){
    int tam = strlen(trecho);
    int t = 0, j = 0, cont = 0, tam2 = 0, flag = 0;
    no *paux = li->prim;
   
    for(; paux != NULL; paux = paux->prox){
        printf(" %d- ",paux->info.linha);
        tam2 = strlen(paux->info.palavra);
        for(int i = 0; i < tam2; i++)
        {
            t = i;
            for(int x = 1; x < tam;x++)
            {
               if(trecho[x] == paux->info.palavra[t])
                {  
                    j++;
                    t++;
                }
            }
            if(j == tam-1)
            {
                for(int k = i; k < t; k++)
                    {
                        bold(1);
                        printf("%c",paux->info.palavra[k]);
                        bold(0);
                        i++;
                    }
                        printf("%c",paux->info.palavra[i]);
                        flag = 1;
                }
                
            else if(flag == 0)
            {
                printf("%c",paux->info.palavra[i]);  
                flag = 1;
            }

            j = 0;  
            flag = 0;
         }
         printf("\n \n"); 
     } 
    return OK;
}





/*---------------------------------------------------------------------------------------------------------------
Objectivo: Alterar uma porção de texto
Parâmetro Entrada: Lista duplamente ligada,valores de x e y
Retorno da Função: TRUE OU FALSE
--------------------------------------------------------------------------------------------------------------*/
int alterar(listaduplamenteligada *li,char *x,char *y,pilha *stack){
    no *paux = li->pactual;
    int tam2 = strlen(li->pactual->info.palavra),t=0,j=0, cont = 0,k=0;
    int certo;
    if(isEmpty(li))
        return LIST_EMPTY;
    
    int tam = strlen(x);
   
    info *saida= (info *) malloc(sizeof(info));
    strcpy(saida->palavra,li->pactual->info.palavra);
    saida->linha=li->pactual->info.linha;


    for(int i = 0; i < tam2; i++)
        {
            t = i;
            for(int z = 1; z < tam;z++){
               if(x[z] == paux->info.palavra[t])
                {  
                    j++;
                    t++;
                }
                if(j == tam-1){
                    if(y[k] =='%' && y[k+1] == '%' || y[k] =='#' && y[k+1] == '#')
                        {
                            copiar2(li,paux,i,t,y);
                        }
                    else
                    {
                       copiar(li,paux,i,t,y,x);
                    }
                    cont++;
                }
            }
            j = 0;
        }
        if(cont > 0){
            return OK;
        }    
    return WORD_NOT_FOUND;
}
/*---------------------------------------------------------------------------------------------------------------
Objectivo: Substituicao de texto
Parâmetro Entrada: Lista duplamente ligada,enderco do ponteiro,valor de i,t,y e x
Retorno da Função: codigo de erro
--------------------------------------------------------------------------------------------------------------*/
int copiar(listaduplamenteligada *li,no *paux,int i,int t,char *y,char *x){
    int k = 1; 
    
    int tam1 = strlen(paux->info.palavra), max = 0;
    int tamx = strlen(x), tamy = strlen(y);
    max = tam1 +tamy-2;
    int x1 = tamx - 1, y1 = tamy-2;
    int c = i+1, s = 0, flag = 0;
    
    if(tamx-1 == tamy-2)
    {
        while (i <= t-1 )
            {
                if(y[k] == '%' || y[k] == '#' && y[k+1] == '\0')
                    break; 
                paux->info.palavra[i] = y[k];
                k++;
                i++;
            }
    }
    else
    { 
        int q=0,u=0,a=0;
        char straux[80];
        for(int i = 0; i < 80; i++)
            straux[i] = ' ';

        for(int z = t; z < tam1; z++)
            {
                straux[q] = paux->info.palavra[z];
                q++;
            }
            straux[q+1] = '\0';
       for(; i < max; i++){
            if(flag == 0)
            {
                paux->info.palavra[i] = y[k];
                k++;
                a++;
            }
            if(a == y1){
                flag =1;
                paux->info.palavra[i+1] = straux[u];
                u++;
            } 
        } 
    }
    return OK;
}
/*---------------------------------------------------------------------------------------------------------------
Objectivo: Substituicao de texto
Parâmetro Entrada: Lista duplamente ligada,enderco do ponteiro,valor de i,t,y e x
Retorno da Função: codigo de erro
--------------------------------------------------------------------------------------------------------------*/
int copiar2(listaduplamenteligada *li, no *paux, int i, int t, char *y){
    int k=0;
    int tam = strlen(paux->info.palavra);
        while (i <= tam)
        {
            paux->info.palavra[i] = paux->info.palavra[t];
            t++;
            i++;
        }   
    return OK;
}
/*---------------------------------------------------------------------------------------------------------------
Objectivo: analisa a sintaxe do comando alterar
Parâmetro Entrada: Lista duplamente ligada e uma string
Retorno da Função: codigo de erro
--------------------------------------------------------------------------------------------------------------*/
int alterarSintaxe(listaduplamenteligada *li,char *str,pilha *stack){
    char st1[30],st2[30],st3[30], st4[50];
    int fim1 = 0, fim2 = 0, flag = 0, z = 0,cont = 0;
    int j = 0, k = 0, x = 0, tm = strlen(str), inic = 0,inicio_da_segunda=0;
    if(isEmpty(li))
        {
            errorMessage(LIST_EMPTY,str);
            return OK;
        }
    for(int i=0; i < tm; i++)
        {
            if(str[i] == '$')
                {
                    inic = i;
                    break;
                }
            else if(str[i+1] == '\0')
              inic = 0;
        }
     for(int i=inic +1; i < tm; i++)
        {
            if(str[i] != ' ' && fim1 == 0)
                {
                    st1[k++] = str[i];
                    if(str[i+1] == ' ')
                        fim1 = 1;
                    else if(str[i+1] == '%' || str[i+1] == '#')
                            {
                                fim1 = 1; 
                                cont++;
                            }
                }
                
                else if(str[i] != ' ' && fim2 == 0)
                { printf("\n - tenho=%c \n",str[i]);
                    st2[j++] = str[i];
                    /*if(str[i+1] == ' ')
                        fim2 = 1;
                    else */
                    if(str[i+1]==' ')
                        st2[j++]=' ';

                    if((str[i+1] == '%' && str[i+2] != '#') || str[i+1] == '#')
                            {
                                fim2 = 1;
                                cont++;
                            }        
                }
                else 
                {
                    st3[x] = str[i];
                    if(str[i+1] == '%' || str[i+1] == '#')
                            cont++;
                    x++;
                 }
        }
        
    st1[k] = '\0';
    st2[j] = '\0';
    st3[x] = '\0';
    for(int i = 0; st3[i] !=  '\0'; i++){
        if(st3[i] == '%' && flag == 0 || st3[i] == '#' && flag == 0)
            flag = 1;
        if(flag == 1){
            st4[z++] = st3[i];
        }
    }
    st4[z] = '\0';
        if(cont < 3)
        {
            errorMessage(NO_DEMI,str);
        }
    else
        printf("\n manda %s \n",st4);
      return operacoes(li,st1,st2,st4,st4,stack);   
}


int alterarSintaxe2(listaduplamenteligada *li,char *str,pilha *stack){
    char st1[30],st2[30],st3[30], st4[50];
    int fim1 = 0, fim2 = 0, flag = 0, z = 0,cont = 0;
    int j = 0, k = 0, x = 0, tm = strlen(str), inic = 0,inicio_da_segunda=0;
    if(isEmpty(li))
        {
            errorMessage(LIST_EMPTY,str);
            return OK;
        }
    for(int i=0; i < tm; i++)
        {
            if(str[i] == '$')
                {
                    inic = i;
                    break;
                }
            else if(str[i+1] == '\0')
              inic = 0;
        }
     for(int i=inic +1; i < tm; i++)
        {
            if(str[i] != ' ' && fim1 == 0)
                {
                    st1[k++] = str[i];
                    if(str[i+1] == ' ')
                        fim1 = 1;
                    else if(str[i+1] == '%' || str[i+1] == '#')
                            {
                                fim1 = 1; 
                                cont++;

                            }
                }
                
                else if(str[i] != ' ' && fim2 == 0)
                { 
                    st2[j++] = str[i];
                    /*if(str[i+1] == ' ')
                        fim2 = 1;
                    else */
                    if(str[i+1]==' ')
                        st2[j++]=' ';

                    if((str[i+1] == '%' && str[i+2] != '#') || str[i+1] == '#')
                            {
                                fim2 = 1;
                                cont++;

                            }        
                }
                 
                {
                    st3[x] = str[i];
                    if(str[i+1] == '%' || str[i+1] == '#')
                            cont++;
                    x++;
                 }
        }
        
    st1[k] = '\0';
    st2[j] = '\0';
    st3[x] = '\0';
    for(int i = 0; i!=2 ; i++){
        
            st4[z++] = '%';
        
    }
    st4[z] = '\0';
        if(cont < 2)
        {
            errorMessage(NO_DEMI_2,str);
        }
    else
       // printf("\n manda %s \n",st4);
      return operacoes(li,st1,st2,st4,st4,stack);   
}

//--------------------------------------------------------------------------------------------------------------fim

/*---------------------------------------------------------------------------------------------------------------
Objectivo: interpretar os comandos
Parâmetro Entrada: listaliga duplamente ligada e uma string
Retorno da Função: codigo de erro
--------------------------------------------------------------------------------------------------------------*/
int inter(listaduplamenteligada *li, char *str,pilha *stack){

    char st1[30],st2[30],st3[30],st4[30];
    int k = 0,j = 0,x = 0,y = 0,z = 0, u = 0, inic = 0;
    int fim1 = 0,fim2 = 0,fim3 = 0,fim4 = 0, t1 = 0, t2 = 0, c = 0,b=0;
    int tm = strlen(str);

    for(int i=0; i < tm; i++)
        {
            if(str[i] == '$')
                {
                    inic = i;
                    break;
                }
            else if(str[i+1] == '\0')
              inic = 0;
        }
         

    if(str[inic] != '$')
        {
            errorMessage(NO_CIFRAO,str); 
        }
    else 
    {
    for(int i=inic + 1; i < tm; i++)
    {
        if(str[i] != ' ' && fim1 == 0)
            {
                st1[k++] = str[i];
                if(str[i+1] == ' ' || eh_numero(str[i+1]) == TRUE)
                   fim1 = 1;
            else if(str[i+1] == '%' || str[i+1] == '#')
                    fim1 = 1; 
               
            }
        else if(str[i] != ' ' && fim2 == 0)
        {
            st2[j++] = str[i];
            if(str[i+1] == ' ' || st2[j-1] == ',')
                    fim2 = 1;
            else if(str[i+1] == '%' || str[i+1] == '#')
                    fim2 = 1; 
        }
        else if(str[i] != ' ' && fim3 == 0)
        {
            st3[x++] = str[i];
            if(str[i+1] == ' ')
               fim3 = 1;
        }
        else if(str[i] != ' ' && fim4 == 0)
        {
            st4[y++] = str[i];
            if(str[i+1] == ' ')
            fim4 = 1;
        }  
    }
    st1[k] = '\0';
    st2[j] = '\0';
    st3[x] = '\0';
    st4[y] = '\0';

    if(strcmp(st1,"imprimir") == 0 || strcmp(st1,"IMPRIMIR") == 0 || strcmp(st1,"remover") == 0 || strcmp(st1,"REMOVER") == 0)
    {
        if(st2[0] == '\0')
            {
                errorMessage(IS_MISSING_NUMBER,st1); 
                return OK;
            }

        if(st2[j-1] != ',')
            {   
                errorMessage(NO_VIRGULA,st1);
                return OK;
            }

        if(st3[0] == '\0')
            {
                errorMessage(IS_MISSING_NUMBER,st1); 
                return OK;
            }
    }
    else if(strcmp(st1,"alterar") == 0)
            return alterarSintaxe(li,str,stack); 
    else if(strcmp(st1,"deletar") == 0)
            return alterarSintaxe2(li,str,stack);         
    return operacoes(li,st1,st2,st3,st4,stack);
    }
} 

int operacoes(listaduplamenteligada *li,char *cmd, char *num1, char *num2,char *st4,pilha *stack){
    char *str1 = (char *) malloc(sizeof(char *) * 100); 
    char num[10];
    int i,tm,inic = 0;

    if(str1 == NULL) return NO_SPACE;
    int k=0;
    int comando = comandos(cmd);
    int comando2 = comandos(num2);



     for(int i=0; num1[i] != ','; i++)
        num[k++] = num[i];
    if(comando == LOCALIZAR)
        {
            if(isEmpty(li))
            {
                errorMessage(LIST_EMPTY,cmd);
            }
            localizar(li,num1);
            return OK;
        }
    else if(comando == ALTERAR)
        {
            int alt = alterar(li,num1,st4,stack);
            if(isEmpty(li))
                errorMessage(LIST_EMPTY,cmd);
            else if(alt == WORD_NOT_FOUND)
                errorMessage(WORD_NOT_FOUND,cmd);
        }
    else if(comando == DELETAR)
        {
            int alt = deletar(li,num1,st4,stack);
            if(isEmpty(li))
                errorMessage(LIST_EMPTY,cmd);
            else if(alt == WORD_NOT_FOUND)
                errorMessage(WORD_NOT_FOUND,cmd);
        }    
    

    int n1 = atoi(num1);
    int n2 = atoi(num2);

    if((comando == INSERIR) || (comando == LINHA && comando2 ==  INSERIR))
    {  
      do{
            gets(str1);
            tm = strlen(str1);
            for(int i=0; i < tm; i++)
            {
                if(str1[i] == '$')
                    {
                        inic = i;
                        break;
                    }
                else if(str1[i+1] == '\0')
                    inic = 0;
            }
            if(str1[inic] == '$')
                inter(li,str1,stack);
            else if(str1[inic] == '\0')
                   {
                       i = 0;
                   }
            else if(num1[0] == '0')
                inserAux(li,str1);
            else
                inserir(li,str1,stack); 
        }while(str1[0] != '$');
    }
    else if(comando == CLEAR)
            system("clear");
     else if(comando == LINHA)
    {
        if(isEmpty(li))
            {
                errorMessage(LIST_EMPTY,cmd);
            }
        else if(n1 > ultimo(li))
            {
                errorMessage(MAIOR_LIMHA,cmd);
            }
        else if(n1 < 0)
           {
                errorMessage(M_MAIOR,cmd);
           }
           else
           {
               linhaCorrente(li,n1);
           }    
    }
    else if(comando == IMPRIMIR)
        {
            if(n1 < 1)
                errorMessage(NO_M_MENOR,cmd);
           else if(n2 > ultimo(li))
                {
                    errorMessage(MAIOR_LIMHA,cmd); 
                    printf("%d \n",ultimo(li));
                }
           else if(n2 < n1)
                errorMessage(NO_N_MENOR,cmd);
            else
                imprimirLista(li,n1,n2);
       }
    else if(comando == PRNVENV)
        {
            if(n1 < 1)
                errorMessage(NO_M_MENOR,cmd);
            else if(n2 < 1)
                errorMessage(N_MAOIR,cmd);
           else if(n1 > ultimo(li))
                {
                    errorMessage(MAIOR_LIMHA,cmd); 
                    printf("%d \n",ultimo(li));
                }
           else if(n1 < n2)
                errorMessage(M_N_MAOIR,cmd);
            else
                imprimirEnv(li,n1,n2);

        }
    else if(comando == REMOVER)
        {
            if(n1 < 1)
                errorMessage(NO_M_MENOR,cmd);
            else if(n2 > ultimo(li))
            {
                errorMessage(MAIOR_LIMHA,cmd);
                printf("%d \n",ultimo(li));
            }
            else if(n2 < n1)
                errorMessage(NO_N_MENOR,cmd);
            else
                remover(li,n1,n2);
        }
    else if(comando == ULTIMO)
    {
        if(isEmpty(li))
            errorMessage(LIST_EMPTY,cmd);
        else
             printf("\n %d \n",ultimo(li));
        printf("fx");     
    }else if(comando==VOLTAR){
        if(!vazia_pilha(stack))
             undo(li,stack);
        return OK;     

    }
       
   else if(comando == FIM)
        return FIM;
   else if(comando == INVALID_COMMAND)
        errorMessage(INVALID_COMMAND,cmd);
} 
/*---------------------------------------------------------------------------------------------------------------
Objectivo: verifica o tipo de comando
Parâmetro Entrada: Lista duplamente ligada circular e uma string
Retorno da Função: codigo de erro
--------------------------------------------------------------------------------------------------------------*/
int comandos(char *comandos){
    if(strcmp(comandos,"INSERIR") == 0 || strcmp(comandos,"inserir") == 0)
        return INSERIR;
    if(strcmp(comandos,"IMPRIMIR")== 0 || strcmp(comandos,"imprimir") == 0)
        return IMPRIMIR;
    if(strcmp(comandos,"REMOVER")== 0 || strcmp(comandos,"remover") == 0)
        return REMOVER;
    if(strcmp(comandos,"LINHA")== 0 || strcmp(comandos,"linha") == 0)
        return LINHA;
    if(strcmp(comandos,"LOCALIZAR")== 0 || strcmp(comandos,"localizar") == 0)
        return LOCALIZAR;
    if(strcmp(comandos,"ALTERAR")== 0 || strcmp(comandos,"alterar") == 0)
        return ALTERAR;
    if(strcmp(comandos,"ULTIMO")== 0 || strcmp(comandos,"ultimo") == 0)
        return ULTIMO;
    if(strcmp(comandos,"PRNENV")== 0 || strcmp(comandos,"prnenv") == 0)
        return PRNVENV;
  
    if(strcmp(comandos,"VOLTAR")== 0 || strcmp(comandos,"voltar") == 0)
            return VOLTAR;

    if(strcmp(comandos,"DELETAR")== 0 || strcmp(comandos,"deletar") == 0)
            return DELETAR;               

    if(strcmp(comandos,"CLEAR")== 0 || strcmp(comandos,"clear") == 0)
        return CLEAR;
    if(strcmp(comandos,"FIM")== 0 || strcmp(comandos,"fim") == 0)
            return FIM;
    
    return INVALID_COMMAND;
} 
/*---------------------------------------------------------------------------------------------------------------
Objectivo: Mostrar Mensagem de erro
Parâmetro Entrada: codigo e comando
Retorno da Função: NADA
Devolve: Mensagem de erro
--------------------------------------------------------------------------------------------------------------*/
void errorMessage(int codigo,char *cmd)
{
    static char *erro[] = {"não é comando valido",
    "ERRO: Comandos devem começar com $", 
    "ERRO: Falta a virgula, apois o 2º valor",
    "ERRO: 2º valor deve ser maior que o 1º valor!",
    "ERRO: Falta um valor!",
    "ERRO: 1º Valor deve ser maior ou igual a 1!",
    "ERRO: o ultimo numero do texto é igual a",
    "Erro: Valor deve ser maior que 0 !",
    "ERRO: ! ",
    "ERRO:palavra nao encontrada",
    "ERRO:Texto Vazio!!",
    "ERRO: Delimitador ocorre somente duas vezes",
    "ERRO: 2º Valor deve ser maior ou igual a 1!",
    "ERRO: 1º valor deve ser maior que o 2º valor!",
    "ERRO: Delimitador ocorre somente 1 vez !",
        };
        if(codigo == 0)
            printf("\nERRO: %s  %s \n",cmd,erro[codigo]);
        else if(codigo == 6)
            printf(" %s ",erro[codigo]);
        else
            printf("\n %s \n",erro[codigo]);
}
/*---------------------------------------------------------------------------------------------------------------
Objectivo: Tornar uma determinada linha, como linha corrente
Parâmetro Entrada: Lista duplamente ligada circular e numero de linha
Retorno da Função: codigo de erro
--------------------------------------------------------------------------------------------------------------*/
no *linhaCorrente(listaduplamenteligada *li, int n_linha){

    for(no *paux = li->prim; paux != NULL; paux = paux->prox)
      {
        if(n_linha == paux->info.linha)
           { 
              li->pactual = paux;
              return paux;
           }     
      } 
      return NULL; 
}
/*---------------------------------------------------------------------------------------------------------------
Objectivo: verifica o ultimo numero de linha
Parâmetro Entrada: Lista duplamente ligada 
Retorno da Função: ultimo numero de linha
--------------------------------------------------------------------------------------------------------------*/
int ultimo(listaduplamenteligada *li){
    return li->nElem;
}
