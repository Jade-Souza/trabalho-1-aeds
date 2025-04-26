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

### Animal.cpp  < a href "https://github.com/Jade-Souza/trabalho-1-aeds/blob/main/src/Animal.cpp">

  #### - encontrarPosicaoInicial()
   Essa método busca na matriz a posição inicial para o animal. Vou explicar como ela faz isso:
    
  - 1°: Ela percorre a matriz com 2 for `(linha 25 e 27)`: o primeiro for é para percorrer a linha (i) e o segundo é para percorrer a coluna (j).

  - 2°: Eu uso um if `(linha 29)` para encontrar uma célula da matriz que tem o número 0. Se encontrar, salva  essa posição (i, j) na variável posicao `(linha 31)`, e dá um return `(linha 32)`, ou seja, já foi encontrado e para de procurar.

  - 3°: Da mesma maneira que utilizei os 2 for para percorrer a matriz anteriormente, faço isso novamente `(linha 37)`, mas agora para encontrar o número 1 ou 4 `(linha 41)`. Se encontrar um desses dois números, salvo a posição (i, j) `(linha43)`, e dou um return `(linha 44)` para parar de procurar.

  - 4°: Se não encontrar nem 0, 1 ou 4, o animal ficará na posição (0, 0) `(linha 49)`, essa atribuição é feita fora dos for anteriores.

  #### - mover()

  Essa método faz o animal se mover na matriz. Vou explicar o passo a passo:
  
  - 1°: Primeiro, usa um if pra checar se o animal ainda está vivo ,se não estiver, ele nem tenta mover, já dá return `(linha 85)`.

  - 2°: Depois, salva a posição atual do animal (x e y) `(linha 87 e 88)`.
  

- 3°: Usa um if pra ver se o animal está em cima de uma célula especial (4) `(linha 90)`, se sim, chama *aplicarEfeitos(matriz)* `(linha92)` e para (return) `(linha 93)`.

- 4°: Se a célula atual for uma área segura (0) `(linha 96)`, ele aumenta um contador *TpAreaSegura++* `(linha 98)`. Se ainda não passou 3 turnos nessa área segura, ele fica parado return `(linha 99)`. Se sair dessa área, zera o contador *TpAreaSegura = 0* `(linha101)`.

- 5°: Cria dois vetores *dx* e *dy* `(linha 103 e 104)` que representam os movimentos possíveis: cima, baixo, esquerda e direita.
  
- 6°: Usa um for `(linha 106)` para tentar andar para todos os 4 lados.
  - `(linha 108)` calcula a nova linha (nx) pra onde o animal poderia ir.Usa o vetor dx pra decidir se sobe, desce ou fica na mesma linha.
  - `(linha 109)` Calcula a nova coluna (ny) pra onde o animal poderia ir.Usa o vetor dy pra decidir se vai pra esquerda, direita ou fica na mesma coluna.
  - `(linha 111 e 112)` Verifica se a nova posição (nx, ny) está dentro da matriz,para evitar erro tentando acessar fora da matriz.
  - `(linha 114)` verifica se na posição (nx, ny) tem água (4).
  - `(linha 116)` atualiza a posição atual do animal pra essa posição nova (nx, ny) onde encontrou a água.
  - `(linha 117)` aumenta o contador de passos que o animal deu
  - `(linha 118)` chama a método *aplicarEfeitos*, porque o animal achou água e precisa fazer o efeito de encontrar a água.
  - `(linha 119)` termina a método na hora,não precisa mais continuar procurando, já encontrou o que queria (a água).

- 7°: `(linha 124)` crio uma variável melhorMovimento para guardar a melhor posição para onde o animal pode ir (linha, coluna). `(linha 125)` crio melhorPrioridade, começando em -1, que vai guardar a prioridade mais alta encontrada.

