#include "BatailleNavale.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>

BatailleNavale::BatailleNavale(const string& nom1, const string& nom2)
    : joueur1(nom1), joueur2(nom2), joueurActuel(nom1),j1(0),j2(0) {
    initialiserGrille();
    placerNavires();
    srand(static_cast<unsigned>(time(0)));

    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Erreur : impossible de charger la police 'arial.ttf'." << endl;
    }
}

void BatailleNavale::initialiserGrille() {
    grille.assign(TAILLE_GRILLE, vector<char>(TAILLE_GRILLE, '~'));
    naviresRestants = 3;
}

void BatailleNavale::placerNavires() {
    int naviresAPlacer = naviresRestants;
    while (naviresAPlacer > 0) {
        int x = rand() % TAILLE_GRILLE;
        int y = rand() % TAILLE_GRILLE;
        if (grille[x][y] == '~') {
            grille[x][y] = 'S';  // Navire
            naviresAPlacer--;
        }
    }
}

bool BatailleNavale::verifierVictoire() {
    for (const auto& ligne : grille) {
        for (char cell : ligne) {
            if (cell == 'S') return false;  // Il reste des navires
        }
    }
    return true;
}

void BatailleNavale::afficherGrille(RenderWindow& window) {
    for (int i = 0; i < TAILLE_GRILLE; i++) {
        for (int j = 0; j < TAILLE_GRILLE; j++) {
            RectangleShape caseGrille(Vector2f(TAILLE_CASE - 5, TAILLE_CASE - 5));
            caseGrille.setPosition(j * TAILLE_CASE, i * TAILLE_CASE);
            caseGrille.setOutlineThickness(2);
            caseGrille.setOutlineColor(Color::Black);

            if (grille[i][j] == 'X') {
                caseGrille.setFillColor(Color::Red);  // Touché
            }
            else if (grille[i][j] == 'O') {
                caseGrille.setFillColor(Color::Blue);  // Raté
            }
            else {
                caseGrille.setFillColor(Color::White);  // Non révélé
            }

            window.draw(caseGrille);
        }
    }
}

bool BatailleNavale::tirer(int x, int y) {
    if (x < 0 || x >= TAILLE_GRILLE || y < 0 || y >= TAILLE_GRILLE) {
        return false;  // Clic hors de la grille
    }

    // Vérifier si la case est déjà touchée ou ratée
    if (grille[x][y] == 'X' || grille[x][y] == 'O') {
        return false;  // Ne rien faire si la case est déjà marquée
    }

    if (grille[x][y] == 'S') {
        grille[x][y] = 'X';  // Touché
        naviresRestants--;
        (joueurActuel == joueur1) ? j1++ : j2++;
        return true;
    }
    else if (grille[x][y] == '~') {
        grille[x][y] = 'O';  // Raté
    }
    return false;
}


void BatailleNavale::afficherTexte(RenderWindow& window) {
    Text info1("Joueur actuel : " + joueurActuel, font, 20);
    info1.setPosition(10, TAILLE_CASE * TAILLE_GRILLE + 10);
    info1.setFillColor(Color::Black);

    Text stats("Navires restants : " + to_string(naviresRestants), font, 20);
    stats.setPosition(10, TAILLE_CASE * TAILLE_GRILLE + 40);
    stats.setFillColor(Color::Black);

    Text info2(joueur1 + " : " + to_string(j1) + "\t" + joueur2 + " : " + to_string(j2), font, 20);
    info2.setPosition(10, TAILLE_CASE * TAILLE_GRILLE + 70);
    info2.setFillColor(Color::Black);

    window.draw(info1);
    window.draw(info2);
    window.draw(stats);
}

void BatailleNavale::lancer(RenderWindow& window) {
    bool jeuTermine = false;
    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            // Gérer l'événement pour Échap (quitter) et R (rejouer) **avant** les clics
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    window.close();  // Fermer le jeu si Échap est pressé
                }
                if (event.key.code == Keyboard::R && jeuTermine) {
                    // Réinitialiser le jeu si R est pressé après la fin
                    joueurActuel = joueur1;
                    j1 = 0;
                    j2 = 0;
                    naviresRestants = 3;
                    initialiserGrille();
                    placerNavires();
                    jeuTermine = false;  // Réinitialiser l'état du jeu
                }
            }

            // Les joueurs ne peuvent pas tirer après la fin du jeu
            if (jeuTermine) continue;

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                int x = event.mouseButton.y / TAILLE_CASE;  // Ligne
                int y = event.mouseButton.x / TAILLE_CASE;  // Colonne
                // Vérifier si la case a déjà été jouée
                if (grille[x][y] == 'X' || grille[x][y] == 'O') {
                    continue;  // Ne rien faire si la case est déjà marquée
                }
                if (tirer(x, y)) {
                    if (verifierVictoire()) {
                        string winner;
                        j1 > j2 ? winner = joueur1 : winner = joueur2;
                        cout << winner + " a gagné !" << endl;
                        jeuTermine = true;
                    }
                }
                else {
                    joueurActuel = (joueurActuel == joueur1) ? joueur2 : joueur1;
                }
            }
        }

        window.clear(Color::White);
        afficherGrille(window);
        afficherTexte(window);

        // Afficher le message de fin de jeu
        if (jeuTermine) {
            Text gameOverText("Le joueur " + joueurActuel + " a gagné !\nAppuyez sur 'Échap' pour quitter ou 'R' pour rejouer.", font, 20);
            gameOverText.setFillColor(Color::Black);
            gameOverText.setPosition(10, TAILLE_CASE * TAILLE_GRILLE + 100);
            window.draw(gameOverText);
        }

        window.display();
    }
}
