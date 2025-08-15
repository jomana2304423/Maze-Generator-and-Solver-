#include <SFML/Graphics.hpp>
#include <iostream>
#include "Maze.h"

using namespace std;

int main()
{
    int w, h;
    cout << "Enter maze width: ";
    cin >> w;
    cout << "Enter maze height: ";
    cin >> h;
    cout << endl;



    const int cellSize = 20;
    unsigned winW = static_cast<unsigned>(w * cellSize);
    unsigned winH = static_cast<unsigned>(h * cellSize);

    // Create a moving "player" circle
    sf::CircleShape player(cellSize / 2.0f - 2); // small circle inside cell
    player.setFillColor(sf::Color::Black);

    // Index in the path vector
    size_t playerIndex = 0;

    // Time tracking for movement speed
    sf::Clock clock;
    float moveDelay = 0.15f; // seconds between moves

    sf::RenderWindow window(sf::VideoMode(sf::Vector2u(winW, winH)), "Maze");


    Maze obj1(w, h);

    obj1.generate(0, 0, window);
    // cout << "Generated Maze:\n";
   //  obj1.displayMaze();

    cout << "Solving maze...\n";
    obj1.solve(window);
    //obj1.displayPath();


    // Reverse solution path so it goes start ? goal
    reverse(obj1.path.begin(), obj1.path.end());


    while (window.isOpen()) {
        while (const auto ev = window.pollEvent()) {
            if (ev->is<sf::Event::Closed>())
                window.close();
        }

        if (playerIndex < obj1.path.size()) {
            if (clock.getElapsedTime().asSeconds() > moveDelay) {
                player.setPosition(
                    sf::Vector2f(obj1.path[playerIndex].first * cellSize,
                        obj1.path[playerIndex].second * cellSize)
                );
                playerIndex++;
                clock.restart();
            }
        }

        window.clear(sf::Color::White);
        obj1.draw(window, cellSize);
        window.draw(player);
        window.display();

    }
}