- 8°: Faço um for `(linha 127)` que vai rodar 4 vezes, testando as quatro direções: cima, baixo, esquerda e direita.
  - Calcula as novas coordenadas nx (nova linha) `(linha 129)` e ny (nova coluna) `(linha 130)` com base nos movimentos possíveis.
  - Verifico `(linha 132 e 133)` se o novo movimento (nx, ny) ainda está dentro dos limites da matriz, para evitar acessar uma posição inválida. Crio uma nova variavel prioridade `(linha 135)` para essa nova posição.
  - Com switch `(linha 136)`, eu atribuo uma prioridade dependendo do que tem na nova posição: Se for 0 (área segura), prioridade 3 `(linha 138)`; Se for 1 (árvore saudável), prioridade 2 `(linha 139)`; Se for 4 (água), prioridade 4 `(linha 140)`; Se for qualquer outra coisa (chamas, árvore queimada), prioridade -1 `(linha 131)` não é recomendado ir pra lá.
  - Compara se essa nova prioridade é melhor do que a melhor encontrada até agora `(linha 143)`.Se for melhor, atualiza melhorPrioridade `(linha 145)` e guarda essa nova posição (nx, ny) como o melhor movimento até agora `(linha 146)`.

 - 9°: Depois de testar todos os lados, verifica se achou algum movimento bom ,prioridade maior que -1 `(linha 151)`. Se achou, move o animal pra melhor posição encontrada `(linha 153)` e aumenta o número de passos que ele deu `(linha 154)`. Se não `(linha 156)` achou nenhum lugar seguro (prioridade continuou -1): O animal morre `(linha 158)` e registra a iteração em que ele morreu `(linha 159)`.

  #### - aplicarEfeito()
  Essa método trata o que acontece quando o animal encontra água na matriz. Explição:

- 1°: Primeiro, ele verifica se o animal ainda está vivo `(linha 54)`, se não estiver vivo, não faz mais nada e já dá return.

- 2°: Pega a posição atual do animal (x e y) `(linha 56 e 57)`,first é a linha, second é a coluna.

- 3°:Verifica se o animal está em cima de uma célula de água (4) (linha 59), se sim ela faz essas coisas:
    -  Aumenta o contador EncontroAgua++ `(linha 61)`.
    - Troca a célula atual de água (4) para área vazia (0) `(linha 62)`.
    - Cria os vetores dx e dy para andar para cima, baixo, esquerda e direita `(linha 64 e 65)`.
    - O for `(linha 67)` serve para olhar para os 4 vizinhos (cima, baixo, direita e esquerda), por isso o for vai se reperitir 4 vezes.
    - `(linha 69)` calcula a nova linha (nx) para onde o animal quer olhar. "dx[i]" é um vetor que diz como andar na linha: "-1" sobe, "1" desce e "0" fica na mesma linha.
    - `(linha 70)` calcula a nova coluna (ny) para onde o animal quer olhar. "dy[i]" é um vetor que diz como o andar na coluna: "-1" vai para a esquerda, "1" vai para a direita e "0" fica na mesma coluna.
    - `(linha 72)` verificar se o vizinho (nx e ny) está dentro dos limites da matriz, eu fiz isso para não dar erro tentando acessar uma posição que não existe.
    - `(linha 75)` se a célula onde o animal quer olhar não for água (4) e se a condição for verdadeira vai transformar a célula em árvore saudável (1).
    - Depois de tudo, exibe uma mensagem na tela dizendo que o animal encontrou água e mostra onde `(linha 79)`.


### Floresta.cpp <a href "https://github.com/Jade-Souza/trabalho-1-aeds/blob/main/src/Floresta.cpp">
  #### - carregarDoArquivo()

- 1°: O set `(linha 14 ate 20)` tem como objetivo alterar as células x e y, só será alterada se x e y forem válidos,para não dar erro de acessar posição inválida na matriz.

- 2°: Tenta abrir o arquivo que tem o nome passado `(linha 24)`.

- 3°: Se não conseguiu abrir `(linha 26)`, mostra erro `(linha 28)` e sai da método `(linha 29)`.

- 4°: Lê as dimensões da floresta (linha, coluna) `(linha 32)` e ajusta o tamanho da matriz `(linha 33)`.

- 5°: Lê a posição inicial do incêndio `(linha 35 até 37)`.

- 6°: Primeiro for `(linha 39)` é para pecorrer cada linha da matriz, o segundo for `(linha 41)` é para pecorrer cada coluna da matriz e assim será lido todos os valores do arquivo e preencher a matriz inteira, linha por linha.

 #### - salvarNoArquivo()

- 1°: Tenta abrir o arquivo que tem o nome passado `(linha 48)`.

- 2°: Se não conseguiu abrir `(linha 50)`, mostra erro `(linha 52)` e sai da método `(linha 53)`.

- 3°: Primeiro for `(linha 58)` é para pecorrer cada linha da matriz, o segundo for `(linha 60)` é para percorrer cada valor dentro da linha atual.

#### - propagarIncendio()

- 1°: Crio uma cópia da matriz para alterar depois `(linha 69)`.Crio uma fila para armazenar as posições das árvores em chamas `(linha 70)`.

- 2°: Primeiro for `(linha 72)` percorre da linha 0 até a última linha da matriz, segundo for `(linha 74)` percorre da coluna 0 até a última coluna de cada linha. Depois erifica se a célula está pegando fogo (2) `(linha 76)` se estiver, adiciona essa posição na fila fila.

