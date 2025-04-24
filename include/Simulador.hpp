#ifndef SIMULADOR_HPP
#define SIMULADOR_HPP

#include "Floresta.hpp"
#include "Animal.hpp"
#include <string>

class Simulador 
{
    private:
        Floresta floresta;
        Animal animal;
        int iteracao;
        
    public:
        Simulador();
        
        void carregarConfiguracao(const std::string& arquivoEntrada);
        void executarSimulacao();
        void gerarRelatorioFinal(const std::string& arquivoSaida) const;
};

#endif