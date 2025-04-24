# TRABALHO 1 - SIMULAÇÃO INCÊNDIO

ALUNO: JADE GIULIA JANUARIA DE SOUZA

PROFESSOR: MICHEL PIRES DA SILVA

DISCIPLINA: ALGORITIMOS E ESTRUTURAS DE DADOS I

# SUMARIO DO PROJETO

1 . INTRODUÇÃO

2 . ESTRUTURA DO PROJETO

3 . LOGICA DA SIMULAÇÃO

4 . SIMULAÇÃO

5 . COMPILAÇÃO


# 1 . INTRODUÇÃO

Esse trabalho tem como objetivo simular como um incêndio se espalha numa floresta, usando um mapa/matriz para
representar a área que ocorrerá o incêndio. Cada pedacinho desse mapa pode estar de um jeito: com árvores boas, pegando fogo, já queimadas, sem nada ou com água. A simulação vai levar em conta como o fogo se move, até memso se o vento estiver soprando. Também vamos colocar um animal correndo para escapar do fogo, procurando o caminho mais seguro.

# 2 . ESTRUTURA DO PROJETO

 INCLUDE: É aqui que está localizado os arquivos de cabeçalho (.hpp)

 SRC: É aqui que está localizado os aquivos de código (.cpp) 

 BIULD: É onde os binários do projeto são gerados após a compilação

# 3 . LOGICA DA SIMULAÇÃO

### Animal.cpp :
 #### - encontrarPosicaoInicial:


        void Animal::encontrarPosicaoInicial(const std::vector<std::vector<int>>& matriz)
        {
            for (size_t i = 0; i < matriz.size(); ++i)
            {
                for (size_t j = 0; j < matriz[i].size(); ++j) 
            {
                if (matriz[i][j] == 0) 
                {
                    this -> posicao = std::make_pair(i, j);
                    return;
                }
            }
        }
        
        for (size_t i = 0; i < matriz.size(); ++i) 
        {
            for (size_t j = 0; j < matriz[i].size(); ++j) 
            {
                if (matriz[i][j] == 1 || matriz[i][j] == 4) 
                {
                    this -> posicao = std::make_pair(i, j);
                    return;
                }
            }
        }
        
        this->posicao = std::make_pair(0, 0);
        }

