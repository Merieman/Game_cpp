#include "PierrePapierCiseaux.h"
#include <iostream>

PierrePapierCiseaux::PierrePapierCiseaux() {
    srand(static_cast<unsigned>(time(0)));  // Initialisation du générateur aléatoire
}

string PierrePapierCiseaux::obtenirChoixOrdinateur() {
    string options[] = { "pierre", "papier", "ciseaux" };
    return options[rand() % 3];
}

string PierrePapierCiseaux::obtenirResultat(const string& utilisateur, const string& ordinateur) {
    if (utilisateur == ordinateur) {
        return "Égalité!";
    }
    else if ((utilisateur == "pierre" && ordinateur == "ciseaux") ||
        (utilisateur == "papier" && ordinateur == "pierre") ||
        (utilisateur == "ciseaux" && ordinateur == "papier")) {
        return "Vous gagnez!";
    }
    else {
        return "Ordinateur gagne!";
    }
}

void PierrePapierCiseaux::lancer(RenderWindow& window) {
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Erreur : Impossible de charger la police 'arial.ttf'." << endl;
        return;
    }

    Text choixTexte("Appuyez sur C (Ciseaux), P (Pierre), ou R (Papier):", font, 20);
    choixTexte.setPosition(50, 50);
    choixTexte.setFillColor(Color::Black);

    Text resultatTexte("", font, 20);
    resultatTexte.setPosition(50, 150);
    resultatTexte.setFillColor(Color::Red);

    Text scoreTexte("", font, 20);
    scoreTexte.setPosition(50, 250);
    scoreTexte.setFillColor(Color::Blue);

    int scoreUtilisateur = 0;
    int scoreOrdinateur = 0;
    int tour = 1;

    while (window.isOpen() && tour <= 3) {
        Event event;
        string choixUtilisateur = "";

        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
            else if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Escape) {
                    window.close();  // Quitter immédiatement si Echap est pressé
                }
                else if (event.key.code == Keyboard::C) {
                    choixUtilisateur = "ciseaux";
                }
                else if (event.key.code == Keyboard::P) {
                    choixUtilisateur = "pierre";
                }
                else if (event.key.code == Keyboard::R) {
                    choixUtilisateur = "papier";
                }

                if (!choixUtilisateur.empty()) {
                    string choixOrdinateur = obtenirChoixOrdinateur();
                    string resultat = obtenirResultat(choixUtilisateur, choixOrdinateur);

                    if (resultat == "Vous gagnez!") {
                        scoreUtilisateur++;
                    }
                    else if (resultat == "Ordinateur gagne!") {
                        scoreOrdinateur++;
                    }

                    resultatTexte.setString(
                        "Tour " + to_string(tour) + ": Vous avez choisi " + choixUtilisateur +
                        "\nOrdinateur a choisi: " + choixOrdinateur +
                        "\nResultat: " + resultat
                    );

                    scoreTexte.setString(
                        "Score - Vous: " + to_string(scoreUtilisateur) +
                        " | Ordinateur: " + to_string(scoreOrdinateur)
                    );

                    tour++;
                }
            }
        }

        window.clear(Color::White);
        window.draw(choixTexte);
        window.draw(resultatTexte);
        window.draw(scoreTexte);
        window.display();
    }

    // Fin du jeu
    Text finTexte("", font, 24);
    finTexte.setPosition(50, 300);
    finTexte.setFillColor(Color::Green);

    if (scoreUtilisateur > scoreOrdinateur) {
        finTexte.setString("Vous avez gagne la partie!");
    }
    else if (scoreUtilisateur < scoreOrdinateur) {
        finTexte.setString("Ordinateur a gagne la partie!");
    }
    else {
        finTexte.setString("La partie est une egalite!");
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }
        }

        window.clear(Color::White);
        window.draw(choixTexte);
        window.draw(resultatTexte);
        window.draw(scoreTexte);
        window.draw(finTexte);
        window.display();
    }
}
