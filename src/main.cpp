#include "Simulador.hpp"
#include <iostream>

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

