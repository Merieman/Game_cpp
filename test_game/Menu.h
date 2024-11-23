#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <iostream>
using namespace std;
using namespace sf;

class Menu {
public:
    int afficher(RenderWindow& window) {
        Font font;
        if (!font.loadFromFile("arial.ttf")) {
            cerr << "Erreur : impossible de charger la police arial.ttf" << endl;
            return -1;
        }

        vector<Text> options;

        // Titre
        Text titre;
        titre.setFont(font);
        titre.setString("Menu des Jeux");
        titre.setCharacterSize(50);
        titre.setFillColor(Color::Black);
        titre.setPosition(100, 50);
        options.push_back(titre);

        // Options de menu
        vector<string> jeux = {
            "1. Snake",
            "2. Bataille Navale",
            "3. Deviner le Nombre",
            "4. Deviner le Mot",
            "5. Pierre Papier Ciseaux",
            "6. Tic Tac Toe",
            "7. Pendu"
        };

        for (size_t i = 0; i < jeux.size(); ++i) {
            Text option;
            option.setFont(font);
            option.setString(jeux[i]);
            option.setCharacterSize(30);
            option.setFillColor(Color::White);
            option.setPosition(100, 150 + i * 50);
            options.push_back(option);
        }

        // Boucle d'affichage
        while (window.isOpen()) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                if (event.type == Event::KeyPressed) {
                    if (event.key.code >= Keyboard::Num1 && event.key.code <= Keyboard::Num7) {
                        return event.key.code - Keyboard::Num0; // Retourne le numéro du jeu choisi
                    }
                }
            }

            window.clear(Color::Blue);
            for (const auto& option : options) {
                window.draw(option);
            }
            window.display();
        }
        return -1; // Fermeture
    }
};
