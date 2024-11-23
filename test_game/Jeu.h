#pragma once

#include <SFML/Graphics.hpp>
#include <string>
using namespace sf;
using namespace std;

class Jeu {
public:
    virtual void lancer(RenderWindow& window) = 0;  // Méthode virtuelle pure
    virtual ~Jeu() = default;
};