- 3°: O while `(linha 80)` se repetirá enquanto a fila não estiver vazia,ou seja, enquanto ainda houver posições de árvores pegando fogo para processar.
  - `(linha 82)` pega o primeiro elemento da fila.

  - `(linha 83)` mesma coisa da anterio, mas pega a posição y dessa célula.

  - `(linha 84)` remove o elemento da fila ,já que agora estamos processando ele.

  - `(linha 86)` marca essa posição na novaMatriz como árvore queimada (3).

  - `(linha 88 e 89)` são vetores auxiliares para mover para as 4 direções:dx altera o x (linha) -> para cima e para baixo ;dy altera o y (coluna) -> para esquerda e direita.

  - O for `(linha 91)` que repete 4 vezes, uma para cada direção, serve para testar os quatro lados em volta da árvore que acabou de queimar.
  - Calcula o novo nx (linha) `(linha 93)` e ny (coluna) `(linha 94)` da posição vizinha .

  - `(linha 96)` Se a variável COM_VENTO estiver ativada.Se a condição anterior for verdadeira irá ocorrer outra verificação `(linha 98)` que é se a direção do movimento atual não coincide com a direção do vento.DIRECAO_VENTO[0]: indica o x do vento eDIRECAO_VENTO[1]: indica o y do vento. Se não for a direção do vento, usa continue `(linha 98)` para pular para a próxima direção (não propaga para essa célula).
  
  - `(linha 101 e 102)`Essa parte do código testa quatro condições ao mesmo tempo: verifica se o novo "x" (nx) é maior ou igual a zero ,ou seja, não é uma posição negativa e menor que o número total de linhas da matriz ,para não ultrapassar o limite inferior ou superior da floresta; faz o mesmo para o novo "y" (ny), garantindo que ele também está dentro dos limites das colunas; além disso, checa se na posição (nx, ny) existe uma árvore saudável (matriz[nx][ny] == 1). A intenção dessas verificações é garantir que a célula vizinha que o fogo pode atingir realmente existe dentro da matriz e que nela há uma árvore que pode pegar fogo.

  - `(linha 105)` atualiza a matriz principal da floresta para ser a novaMatriz modificada.Com o objetivo de trocar o estado da floresta: agora as mudanças (árvores queimadas, árvores pegando fogo) são definitivas.

  #### - aplicarEfitoAnimal()
   
- 1°: pega a linha "first" `(linha 110)` e a coluna "second" `(linha 111)`  onde o animal está.

- 2°: `(linha 113)` verifico se o animal está em cima de uma célula de água (4). Só aplica o efeito se for água.
  - `(linha 115)` troca a água (4) por área vazia (0)
  - `(linha 117 e 118)` define dois vetores que representam os movimentos possíveis: cima, baixo, esquerda e direita.
  - O for `(linha 120)` que vai testar os 4 lados: cima, baixo, esquerda e direita da célula atual.
  - `(linha 122 e 123)` calcula a posição (nx, ny) do vizinho correspondente ao movimento atual.
  - `(linha 125)` verifica se o vizinho (nx, ny) está dentro dos limites da matriz.
  - `(linha 126)` Se estiver dentro dos limites, transforma a célula vizinha em uma árvore saudável (1).

#### - incendioAtivo()

Essa método percorre toda a matriz da floresta para verificar se ainda existe algum incêndio acontecendo. Ela faz isso usando dois laços: o primeiro `(linha 133)`percorre cada linha da matriz, e o segundo `(linha 135)` percorre cada valor dentro da linha. Se encontrar alguma célula com o valor 2 `(linha 136)`, que representa uma árvore em chamas, a método imediatamente retorna true `(linha 136)`, indicando que o incêndio ainda está ativo. Se terminar de percorrer toda a matriz sem encontrar nenhum 2, retorna false `(linha 138)`, significando que o incêndio acabou.

#### - imprimir()

A método serve para mostrar o estado atual da floresta no console. Ela percorre cada linha da matriz e, para cada valor encontrado dentro da linha, imprime o valor seguido de um espaço usando std::cout. Depois que termina de imprimir todos os valores de uma linha, ela pula para a próxima linha com \n, para manter o formato correto da matriz na tela. Ao final da impressão completa da matriz, é dado mais um \n para deixar uma linha em branco, separando visualmente a matriz de outras possíveis informações que venham depois.


###  Simulador.cpp <a href "https://github.com/Jade-Souza/trabalho-1-aeds/blob/main/src/Simulador.cpp">

#### - carregarConfiguracao()

