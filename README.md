# TRABALHO 1 - SIMULAÇÃO INCÊNDIO

ALUNO: JADE GIULIA JANUARIA DE SOUZA

PROFESSOR: MICHEL PIRES DA SILVA

DISCIPLINA: ALGORITIMOS E ESTRUTURAS DE DADOS I

# SUMARIO DO PROJETO

1 . INTRODUÇÃO

2 . METODOLOGIA

3 . RESULTADOS

4 . CONCLUSÃO

5 . COMPILAÇÃO


# 1 . INTRODUÇÃO

Esse trabalho tem como objetivo simular como um incêndio se espalha numa floresta, usando um mapa/matriz para
representar a área que ocorrerá o incêndio. Cada pedacinho desse mapa pode estar de um jeito: com árvores boas, pegando fogo, já queimadas, sem nada ou com água. A simulação vai levar em conta como o fogo se move, até memso se o vento estiver soprando. Também vamos colocar um animal correndo para escapar do fogo, procurando o caminho mais seguro.



#  . METODOLOGIA

###  1 - main.cpp

 - Bloco try:
   - É nesse bloco onde a gente tenta rodar um código que pode dar errado. Se tudo dê certo, a simulação acontece normalmente. Mas se acontecer algum problema, tipo o arquivo não existir, ele vai para o catch.
   - Linha 8: Aqui é criado um objeto do tipo Simulador. Esse objeto é quem vai cuidar de tudo: ler o cenário, simular os incêndios e os movimentos do animal.
   - Linha 9: Esse método lê o arquivo input.dat, que tem o cénario da floresta (onde estão as árvores, o fogo e animal). Se o arquivo não for encontrado,pode dar erro, por isso está dentro do try.
   - Linha 10: Aqui é onde a simulação realmente acontece. O simulador vai processar o que realmente acontece a cada rodada: o fogo se espalha, o animal se move, e assim vai até o fim da simulação.

 - Bloco catch:
 
 Se der algum erro durante o carregamento do arquivo ou durante a simulação, o programa não trava. Ele mostra a mensagem de erro com o "e.what()".

# 5 . COMO EXECUTAR

Será necessario usar o make fornecido:

1° make clear -> para limpeza prévia.

2° make -> compilação