Esse metodo recebe a matriz da floresta. Procura a primeira célula com valor 0(área segura). Se encontrar,define como posição inicial. Se não encontrar, procura por 1 (vegetação normal) ou 4 (água). Se nenhuma dessas opções existir, usa 
(0,0).

 #### - mover() A principal

        void Animal::mover(const std::vector<std::vector<int>>& matriz)
        {
            if (!this->vivo) return;

            int x = this -> posicao.first;
            int y = this -> posicao.second;
            
            if (matriz[x][y] == 0)
            {
                this->TpAreaSegura++;
                if (this -> TpAreaSegura <= 3)  {return;}
            } 
            else { this -> TpAreaSegura = 0; }

            if (matriz[x][y] == 2) 
            {
                std::cout << "ANIMAL EM PERIGO! TENTANDO FUGIR..." << std::endl;
            }

            const int dx[] = {-1, 1, 0, 0};
            const int dy[] = {0, 0, -1, 1};

            std::pair<int, int> melhorMovimento;
            int melhorPrioridade = -1;

            for (int i = 0; i < 4; ++i) 
            {
                int nx = x + dx[i];
                int ny = y + dy[i];

                if (nx >= 0 && nx < static_cast<int>(matriz.size()) && ny >= 0 && ny < static_cast<int>(matriz[0].size())) 
                {
                    
                    int prioridade;
                    switch (matriz[nx][ny]) 
                    {
                        case 4: prioridade = 3; break;  
                        case 0: prioridade = 2; break;  
                        case 1: prioridade = 1; break;  
                        case 3: prioridade = 0; break;  
                        case 2: prioridade = -1; break;
                        default: prioridade = -1;
                    }

                    if (prioridade > melhorPrioridade)
                    {
                        melhorPrioridade = prioridade;
                        melhorMovimento = std::make_pair(nx, ny);
                    }
                }
            }

            if (melhorPrioridade >= 0)
            {
                this -> posicao = melhorMovimento;
                this -> passos++;
                
                if (matriz[this->posicao.first][this->posicao.second] == 4) { this -> EncontroAgua++; }
            } 
            else 
            {
                this -> vivo = false;
                this-> ItMorte = this -> passos;
                std::cout << "ANIMAL MORREU! NAO HA ROTAS DE FUGA." << std::endl;
            }
        }

 - 1° -> Verifica se está vivo, porque se estiver morto nada será feito.
 - 2° -> Lê a posição atual (x,y).
 - 3° -> Se estiver em área segura (0), aumenta TpAreaSegura.
   - Se já ficou parado por 3 rodadas, é forçado a andar.
   - Caso contrário, permanece ali, como uma estratégia de sobrevivência.
 - 4° -> Se estiver em fogo (2), imprime alerta.
 - 5° -> Verifica as 4 direções (cima, baixo,direta e esquerda):
   - Usa vetores dx[] e dy[] para calcular as posições vizinhas.
 - 6° -> Avalia cada vizinho como base na prioridade:
   - 4 (água): prioridade 3
   - 0 (área segura): prioridade 2
   - 1 (vegetação normal): prioridade 1
   - 3 (queimado): prioridade 0    
   - 2 (fogo): prioridade -1
 - 7° -> Escolhe a melhor opção(maior prioridade):
 - 8° -> Se encontrou uma boa célula:
   - Atualiza a posição
   - Incrementa passos
   - Se a nova célula for 4, incrementa EncontroAgua
 - 9° Se não achou nenhuma célula válida:
   - Marca o animal como morto
   - Registra a iteração da morte.

 ### Floresta.cpp

 #### - carregarDoArquivo(nomeArquivo)

        void Floresta::carregarDoArquivo(const std::string& nomeArquivo) 
        {
            std::ifstream arquivo(nomeArquivo);

            if (!arquivo) 
            {
                std::cerr << "ERRO AO ABRIR O ARQUIVO " << nomeArquivo << std::endl;
                return;
            }

            arquivo >> linha >> coluna;
            matriz.resize(linha, std::vector<int>(coluna));

            int x, y;
            arquivo >> x >> y;
            incendioInicial = {x, y};

            for (int i = 0; i < linha; ++i) 
            {
                for (int j = 0; j < coluna; ++j)
                { arquivo >> matriz[i][j]; }
            }
        }


  - Abre o arquivo de entrada (input.dat).
  - Lê dimensões da matriz.
  - Lê a posição inicial do incêndio. 
  - Lê os valores da matriz e armazena, essa parte é essencial para carregar o mapa da floresta com suas zonas, água e fogo.


  #### - salvarNoArquivo      

        void Floresta::salvarNoArquivo(const std::string& nomeArquivo, int iteracao) const 
            {
                std::ofstream arquivo(nomeArquivo, std::ios::app);

                if (!arquivo)
                {
                    std::cerr << "ERRO AO ABRIR O ARQUIVO  " << nomeArquivo << std::endl;
                    return;
                }

                arquivo << "ITERAÇÃO " << iteracao << ":\n";

                for (const auto& linha : matriz) 
                {
                    for (int valor : linha) 
                    { arquivo << valor << " "; }
                    arquivo << "\n";
                }
                arquivo << "\n";
            } 

 - Abre o arquivo de saída(output.dat) no modo append.
   - O modo append é um modo de abertura de arquivos que permite adicionar (ou anexar) conteúdo ao final de um arquivo, sem apagar o que já estava nele. E eu o utilizei pois eu queria registrar o estado da floresta a cada iteração, e guardar todo o histórico no arquivo, sem sobrescrever as rodadas anteriores.
 - Escreve o número da iteração e a matriz naquele momento. Permite acompanhar a simulação ao longo do tempo.

 #### - propagarIncendio()

    void Floresta::propagarIncendio()
    {
        std::vector<std::vector<int>> novaMatriz = matriz;
        std::queue<std::pair<int, int>> fila;

        for (int i = 0; i < linha; ++i)
        {
            for (int j = 0; j < coluna; ++j)
            {
                if (matriz[i][j] == 2) {fila.push({i, j}); }
            }
        }

        while (!fila.empty())
        {
            int x = fila.front().first;  
            int y = fila.front().second;
            fila.pop();
        
            novaMatriz[x][y] = 3;
        
            const int dx[] = {-1, 1, 0, 0};
            const int dy[] = {0, 0, -1, 1};
        
            for (int i = 0; i < 4; ++i) 
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
        
                if (COM_VENTO) 
                {
                    if (dx[i] != DIRECAO_VENTO[0] && dy[i] != DIRECAO_VENTO[1]) { continue; }
                }
        
                if (nx >= 0 && nx < linha && ny >= 0 && ny < coluna && matriz[nx][ny] == 1)
                { novaMatriz[nx][ny] = 2; }
            }
        }
        matriz = novaMatriz;
    }

 Essa função simula o avanço do fogo.
 - 1° -> Cria uma nova matriz igual a atual.
 - 2° -> Coloca na fila todas as células como fogo (2).
 - 3° -> Para cada célula da fila: 
   - Marca como queimada (3) na nova matriz.
   - Verifica os 4 vizinhos.
   - Se o vento estiver ativado (COM_VENTO), só propaga na direção do vento.
   - Se o vizinho for floresta (1), vira fogo (2).
 - 4° -> Atualiza a matriz com a nova, controla como o fogo se espalha.   

 #### - aplicarEfeitoAnimal()

    void Floresta :: aplicarEfeitoAnimal(const std::pair<int, int>& posicao)
    {
        int x = posicao.first;
        int y = posicao.second;
        
        if (matriz[x][y] == 4)
        {
            matriz[x][y] = 0;
            
            const int dx[] = {-1, 1, 0, 0};
            const int dy[] = {0, 0, -1, 1};
            
            for (int i = 0; i < 4; ++i)
            {
                int nx = x + dx[i];
                int ny = y + dy[i];
                
                if (nx >= 0 && nx < linha && ny >= 0 && ny < coluna) 
                { matriz[nx][ny] = 1; }
            }
        }
    }

 - Se o animal pisar em uma célula de água (4), transforma essa célula em área segura (0).
 - Além disso, transforma os vizinhos em floresta (1). Que represnta  impacto do animal no meio ambiente, como se estivesse "limpando" a água para ganhar espaço.

 #### -  incendioAtivo() const 

    bool Floresta::incendioAtivo() const
    {
        for (const auto& linha : matriz)
        {
            for (int valor : linha) 
            { if (valor == 2) return true; }
        }
        return false;
    }

 Verifica se ainda existem células com fogo (2) e retorna true se tiver e se não tiver retorna false.

 #### - imprimir()    

    void Floresta::imprimir() const 
    {
        for (const auto& linha : matriz) 
        {
            for (int valor : linha) 
            { std::cout << valor << " "; }
            
            std::cout << "\n";
        }
        
        std::cout << "\n";
    }
 Vai imprimir o mapa/matriz da floresta no terminal.

 ### Simulador.cpp
 #### -  carregarConfiguracao()

    void Simulador::carregarConfiguracao(const std::string& arquivoEntrada)
    {
        floresta.carregarDoArquivo(arquivoEntrada);
        animal.encontrarPosicaoInicial(floresta.getMatriz());
        std::ofstream output("output.dat", std::ios::trunc); 
        /* trunc -> apagar todo o conteúdo anterior do arquivo assim que ele for aberto.Se o arquivo já existir, o conteúdo dele será deletado na hora.Se o arquivo não existir, ele será criado vazio.*/
        output.close();
    }

 - Carrega a floresta a partir do arquivo.
 - Determina a posição inicial do animal.
 - Limpa o arquivo de saída (output.dat).    

