#include "Pendu.h"
#include <iostream>

Pendu::Pendu() {
    // Initialisation des variables du jeu dans le constructeur
    mots = { "ordinateur", "programmation", "logiciel", "algorithme", "électronique" };
    srand(static_cast<unsigned>(time(0)));  // Initialisation du générateur de nombres aléatoires
    motSecret = mots[rand() % mots.size()];
    motDevine = string(motSecret.length(), '_');
    tentativesRestantes = 6;
    lettresDevinees = "";
}

void Pendu::lancer(RenderWindow& window) {
    // Charger une police prenant en charge les caractères spéciaux
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cout << "Erreur : impossible de charger la police arial.ttf" << endl;
        return;
    }

    // Créer des textes SFML
    Text prompt, tentatives, lettresUtilisees, resultat;
    prompt.setFont(font);
    prompt.setCharacterSize(24);
    prompt.setFillColor(Color::Black);
    prompt.setPosition(50, 50);

    tentatives.setFont(font);
    tentatives.setCharacterSize(24);
    tentatives.setFillColor(Color::Black);
    tentatives.setPosition(50, 100);

    lettresUtilisees.setFont(font);
    lettresUtilisees.setCharacterSize(24);
    lettresUtilisees.setFillColor(Color::Black);
    lettresUtilisees.setPosition(50, 150);

    resultat.setFont(font);
    resultat.setCharacterSize(24);
    resultat.setFillColor(Color::Black);
    resultat.setPosition(50, 200);

    bool rejouer = true;  // Variable pour gérer le redémarrage du jeu

    while (window.isOpen() && rejouer) {
        // Réinitialiser les variables à chaque nouvelle partie
        motSecret = mots[rand() % mots.size()];
        motDevine = string(motSecret.length(), '_');
        tentativesRestantes = 6;
        lettresDevinees = "";
        rejouer = false;  // Réinitialisation de la variable de redémarrage

        // Boucle de jeu
        while (window.isOpen() && tentativesRestantes > 0 && motDevine != motSecret) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                // Gestion de la saisie utilisateur pour les lettres
                else if (event.type == Event::TextEntered) {
                    char lettre = static_cast<char>(event.text.unicode);
                    if (isalpha(lettre) || (lettre == 'é')) {  // Support des caractères spéciaux
                        lettre = tolower(lettre);
                        // Ignorer la lettre 'R' lors du redémarrage
                        if (lettresDevinees.find(lettre) == string::npos) {
                            lettresDevinees += lettre;
                            lettresDevinees += " ";

                            // Vérifie si la lettre est dans le mot secret
                            if (motSecret.find(lettre) != string::npos) {
                                for (size_t i = 0; i < motSecret.size(); ++i) {
                                    if (motSecret[i] == lettre) {
                                        motDevine[i] = lettre;
                                    }
                                }
                            }
                            else {
                                tentativesRestantes--;  // Réduit les tentatives si la lettre est incorrecte
                            }
                        }

                    }
                }
                // Gestion des touches R et Échap
                if (event.type == Event::KeyPressed) {
                    if (event.key.code == Keyboard::Escape) {
                        window.close();  // Quitter si Échap est pressé
                    }
                    else if (event.key.code == Keyboard::R) {
                        rejouer = true;  // Relancer une nouvelle partie si R est pressé
                        break;
                    }
                }
            }

            // Vérifier les conditions de fin de partie
            if (tentativesRestantes == 0 || motDevine == motSecret) {
                if (motDevine == motSecret) {
                    resultat.setString("Bravo ! Vous avez trouvé le mot : " + motSecret);
                }
                else {
                    resultat.setString("Perdu ! Le mot était : " + motSecret);
                }
            }
            else {
                prompt.setString("Devinez le mot : " + motDevine);
                tentatives.setString("Tentatives restantes : " + to_string(tentativesRestantes));

                string lettresFormatees = "Lettres utilisées : ";
                int ligneMax = 20;
                for (size_t i = 0; i < lettresDevinees.size(); ++i) {
                    lettresFormatees += lettresDevinees[i];
                    if ((i + 1) % ligneMax == 0) {
                        lettresFormatees += "\n                  ";
                    }
                }
                lettresUtilisees.setString(lettresFormatees);
            }

            // Dessiner les éléments
            window.clear(Color::White);
            window.draw(prompt);
            window.draw(tentatives);
            window.draw(lettresUtilisees);
            window.draw(resultat);
            window.display();
        }

        // Afficher le message de fin de jeu et les instructions pour rejouer
        if (tentativesRestantes == 0 || motDevine == motSecret) {
            Text messageFin("Appuyez sur R pour rejouer ou sur Échap pour quitter.", font, 20);
            messageFin.setFillColor(Color::Black);
            messageFin.setPosition(50, 250);

            while (window.isOpen()) {
                Event event;
                while (window.pollEvent(event)) {
                    if (event.type == Event::Closed) {
                        window.close();
                    }
                    else if (event.type == Event::KeyPressed) {
                        if (event.key.code == Keyboard::Escape) {
                            window.close();  // Quitter si Échap est pressé
                        }
                        else if (event.key.code == Keyboard::R) {
                            rejouer = true;  // Relancer une nouvelle partie si R est pressé
                            break;
                        }
                    }
                }

                if (rejouer) break;  // Sortir de la boucle d'affichage pour redémarrer une nouvelle partie

                window.clear(Color::White);
                window.draw(messageFin);
                window.display();
            }
        }
    }
}
