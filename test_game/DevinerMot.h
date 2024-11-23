#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <ctime>
#include <cstdlib>
#include "Jeu.h"


class DevinerMot : public Jeu {
private:
    string ajusterTexte(const string& texte, unsigned int largeurMax, Font& font, unsigned int tailleTexte);
public:
    DevinerMot();  // Constructeur
    void lancer(RenderWindow& window) override;  // Implémentation du jeu


};