### - executarSimulacao() - Essa é a função principal

    void Simulador::executarSimulacao() 
    {
        while (iteracao < MAX_ITERACOES && floresta.incendioAtivo())
        {
            std::cout << "\n--- ITERAÇÃO " << iteracao << " ---" << std::endl;
            
            animal.mover(floresta.getMatriz());
            floresta.aplicarEfeitoAnimal(animal.getPosicao());
            floresta.propagarIncendio();
            
            auto pos = animal.getPosicao();
            if (floresta.getMatriz()[pos.first][pos.second] == 2 && animal.estaVivo()) 
            {
                std::cout << "ANIMAL EM PERIGO! TENTANDO FUGIR NOVAMENTE..." << std::endl;
                animal.mover(floresta.getMatriz());
                floresta.aplicarEfeitoAnimal(animal.getPosicao());
            }
            
            floresta.imprimir();
            floresta.salvarNoArquivo("output.dat", iteracao);     
            iteracao++;
            
            if (!animal.estaVivo()) { break; }
        }
        
        gerarRelatorioFinal("output.dat");
    }

 - 1° -> Enquanto:
   - número de iterações < MAX_ITERACOES >
   - e ainda houver incêndio
 - 2° -> A cada iteração: 
   - O animal tenta se mover.
   - Aplica efeitos se ele pisou em água.
   - O fogo se propaga.
   - Se o animal ficou no fogo, tenta se mover de novo.
   - Mostra a matriz e salva no arquivo.
   - Incrementa a iteração.
   - Se o animal morrer, encerra o loop. 

