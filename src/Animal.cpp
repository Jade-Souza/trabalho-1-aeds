#include "Animal.hpp"
#include <iostream>
#include <utility>
#include <vector>

Animal :: Animal() 
{
    this -> posicao = std::make_pair(0, 0);
    this -> passos = 0;
    this -> EncontroAgua = 0;
    this -> ItMorte = iteracao;
    this -> vivo = true;
    this -> TpAreaSegura = 0;
}

bool Animal :: estaVivo() const {return this -> vivo;}
int Animal :: getPassos() const {return this -> passos;}
int Animal :: getEncontroAgua() const {return this -> EncontroAgua;}
int Animal::getItMorte() const {return this -> ItMorte;}
std::pair<int, int> Animal :: getPosicao() const {return this -> posicao;}
void Animal::setIteracao(int iter) {iteracao = iter;}

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

void Animal::aplicarEfeitos(std::vector<std::vector<int>>& matriz)
{
    if (!this->vivo) return;
    
    int x = this->posicao.first;
    int y = this->posicao.second;
    
    if (matriz[x][y] == 4)
    {
        this->EncontroAgua++;
        matriz[x][y] = 0;

        const int dx[] = {-1, 1, 0, 0};
        const int dy[] = {0, 0, -1, 1};
        
        for (int i = 0; i < 4; ++i)
        {
            int nx = x + dx[i];
            int ny = y + dy[i];
            
            if (nx >= 0 && nx < static_cast<int>(matriz.size()) && 
                ny >= 0 && ny < static_cast<int>(matriz[0].size()))
            {
                if (matriz[nx][ny] != 4) { matriz[nx][ny] = 1; }
            }
        }
        
        std::cout << "ANIMAL ENCONTROU ÁGUA EM (" << x << "," << y << ")!\n";
    }
}

void Animal::mover(std::vector<std::vector<int>>& matriz, int iteracao)
{
    if (!this->vivo) return;

    int x = this->posicao.first;
    int y = this->posicao.second;

    if (matriz[x][y] == 4) 
    {
        aplicarEfeitos(matriz);
        return;
    }

    if (matriz[x][y] == 0)
    {
        this->TpAreaSegura++;
        if (this->TpAreaSegura <= 3) return;
    } 
    else { this->TpAreaSegura = 0; }

    const int dx[] = {-1, 1, 0, 0};
    const int dy[] = {0, 0, -1, 1};

    for (int i = 0; i < 4; ++i)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];
        if (nx >= 0 && nx < static_cast<int>(matriz.size()) && 
            ny >= 0 && ny < static_cast<int>(matriz[0].size()))
        {
            if (matriz[nx][ny] == 4) 
            {
                this->posicao = {nx, ny};
                this->passos++;
                aplicarEfeitos(matriz);
                return;
            }
        }
    }

    std::pair<int, int> melhorMovimento;
    int melhorPrioridade = -1;
    for (int i = 0; i < 4; ++i)
    {
        int nx = x + dx[i];
        int ny = y + dy[i];

        if (nx >= 0 && nx < static_cast<int>(matriz.size()) && 
            ny >= 0 && ny < static_cast<int>(matriz[0].size()))
        {
            int prioridade;
            switch (matriz[nx][ny])
            {
                case 0: prioridade = 3; break;
                case 1: prioridade = 2; break;
                case 4: prioridade = 4; break;
                default: prioridade = -1;
            }
            if (prioridade > melhorPrioridade)
            {
                melhorPrioridade = prioridade;
                melhorMovimento = {nx, ny};
            }
        }
    }

    if (melhorPrioridade > -1)
    {
        this->posicao = melhorMovimento;
        this->passos++;
    } 
    else
    {
        this->vivo = false;
        this->ItMorte = iteracao;
    }
}