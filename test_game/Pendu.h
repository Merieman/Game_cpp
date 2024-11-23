#pragma once

#include <SFML/Graphics.hpp>
#include <string>
#include <vector>
#include <ctime>
#include "Jeu.h"


class Pendu : public Jeu {
private:
    vector<string> mots;  // Liste des mots
    string motSecret;          // Mot secret choisi
    string motDevine;          // Mot avec les lettres devinées
    int tentativesRestantes;        // Nombre de tentatives restantes
    string lettresDevinees;   // Lettres déjà devinées

public:
    Pendu();  // Constructeur
    void lancer(RenderWindow& window) override;
};

