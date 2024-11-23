#include "TicTacToe.h"
#include <iostream>

TicTacToe::TicTacToe() {}

void TicTacToe::lancer(RenderWindow& window) {
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Erreur : impossible de charger la police 'arial.ttf'." << endl;
        return;
    }

    bool rejouer = true;  // Variable pour gérer le redémarrage du jeu

    while (window.isOpen() && rejouer) {
        // Initialisation pour une nouvelle partie
        vector<vector<char>> plateau(3, vector<char>(3, ' '));  // Plateau vide
        bool tourJoueurX = true;
        bool partieTerminee = false;
        string message = "Tour du joueur : X";
        rejouer = false;  // Réinitialisé ici pour ne pas redémarrer automatiquement

        Text texteMessage;
        texteMessage.setFont(font);
        texteMessage.setCharacterSize(24);
        texteMessage.setFillColor(Color::Black);
        texteMessage.setPosition(50, 20);

        float tailleCase = 100.0f;
        float offsetX = 150.0f, offsetY = 100.0f;

        // Boucle principale de la partie
        while (window.isOpen() && !partieTerminee) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }

                if (event.type == Event::MouseButtonPressed && !partieTerminee) {
                    Vector2i souris = Mouse::getPosition(window);
                    int ligne = (souris.y - offsetY) / tailleCase;
                    int colonne = (souris.x - offsetX) / tailleCase;

                    if (ligne >= 0 && ligne < 3 && colonne >= 0 && colonne < 3) {
                        if (plateau[ligne][colonne] == ' ') {
                            plateau[ligne][colonne] = tourJoueurX ? 'X' : 'O';
                            tourJoueurX = !tourJoueurX;
                            message = "Tour du joueur : " + string(1, tourJoueurX ? 'X' : 'O');

                            char gagnant = verifierGagnant(plateau);
                            if (gagnant != ' ') {
                                message = string("Joueur ") + gagnant + " a gagné !";
                                partieTerminee = true;
                            }
                            else if (estEgalite(plateau)) {
                                message = "Match nul !";
                                partieTerminee = true;
                            }
                        }
                    }
                }
            }

            texteMessage.setString(message);

            window.clear(Color::White);

            // Dessin des lignes du plateau
            for (int i = 0; i < 4; ++i) {
                RectangleShape ligneHorizontale(Vector2f(3 * tailleCase, 2));
                ligneHorizontale.setPosition(offsetX, offsetY + i * tailleCase);
                ligneHorizontale.setFillColor(Color::Black);
                window.draw(ligneHorizontale);

                RectangleShape ligneVerticale(Vector2f(2, 3 * tailleCase));
                ligneVerticale.setPosition(offsetX + i * tailleCase, offsetY);
                ligneVerticale.setFillColor(Color::Black);
                window.draw(ligneVerticale);
            }

            // Dessin des symboles sur le plateau
            for (int i = 0; i < 3; ++i) {
                for (int j = 0; j < 3; ++j) {
                    if (plateau[i][j] == 'X' || plateau[i][j] == 'O') {
                        Text symbole;
                        symbole.setFont(font);
                        symbole.setCharacterSize(48);
                        symbole.setFillColor(Color::Black);
                        symbole.setString(string(1, plateau[i][j]));
                        symbole.setPosition(offsetX + j * tailleCase + 25, offsetY + i * tailleCase + 10);
                        window.draw(symbole);
                    }
                }
            }

            window.draw(texteMessage);
            window.display();
        }

        // Affichage du gagnant et des instructions pour continuer
        Text gagnantTexte(message, font, 28);
        gagnantTexte.setFillColor(Color::Red);
        gagnantTexte.setPosition(50, 300);

        Text instructionTexte("Appuyez sur R pour rejouer ou sur Échap pour quitter.", font, 20);
        instructionTexte.setFillColor(Color::Black);
        instructionTexte.setPosition(50, 350);

        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                else if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Escape) {
                        window.close();  // Quitter immédiatement si Échap est pressé
                    }
                    else if (event.key.code == Keyboard::R) {
                        rejouer = true;  // Indique qu'une nouvelle partie doit commencer
                        break;
                    }
                }
            }

            if (rejouer) break;  // Sort de la boucle d'affichage pour redémarrer une nouvelle partie

            window.clear(Color::White);
            window.draw(gagnantTexte);
            window.draw(instructionTexte);
            window.display();
        }
    }
}

char TicTacToe::verifierGagnant(const vector<vector<char>>& plateau) {
    for (int i = 0; i < 3; ++i) {
        if (plateau[i][0] == plateau[i][1] && plateau[i][1] == plateau[i][2] && plateau[i][0] != ' ') {
            return plateau[i][0];
        }
        if (plateau[0][i] == plateau[1][i] && plateau[1][i] == plateau[2][i] && plateau[0][i] != ' ') {
            return plateau[0][i];
        }
    }
    if (plateau[0][0] == plateau[1][1] && plateau[1][1] == plateau[2][2] && plateau[0][0] != ' ') {
        return plateau[0][0];
    }
    if (plateau[0][2] == plateau[1][1] && plateau[1][1] == plateau[2][0] && plateau[0][2] != ' ') {
        return plateau[0][2];
    }
    return ' ';
}

bool TicTacToe::estEgalite(const vector<vector<char>>& plateau) {
    for (const auto& ligne : plateau) {
        for (char c : ligne) {
            if (c == ' ') {
                return false;
            }
        }
    }
    return true;
}
