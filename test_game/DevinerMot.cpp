#include "DevinerMot.h"
#include <iostream>

DevinerMot::DevinerMot() {
    srand(static_cast<unsigned>(time(0)));  // Initialiser le générateur aléatoire
}

string DevinerMot::ajusterTexte(const string& texte, unsigned int largeurMax, Font& font, unsigned int tailleTexte) {
    Text test(texte, font, tailleTexte);
    string ajustedText = "";
    string ligne = "";
    for (size_t i = 0; i < texte.size(); i++) {
        ligne += texte[i];
        test.setString(ligne);
        if (test.getLocalBounds().width > largeurMax) {
            ajustedText += ligne + "\n";
            ligne = "";
        }
    }
    ajustedText += ligne;
    return ajustedText;
}

void DevinerMot::lancer(RenderWindow& window) {
    Font font;
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Erreur : Impossible de charger la police 'arial.ttf'." << endl;
        return;
    }

    vector<string> langages = { "c++", "python", "java", "javascript", "ruby", "swift", "kotlin", "golang", "php", "rust", "dart"};

    bool rejouer = true;

    while (rejouer && window.isOpen()) {
        string motSecret = langages[rand() % langages.size()];
        Text prompt("Devinez le langage de programmation !", font, 20);
        prompt.setPosition(50, 50);
        prompt.setFillColor(Color::Black);

        Text saisieUtilisateur("", font, 20);
        saisieUtilisateur.setPosition(50, 100);
        saisieUtilisateur.setFillColor(Color::Blue);

        Text resultat("", font, 20);
        resultat.setPosition(50, 150);
        resultat.setFillColor(Color::Red);

        string motUtilisateur = "";
        int tentatives = 5;
        bool trouve = false;

        while (window.isOpen() && tentatives > 0 && !trouve) {
            Event event;
            while (window.pollEvent(event)) {
                if (event.type == Event::Closed) {
                    window.close();
                }
                else if (event.type == Event::TextEntered) {
                    char lettre = static_cast<char>(event.text.unicode);
                    if (lettre == '\b' && !motUtilisateur.empty()) {
                        motUtilisateur.pop_back();
                    }
                    else if (isalnum(lettre) && motUtilisateur.size() < 20) {
                        motUtilisateur += lettre;
                    }
                    else if (lettre == '\r') {
                        if (motUtilisateur == motSecret) {
                            string message = "Felicitations, vous avez trouve le langage : " + motSecret + " !";
                            resultat.setString(ajusterTexte(message, 500, font, 20));
                            resultat.setFillColor(Color::Green);
                            trouve = true;
                        }
                        else {
                            tentatives--;
                            string message = "Mauvais mot ! Tentatives restantes: " + to_string(tentatives);
                            resultat.setString(ajusterTexte(message, 500, font, 20));
                            motUtilisateur = "";
                        }
                    }
                }
            }

            saisieUtilisateur.setString("Votre mot: " + motUtilisateur);

            window.clear(Color::White);
            window.draw(prompt);
            window.draw(saisieUtilisateur);
            window.draw(resultat);
            window.display();
        }

        if (!trouve) {
            string message = "Vous avez perdu ! Le langage etait : " + motSecret;
            resultat.setString(ajusterTexte(message, 500, font, 20));
            resultat.setFillColor(Color::Red);
        }

        Text rejouerTexte("Appuyez sur 'R' pour rejouer ou 'Echap' pour quitter.", font, 18);
        rejouerTexte.setPosition(50, 300);
        rejouerTexte.setFillColor(Color::Black);

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
                        window.close();  // Fermer la fenêtre si Échap est pressé
                        rejouer = false;  // Terminer la boucle principale
                        return;
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
