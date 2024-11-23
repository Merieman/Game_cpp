#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "SnakeGame.h"
#include "BatailleNavale.h"
#include "DevinerNombre.h"
#include "DevinerMot.h"
#include "PierrePapierCiseaux.h"
#include "TicTacToe.h"
#include "Pendu.h"

int main() {
    RenderWindow menuWindow(VideoMode(800, 600), "Menu des Jeux");

    Menu menu;
    while (menuWindow.isOpen()) {

        int choix = menu.afficher(menuWindow);
        switch (choix) {
        case 1: {
            SnakeGame snakeGame;
            RenderWindow snakeWindow(VideoMode(800, 600), "Snake");
            snakeGame.lancer(snakeWindow);
            break;
        }
        case 2: {
            string joueur1 = "Joueur 1";
            string joueur2 = "Joueur 2";
            BatailleNavale bataille(joueur1, joueur2);
            RenderWindow batailleWindow(VideoMode(800, 600), "Bataille Navale");
            bataille.lancer(batailleWindow);
            break;
        }
        case 3: {
            DevinerNombre devinerNombre;
            RenderWindow devinerWindow(VideoMode(600, 400), "Deviner le nombre");
            devinerNombre.lancer(devinerWindow);
            break;
        }
        case 4: {
            DevinerMot devinerMot;
            RenderWindow devinerWindow(VideoMode(600, 400), "Deviner le mot");
            devinerMot.lancer(devinerWindow);
            break;
        }
        case 5: {
            PierrePapierCiseaux ppc;
            RenderWindow ppcWindow(VideoMode(600, 400), "Pierre-Papier-Ciseaux");
            ppc.lancer(ppcWindow);
            break;
        }
        case 6: {
            TicTacToe ticTacToe;
            RenderWindow tttWindow(VideoMode(600, 600), "Tic Tac Toe");
            ticTacToe.lancer(tttWindow);
            break;
        }
        case 7: {
            Pendu pendu;
            RenderWindow penduWindow(VideoMode(800, 600), "Jeu de Pendu");
            pendu.lancer(penduWindow);
            break;
        }
        default:
            cerr << "Choix non valide ou fermeture du menu." << endl;
            break;
        }
    }

    return 0;
}
