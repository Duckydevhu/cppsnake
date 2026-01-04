#include <SFML/Graphics.hpp>
#include <vector>
#include <optional>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// --- BEÁLLÍTÁSOK ---
const int TILE_SIZE = 25;
const int WIDTH = 32;
const int HEIGHT = 24;

enum Direction { STOP = 0, LEFT, RIGHT, UP, DOWN };

struct Snake {
    vector<sf::Vector2i> body;
    Direction dir;

    Snake() {
        body.push_back({ 10, 10 });
        body.push_back({ 9, 10 });
        body.push_back({ 8, 10 });
        dir = STOP;
    }

    void Move() {
        if (dir == STOP) return;

        // Test követi a fejet
        for (int i = body.size() - 1; i > 0; i--) {
            body[i] = body[i - 1];
        }

        // Fej mozgatása
        if (dir == LEFT)  body[0].x -= 1;
        if (dir == RIGHT) body[0].x += 1;
        if (dir == UP)    body[0].y -= 1;
        if (dir == DOWN)  body[0].y += 1;
    }

    void Grow() {
        body.push_back(body.back());
    }
};

int main() {
    srand(static_cast<unsigned>(time(0)));

    sf::RenderWindow window(sf::VideoMode({ WIDTH * TILE_SIZE, HEIGHT * TILE_SIZE }), "Snake Game | Score: 0");
    window.setFramerateLimit(60);

    Snake snake;
    sf::Vector2i fruit = { rand() % WIDTH, rand() % HEIGHT };

    sf::Clock clock;
    float timer = 0;
    float delay = 0.1f;

    int score = 0;
    bool isGameOver = false;

    while (window.isOpen()) {
        float time = clock.restart().asSeconds();
        timer += time;

        // --- ESEMÉNYEK ---
        while (const optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) window.close();
        }

        if (!isGameOver) {
            // MÓDOSÍTÁS: Kurzorbillentyûk (Nyilak) használata
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left) && snake.dir != RIGHT) snake.dir = LEFT;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right) && snake.dir != LEFT)  snake.dir = RIGHT;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up) && snake.dir != DOWN)    snake.dir = UP;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down) && snake.dir != UP)    snake.dir = DOWN;
        }
        else {
            // MÓDOSÍTÁS: Enter-re indítsa újra
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape)) window.close();
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Enter)) {
                isGameOver = false;
                score = 0;
                delay = 0.1f;
                snake = Snake();
                window.setTitle("Snake Game | Score: 0");
            }
        }

        // --- LOGIKA ---
        if (!isGameOver && timer > delay) {
            timer = 0;
            snake.Move();

            // 1. Ütközés a fallal
            if (snake.body[0].x >= WIDTH || snake.body[0].x < 0 ||
                snake.body[0].y >= HEIGHT || snake.body[0].y < 0) {
                isGameOver = true;
                window.setTitle("GAME OVER | Final Score: " + to_string(score) + " | Press ENTER");
            }

            // 2. Ütközés önmagával
            for (size_t i = 1; i < snake.body.size(); i++) {
                if (snake.body[0] == snake.body[i]) {
                    isGameOver = true;
                    window.setTitle("GAME OVER | Final Score: " + to_string(score) + " | Press ENTER");
                }
            }

            // 3. Evés
            if (snake.body[0].x == fruit.x && snake.body[0].y == fruit.y) {
                snake.Grow();
                score++;
                fruit = { rand() % WIDTH, rand() % HEIGHT };

                window.setTitle("Snake Game | Score: " + to_string(score));

                // Gyorsulás
                if (score % 10 == 0) {
                    if (delay > 0.03f) delay -= 0.01f;
                }
            }
        }

        // --- RAJZOLÁS ---
        window.clear();

        sf::RectangleShape block({ (float)TILE_SIZE - 1, (float)TILE_SIZE - 1 });

        if (isGameOver) block.setFillColor(sf::Color::Color(100, 100, 100));
        else block.setFillColor(sf::Color::Green);

        for (auto& part : snake.body) {
            block.setPosition({ (float)part.x * TILE_SIZE, (float)part.y * TILE_SIZE });
            window.draw(block);
        }

        if (!isGameOver) {
            sf::RectangleShape fruitShape({ (float)TILE_SIZE, (float)TILE_SIZE });
            fruitShape.setFillColor(sf::Color::Red);
            fruitShape.setPosition({ (float)fruit.x * TILE_SIZE, (float)fruit.y * TILE_SIZE });
            window.draw(fruitShape);
        }

        window.display();
    }

    return 0;
}