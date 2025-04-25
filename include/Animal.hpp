#ifndef _ANIMAL_HPP
#define _ANIMAL_HPP

#include <utility>
#include <vector>

class Animal
{
    private:
        std::pair<int, int> posicao;
        int passos;
        int EncontroAgua;
        int ItMorte;
        bool vivo;
        int TpAreaSegura;
        int iteracao; 

    public:
        Animal();

        void encontrarPosicaoInicial(const std::vector<std::vector<int>>& matriz);
        void mover(std::vector<std::vector<int>>& matriz, int iteracao);
        void aplicarEfeitos(std::vector<std::vector<int>>& matriz);
        
        bool estaVivo() const;
        int getPassos() const;
        int getEncontroAgua() const;
        int getItMorte() const;
        std::pair<int, int> getPosicao() const;
        void setIteracao(int iter);      
};


#endif