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
                caseGrille.setFillColor(Color::Red);  // Touch�
            }
            else if (grille[i][j] == 'O') {
                caseGrille.setFillColor(Color::Blue);  // Rat�
            }
            else {
                caseGrille.setFillColor(Color::White);  // Non r�v�l�
            }

            window.draw(caseGrille);
        }
    }
}

bool BatailleNavale::tirer(int x, int y) {
    if (x < 0 || x >= TAILLE_GRILLE || y < 0 || y >= TAILLE_GRILLE) {
        return false;  // Clic hors de la grille
    }

    // V�rifier si la case est d�j� touch�e ou rat�e
    if (grille[x][y] == 'X' || grille[x][y] == 'O') {
        return false;  // Ne rien faire si la case est d�j� marqu�e
    }

    if (grille[x][y] == 'S') {
        grille[x][y] = 'X';  // Touch�
        naviresRestants--;
        (joueurActuel == joueur1) ? j1++ : j2++;
        return true;
    }
    else if (grille[x][y] == '~') {
        grille[x][y] = 'O';  // Rat�
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

            // G�rer l'�v�nement pour �chap (quitter) et R (rejouer) **avant** les clics
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    window.close();  // Fermer le jeu si �chap est press�
                }
                if (event.key.code == Keyboard::R && jeuTermine) {
                    // R�initialiser le jeu si R est press� apr�s la fin
                    joueurActuel = joueur1;
                    j1 = 0;
                    j2 = 0;
                    naviresRestants = 3;
                    initialiserGrille();
                    placerNavires();
                    jeuTermine = false;  // R�initialiser l'�tat du jeu
                }
            }

            // Les joueurs ne peuvent pas tirer apr�s la fin du jeu
            if (jeuTermine) continue;

            if (event.type == Event::MouseButtonPressed && event.mouseButton.button == Mouse::Left) {
                int x = event.mouseButton.y / TAILLE_CASE;  // Ligne
                int y = event.mouseButton.x / TAILLE_CASE;  // Colonne
                // V�rifier si la case a d�j� �t� jou�e
                if (grille[x][y] == 'X' || grille[x][y] == 'O') {
                    continue;  // Ne rien faire si la case est d�j� marqu�e
                }
                if (tirer(x, y)) {
                    if (verifierVictoire()) {
                        string winner;
                        j1 > j2 ? winner = joueur1 : winner = joueur2;
                        cout << winner + " a gagn� !" << endl;
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
            Text gameOverText("Le joueur " + joueurActuel + " a gagn� !\nAppuyez sur '�chap' pour quitter ou 'R' pour rejouer.", font, 20);
            gameOverText.setFillColor(Color::Black);
            gameOverText.setPosition(10, TAILLE_CASE * TAILLE_GRILLE + 100);
            window.draw(gameOverText);
        }

        window.display();
    }
}
