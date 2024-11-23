#pragma once


#include "Jeu.h"
#include <iostream>
#include <SFML/Graphics.hpp>
#include <vector>

class SnakeGame : public Jeu {
private:
    static constexpr int WIDTH = 40;     // Largeur de la grille
    static constexpr int HEIGHT = 30;    // Hauteur de la grille
    static constexpr int SIZE = 20;      // Taille d'une case
    bool gameOver;

    enum Direction { STOP, LEFT, RIGHT, UP, DOWN };
    Direction dir;

    int x, y;                            // Position de la tête
    int fruitX, fruitY;                  // Position du fruit
    int score, nTail;                    // Score et taille de la queue
    vector<Vector2i> tail;      // Queue du serpent

    void deplacerSerpent();

public:
    SnakeGame();
    void lancer(RenderWindow& window) override;
};

