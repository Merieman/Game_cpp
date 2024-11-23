#include "DevinerNombre.h"
#include <iostream>

DevinerNombre::DevinerNombre() {
    // Initialisation du générateur aléatoire
    srand(static_cast<unsigned>(time(0)));
}

void DevinerNombre::lancer(RenderWindow& window) {
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Erreur : Impossible de charger la police 'arial.ttf'." << endl;
        return;
    }

    bool rejouer = true;

    while (rejouer && window.isOpen()) {
        int nombreSecret = rand() % 100 + 1;
        int nombreUtilisateur = 0;
        string saisieUtilisateur = "";
        int tentatives = 0;
        bool trouve = false;

        Text prompt("Devinez un nombre entre 1 et 100 :", font, 20);
        prompt.setPosition(50, 50);
        prompt.setFillColor(Color::Black);

        Text saisieTexte("Votre nombre : ", font, 20);
        saisieTexte.setPosition(50, 100);
        saisieTexte.setFillColor(Color::Blue);

        Text resultat("", font, 20);
        resultat.setPosition(50, 150);
        resultat.setFillColor(Color::Red);

        Text rejouerTexte("Appuyez sur 'R' pour rejouer ou 'Echap' pour quitter.", font, 18);
        rejouerTexte.setPosition(50, 300);
        rejouerTexte.setFillColor(Color::Black);

        while (window.isOpen() && !trouve) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                else if (event.type == Event::TextEntered) {
                    char lettre = static_cast<char>(event.text.unicode);

                    if (isdigit(lettre) && saisieUtilisateur.size() < 3) {
                        saisieUtilisateur += lettre;
                    }
                    else if (lettre == '\b' && !saisieUtilisateur.empty()) {
                        saisieUtilisateur.pop_back();
                    }
                    else if (lettre == '\r' && !saisieUtilisateur.empty()) {
                        nombreUtilisateur = stoi(saisieUtilisateur);
                        tentatives++;

                        if (nombreUtilisateur == nombreSecret) {
                            resultat.setString("Bravo ! Vous avez devine en " + to_string(tentatives) + " tentatives.");
                            resultat.setFillColor(Color::Green);
                            trouve = true;
                        }
                        else if (nombreUtilisateur < nombreSecret) {
                            resultat.setString("Trop petit !");
                        }
                        else {
                            resultat.setString("Trop grand !");
                        }

                        saisieUtilisateur = "";
                    }
                }
            }

            saisieTexte.setString("Votre nombre : " + saisieUtilisateur);

            window.clear(Color::White);
            window.draw(prompt);
            window.draw(saisieTexte);
            window.draw(resultat);
            window.display();
        }

        if (trouve) {
            bool attendreAction = true;
            while (attendreAction && window.isOpen()) {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        window.close();
                    }
                    else if (event.type == Event::KeyPressed) {
                        if (event.key.code == Keyboard::R) {
                            rejouer = true;
                            attendreAction = false;
                        }
                        else if (event.key.code == Keyboard::Escape) {
                            rejouer = false;
                            attendreAction = false;
                        }
                    }
                }

                window.clear(Color::White);
                window.draw(resultat);
                window.draw(rejouerTexte);
                window.display();
            }
        }
    }
}
