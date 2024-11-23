#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <cstdlib>
#include <ctime>
#include "Jeu.h"


class DevinerNombre : public Jeu {
public:
    DevinerNombre();  // Constructeur
    void lancer(RenderWindow& window) override;  // Implémentation du jeu
};


