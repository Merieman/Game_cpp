#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <ctime>
#include <algorithm>
#include "Jeu.h"

class PierrePapierCiseaux : public Jeu {
public:
    PierrePapierCiseaux();  // Constructeur
    void lancer(RenderWindow& window) override;  // Implémentation du jeu

private:
    string convertirEnMinuscule(const string& s);
    string obtenirChoixOrdinateur();
    string obtenirResultat(const string& utilisateur, const string& ordinateur);
};

