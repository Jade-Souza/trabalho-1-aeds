#include "Simulador.hpp"
#include "Config.hpp"
#include <fstream>
#include <iostream>

Simulador::Simulador() { this->iteracao = 0; }

void Simulador::carregarConfiguracao(const std::string& arquivoEntrada)
{
    floresta.carregarDoArquivo(arquivoEntrada);
    animal.encontrarPosicaoInicial(floresta.getMatriz());
    std::ofstream output("output.dat", std::ios::trunc);
    output.close();
}

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