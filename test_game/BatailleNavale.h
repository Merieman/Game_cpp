#pragma once

#include "Jeu.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>


class BatailleNavale : public Jeu {
private:
    static constexpr int TAILLE_GRILLE = 5;
    static constexpr int TAILLE_CASE = 80;

    vector<vector<char>> grille;  // Grille de jeu
    int naviresRestants;
    string joueur1, joueur2;
    string joueurActuel;
    Font font;
    int j1, j2;
    void initialiserGrille();
    void placerNavires();
    bool verifierVictoire();
    void afficherGrille(RenderWindow& window);
    bool tirer(int x, int y);
    void afficherTexte(RenderWindow& window);

public:
    BatailleNavale(const string& nom1, const string& nom2);
    void lancer(RenderWindow& window) override;
};

