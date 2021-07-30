#include<stdio.h>
#include<stdlib.h>
#include"implementacao.c"

int main(){
    listaduplamenteligada *li = li = (listaduplamenteligada *) malloc (sizeof(listaduplamenteligada));
    pilha *stack=stack=(pilha *)malloc(sizeof(pilha));
    char *str;
    int n=0;
    str = (char *) malloc(80*sizeof(char *)); 
    int t1;
    do{
         get(str);
        t1 = inter(li,str,stack);  
     }while(t1 != FIM); 
    return 0; 
}
