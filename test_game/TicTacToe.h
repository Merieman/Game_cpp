#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include "Jeu.h"

class TicTacToe : public Jeu {
public:
    TicTacToe();  // Constructeur
    void lancer(RenderWindow& window) override;

private:
    char verifierGagnant(const vector<vector<char>>& plateau);
    bool estEgalite(const vector<vector<char>>& plateau);
};

