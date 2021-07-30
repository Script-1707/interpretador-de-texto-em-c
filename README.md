# interpretador-de-texto-em-c
pequeno editor de texto, baseado em linha de comando com o tipo abstracto de dados

Por definição, um editor de texto é um programa
que processa texto, linha por linha. Suponhamos que cada linha tenha
exactamente 80 caracteres. Cada comando de edição começa com o caracter
cifrão (e nenhuma outra linha começa com esse caracter. Este editor de texto
possui oito comandos:

1o- $inserir : Inserir uma porção de texto depois da linha corrente

2o- $remover m,n: Cada linha no texto, entre as linhas m e n, inclusive, devem
ser removidas.

3o- $linha m : A linha m deve tornar-se a linha corrente.

4o- Localizar %x: localizar no texto todas as ocorrências da cadeia de caracteres
x.

5o- alterar %x %y %: na linha corrente, cada ocorrência da cadeia x deve ser
substituída pela cadeia y.

6o- $último: deve imprimir o número da última linha do texto.

7o- $imprimir m,n: devem ser impressas todas as linhas do texto, e o número
de linhas, das linhas m até n, inclusive n

8o- $fim: termina a execução do editor de texto.
