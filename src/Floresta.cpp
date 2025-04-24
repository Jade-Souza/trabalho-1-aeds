#include "Floresta.hpp"
#include "Config.hpp"
#include <fstream>
#include <iostream>
#include <queue>


Floresta::Floresta()
{
    this -> linha = 0;
    this -> coluna = 0;
}

void Floresta::setCelula(int x, int y, int valor)
{
    if (x >= 0 && x < this->linha && y >= 0 && y < this->coluna) {
        this->matriz[x][y] = valor;
    }
}

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

bool Floresta::incendioAtivo() const
{
    for (const auto& linha : matriz)
    {
        for (int valor : linha) 
        { if (valor == 2) return true; }
    }
    return false;
}

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

const std::vector<std::vector<int>>& Floresta::getMatriz() const {return this->matriz;}
std::pair<int, int> Floresta::getIncendioInicial() const {return this->incendioInicial;}
int Floresta::getLinha() const { return this -> linha;}
int Floresta::getColuna() const {return this -> coluna;}