#### - gerarRelatorioFinal()

    void Simulador::gerarRelatorioFinal(const std::string& arquivoSaida) const 
    {
        std::ofstream output(arquivoSaida, std::ios::app);
        
        output << "\n=== RELATÓRIO FINAL ===\n";
        output << "TOTAL DE ITERAÇÕES: " << iteracao << "\n";
        output << "PASSOS DO ANIMAL: " << animal.getPassos() << "\n";
        output << "ENCONTROS COM ÁGUA: " << animal.getEncontroAgua() << "\n";
        
        if (animal.estaVivo()) { 
            output << "STATUS: ANIMAL SOBREVIVEU!\n"; 
        } else { 
            output << "STATUS: ANIMAL MORREU NA ITERAÇÃO " << animal.getItMorte() << "\n"; 
        }
        
        output << "FIM...\n";
    }

 - Ao final da simulação, escreve um relatório com:
  - Total de iterações.
  - Quantos passos o animal deu.
  - Quantos encontros com água.
  - Se ele sobreviveu ou morreu (e em qual iteração).  

### - main.cpp

    int main() 
    {
        try 
        {
            Simulador simulador;
            simulador.carregarConfiguracao("input.dat");
            simulador.executarSimulacao();
            return 0;
        } 
        catch (const std::exception& e)
        {
            std::cerr << "Error: " << e.what() << std::endl;
            return 1;
        }
    }   

O ponto de início do programa é a função main(), onde instanciamos um objeto da classe Simulador. Esse objeto tem a tarefa de ler as configurações da floresta e do animal do arquivo input.dat e, então, dar andamento à simulação completa do incêndio e da luta do animal para sobreviver. Para garantir a estabilidade, usamos um bloco try-catch, que lida com quaisquer problemas (exceções) que possam surgir, como erros ao abrir arquivos ou ao acessar dados incorretos. Se tudo correr bem, o programa retorna 0, sinalizando que foi executado com sucesso. No entanto, se ocorrer algum problema e uma exceção for disparada, o bloco catch a intercepta, exibe uma mensagem de erro detalhada usando e.what() e o programa retorna 1, mostrando que houve um problema durante a execução. Isso impede que o programa pare de funcionar repentinamente.


### Config.hpp

    #ifndef CONFIG_HPP
    #define CONFIG_HPP

    const int MAX_ITERACOES = 1000; 
    const bool COM_VENTO = false;
    const int DIRECAO_VENTO[] = {1, 0, -1, 0};

    #endif  

 - MAX_ITERACOES -> define o número máximo de iterações da simulação como 1000.Isso serve para evitar que o programa entre em loop infinito, se o incêndio não acabar, ele será forçado a parar após 1000 ciclos.

 - COM_VENTO -> Define se o vento está ativado ou não na propagação do incêndio.
Quando false, o fogo se propaga normalmente em todas as direções. Se mudar para true, o fogo só vai se espalhar na direção definida por DIRECAO_VENTO.

 - DIRECAO_VENTO[] -> Define um vetor com direções possíveis do vento (usado na propagação do fogo).
   - Pode representar, por exemplo:
    - {1, 0} → vento para baixo
    - {0, 1} → direita
    - {-1, 0} → cima
    - {0, -1} → esquerda

No meu código, quando o vento está ativo (COM_VENTO = true), ele verifica se o fogo vai se espalhar somente naquela direção.


# 5 . COMO EXECUTAR

Será necessario usar o make fornecido:

1° make clear -> para limpeza prévia.

2° make -> compilação





