#ifndef FLORESTA_HPP
#define FLORESTA_HPP

#include <vector>
#include <string>

class Floresta {
private:
    int linha, coluna;
    std::vector<std::vector<int>> matriz;
    std::pair<int, int> incendioInicial;

public:
    Floresta();
    
    void carregarDoArquivo(const std::string& nomeArquivo);
    void salvarNoArquivo(const std::string& nomeArquivo, int iteracao) const;
    void propagarIncendio();
    void aplicarEfeitoAnimal(const std::pair<int, int>& posicao);
    bool incendioAtivo() const;
    void imprimir() const;

    int getLinha() const;
    int getColuna() const;
    std::vector<std::vector<int>>& getMatriz();
    const std::vector<std::vector<int>>& getMatriz() const;
    std::pair<int, int> getIncendioInicial() const;
    void setCelula(int x, int y, int valor);
};

#endif