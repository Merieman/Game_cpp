#include "SnakeGame.h"
#include <cstdlib>
#include <ctime>
#include <thread> // Pour this_thread::sleep_for
#include <chrono> // Pour chrono::milliseconds


SnakeGame::SnakeGame()
    : dir(STOP), x(WIDTH / 2), y(HEIGHT / 2), score(0), nTail(0), gameOver(false) {
    fruitX = rand() % WIDTH;
    fruitY = rand() % HEIGHT;
    srand(static_cast<unsigned>(time(0)));
}

void SnakeGame::deplacerSerpent() {

    // Déplacer la tête
    if (dir == LEFT) x--;
    if (dir == RIGHT) x++;
    if (dir == UP) y--;
    if (dir == DOWN) y++;

    // Gestion des bordures
    if (x >= WIDTH) x = 0; else if (x < 0) x = WIDTH - 1;
    if (y >= HEIGHT) y = 0; else if (y < 0) y = HEIGHT - 1;

    // Vérifier si le serpent se mord lui-même
    for (const auto& segment : tail) {
        if (x == segment.x && y == segment.y) {
            gameOver = true;
            return;
        }
    }

    // Gestion de la queue
    if (!tail.empty()) {
        tail.insert(tail.begin(), Vector2i(x, y));
        if (tail.size() > nTail) tail.pop_back();
    }

    // Vérifier la collision avec le fruit
    if (x == fruitX && y == fruitY) {
        score += 10;
        nTail++;
        fruitX = rand() % WIDTH;
        fruitY = rand() % HEIGHT;
    }
}

void SnakeGame::lancer(RenderWindow& window) {
    const int DELAY = 100; // Délai en millisecondes
    Font font;

    // Charger la police pour le score
    if (!font.loadFromFile("arial.ttf")) {
        cerr << "Erreur lors du chargement de la police." << endl;
        return;
    }

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();

            // Contrôles
            if (Keyboard::isKeyPressed(Keyboard::Q)) dir = LEFT;
            if (Keyboard::isKeyPressed(Keyboard::D)) dir = RIGHT;
            if (Keyboard::isKeyPressed(Keyboard::Z)) dir = UP;
            if (Keyboard::isKeyPressed(Keyboard::S)) dir = DOWN;

            // Fermer le jeu avec Échap
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                window.close(); // Fermer le jeu
            }

            // Redémarrer le jeu avec R
            if (event.type == Event::KeyPressed && event.key.code == Keyboard::R) {
                
                    // Réinitialiser les paramètres du jeu pour recommencer
                    gameOver = false;
                    score = 0;
                    nTail = 0;
                    x = WIDTH / 2;
                    y = HEIGHT / 2;
                    dir = STOP;
                    tail.clear();
                    fruitX = rand() % WIDTH;
                    fruitY = rand() % HEIGHT;
                
            }
        }

        if (gameOver) {
            window.clear(Color::Red);

            Text gameOverText("Game Over!", font, 50);
            gameOverText.setFillColor(Color::White);
            gameOverText.setPosition(100, 100);
            window.draw(gameOverText);

            window.display();
            sleep(seconds(3)); // Pause pour afficher le message
            return; // Quitter le jeu
        }

        deplacerSerpent();

        // Dessin du jeu
        window.clear(Color::Black);

        // Dessiner la queue
        for (auto& segment : tail) {
            RectangleShape snakeSegment(Vector2f(SIZE - 2, SIZE - 2));
            snakeSegment.setFillColor(Color::Green);
            snakeSegment.setPosition(segment.x * SIZE, segment.y * SIZE);
            window.draw(snakeSegment);
        }

        // Dessiner la tête
        RectangleShape snakeHead(Vector2f(SIZE - 2, SIZE - 2));
        snakeHead.setFillColor(Color::White);
        snakeHead.setPosition(x * SIZE, y * SIZE);
        window.draw(snakeHead);

        // Dessiner le fruit
        CircleShape fruit(SIZE / 2);
        fruit.setFillColor(Color::Red);
        fruit.setPosition(fruitX * SIZE, fruitY * SIZE);
        window.draw(fruit);

        // Dessiner le score
        Text scoreText("Score: " + to_string(score), font, 20);
        scoreText.setFillColor(Color::White);
        scoreText.setPosition(10, 10);
        window.draw(scoreText);

        window.display();

        // Ajouter un délai pour ralentir le jeu
        this_thread::sleep_for(chrono::milliseconds(DELAY));
    }
}