Essa método é responsável por preparar tudo para iniciar a simulação. Primeiro `(linha 10)`, ela manda a floresta carregar o cenário a partir de um arquivo de entrada chamando floresta.carregarDoArquivo(arquivoEntrada). Em seguida `(linha 11)`, chama animal.encontrarPosicaoInicial, passando a matriz da floresta, para que o animal escolha onde começar. Por fim `(linha 12)`, ela cria ou limpa o arquivo output.dat usando std::ofstream com a opção std::ios::trunc, que apaga qualquer conteúdo anterior do arquivo, deixando-o vazio e pronto para armazenar novos resultados da simulação.

#### - executarSimulação()

Essa método que é a responsável por rodar toda a simulação do fogo e do animal.

- 1°: O while `(linha 18)` irá rodar enquanto a quantidade de iterações for menor que MAX_ITERACOES e ainda existir incêndio na floresta.

- 2°: imprime uma mensagem na tela `(linha 20)`.

- 3°: `(linha 22)` manda o animal se mover dentro da floresta com base na matriz atual e na iteração atual.

- 4°: `(linha 23)` aplica os efeitos no ambiente (por exemplo, se o animal achou água) na posição onde o animal parou.

- 5°: `(linha 24)` propaga o fogo para outras árvores da floresta (simula o avanço do incêndio para a próxima iteração).

- 6°: `(linha 26)` alva a posição atual do animal na variável pos.

- 7°: Verifica `(linha 27)` se o animal está atualmente sobre uma árvore em chamas (2) e ainda está vivo.
   - Se o if for verdadeiro, imprime uma mensagem de alerta que o animal está em perigo e tentará fugir `(linha 29)`.

   - Manda o animal tentar se mover novamente para fugir do fogo.`(linha 30)`.

   - Aplica novamente os efeitos no novo local onde o animal se moveu após tentar fugir.`(linha 31)`.

- 8°: Imprime o estado atual da floresta no console (mostra a matriz) `(linha 34)`.

- 9°: Salva o estado atual da floresta no arquivo output.dat, registrando como estava após a iteração `(linha 35)`.

- 10°: Incrementa o contador de iteração em 1 `(linha 36)`.

- 11°: Verifica se o animal morreu depois da movimentação e propagação do incêndio. Se o animal tiver morrido o laço se encerra `(linha 38)`.

- 12°: Depois de terminar todas as iterações (ou se o animal morreu antes), gera o relatório final da simulação baseado no arquivo output.dat `(linha 41)`.

#### - gerarRelatorio()

Esse método  é responsável por escrever no final do arquivo de saída um resumo da simulação. Primeiro `(linha 46)`, ela abre o arquivo especificado em modo de adição (append). Em seguida `(linha 48)`, escreve o título "RELATÓRIO FINAL" e, logo depois, registra o número total de iterações realizadas (iteracao) `(linha 49)`, a quantidade de passos que o animal deu (animal.getPassos()) `(linha 50)`, e o número de vezes que o animal encontrou água (animal.getEncontroAgua()) `(linha 51)`. Depois, verifica se o animal ainda está vivo `(linha 53)`: se sim, escreve que ele sobreviveu `(linha 53)`; se não `(linha 54)`, registra que o animal morreu e em qual iteração (animal.getItMorte())`(linha 54)`. Por fim, adiciona a linha "FIM..." para indicar o encerramento do relatório `(linha 56)`.

### - main() <a href "https://github.com/Jade-Souza/trabalho-1-aeds/blob/main/src/main.cpp">

O main() é o ponto de entrada do programa. 

- 1°: Ele começa com um bloco try `(linha 6)`, que serve para capturar exceções que possam acontecer durante a execução, evitando que o programa termine de forma inesperada.

  - `(linha 8)` Cria um objeto da classe Simulador, que vai gerenciar toda a simulação da floresta e do animal.

  - `(linha 9)` chama o método carregarConfiguracao, que carrega as informações da floresta  a partir de um arquivo chamado "input.dat".

  - `(linha 10)` Depois que os dados são carregados, o programa inicia a simulação, chamando o método executarSimulacao do objeto simulador.

- 2°: O catch `(linha 13)`captura qualquer erro que possa acontecer dentro do bloco try. Se algum erro ocorrer:

  - A mensagem do erro (e.what()) é exibida no console usando std::cerr.

  - Depois disso, o programa retorna 1, indicando que terminou por causa de um problema.


# 3 - RESULTADOS

  ## ITERAÇÕES COM A INFLUÊNCIA DO VENTO:

- ITERAÇÃO 0:

  <img src="images/INFLUENCIA DO VENTO - IT 0" />





   

# 5  COMO EXECUTAR

Será necessario usar o make fornecido:

1° make clear -> para limpeza prévia.

2° make -> compilação





