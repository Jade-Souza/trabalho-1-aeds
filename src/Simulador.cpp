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
        std::cout << "\n--- ITERACAO " << iteracao << " ---" << std::endl;
        animal.mover(floresta.getMatriz());
        animal.aplicarEfeitos(floresta.getMatriz());
    
        auto pos = animal.getPosicao();
        if (floresta.getMatriz()[pos.first][pos.second] == 2 && animal.estaVivo())
        {
            animal.mover(floresta.getMatriz());
            animal.aplicarEfeitos(floresta.getMatriz());
        }
    
        floresta.propagarIncendio();
        floresta.imprimir();
        floresta.salvarNoArquivo("output.dat", iteracao);
        iteracao++;
        
        if (!animal.estaVivo()) break;
    }
    
    gerarRelatorioFinal("output.dat");
}

void Simulador::gerarRelatorioFinal(const std::string& arquivoSaida) const 
{
    std::ofstream output(arquivoSaida, std::ios::app);
    
    output << "\n=== RELATORIO FINAL ===\n";
    output << "TOTAL DE ITERACOES: " << iteracao << "\n";
    output << "PASSOS DO ANIMAL: " << animal.getPassos() << "\n";
    output << "ENCONTROS COM AGUA: " << animal.getEncontroAgua() << "\n";
    
    if (animal.estaVivo())
    { output << "STATUS: ANIMAL SOBREVIVEU!\n"; } 
    else { output << "STATUS: ANIMAL MORREU NA ITERACAO " << animal.getItMorte() << "\n"; }
    
    output << "FIM...\n";
}