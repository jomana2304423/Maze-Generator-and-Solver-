#include <SFML/Graphics.hpp>
#include "Maze.h"
#include <iostream>
#include <vector>
#include <random>
#include <algorithm>


using namespace std;

Maze::Maze(int w, int h) : width(w), height(h) // sets the width and height to the variable value of w and h in the argument 
{
    // Creating a 2d grid cell obj 
    grid.resize(height, vector<cell>(width)); // height is the rows (vertical size) how far can you go down "y"
    //and width is the column ( horizontal size) how far can u go right "x"

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            grid[y][x].visited = false;

            for (int i = 0; i < 4; i++)
                grid[y][x].walls[i] = true; // true to start the maze with solid walls 
        }
    }
}

void Maze::generate(int startX, int startY, sf::RenderWindow& window)
{
    generateMazeIterative(startX, startY, window);
}

    void Maze::generateMazeIterative(int startX, int startY, sf::RenderWindow & window)
    {
        vector<pair<int, int>> stack;
        stack.push_back({ startX, startY });
        grid[startY][startX].visited = true;

        while (!stack.empty())
        {
            auto [x, y] = stack.back();

            // Find unvisited neighbors
            vector<int> dirs = { 0, 1, 2, 3 };
            shuffle(dirs.begin(), dirs.end(), mt19937(random_device{}()));

            bool moved = false;
            for (int dir : dirs)
            {
                int nx = x, ny = y;
                if (dir == 0) ny--;
                else if (dir == 1) nx++;
                else if (dir == 2) ny++;
                else if (dir == 3) nx--;

                if (nx >= 0 && nx < width && ny >= 0 && ny < height && !grid[ny][nx].visited)
                {
                    grid[y][x].walls[dir] = false;
                    grid[ny][nx].walls[(dir + 2) % 4] = false;
                    grid[ny][nx].visited = true;
                    stack.push_back({ nx, ny });
                    moved = true;

                    // Animate
                    window.clear(sf::Color::White);
                    draw(window, cellSize);
                    window.display();
                    sf::sleep(sf::milliseconds(20));
                    break;
                }
            }

            if (!moved) stack.pop_back();
        }
    }

    bool Maze::isValid(int x, int y)
    {
        return x >= 0 && x < width && y >= 0 && y < height;
    }



    void Maze::solve(sf::RenderWindow& window) {
        visited.assign(height, vector<bool>(width, false));
        path.clear();
        exploredPath.clear();

        vector<pair<int, int>> solutionPath;
        if (solveDFS(0, 0, width - 1, height - 1, solutionPath, window)) {
            path = solutionPath;
            reverse(path.begin(), path.end());
            cout << "Solution found in " << path.size() << " steps.\n";
        }
        else {
            cout << "No path found.\n";
        }
    }


    bool Maze::solveDFS(int x, int y, int endX, int endY,
        vector<pair<int, int>>& solutionPath,
        sf::RenderWindow& window)
    {
        visited[y][x] = true;
        exploredPath.push_back({ x, y }); // track exploration

        // Animate exploration
        window.clear(sf::Color::White);
        draw(window, cellSize);
        window.display();
        if (width * height > 225)
            sf::sleep(sf::milliseconds(5));
        else
            sf::sleep(sf::milliseconds(20));

        if (x == endX && y == endY) {
            solutionPath.push_back({ x, y });
            return true;
        }

        int dx[4] = { 1, 0, -1, 0 };
        int dy[4] = { 0, 1, 0, -1 };

        for (int i = 0; i < 4; i++) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (nx >= 0 && nx < width && ny >= 0 && ny < height &&
                !visited[ny][nx] && canMove(x, y, nx, ny))
            {
                if (solveDFS(nx, ny, endX, endY, solutionPath, window)) {
                    solutionPath.insert(solutionPath.begin(), { x, y });
                    return true;
                }

            }
        }

        return false;
    }



//SFML

void Maze::draw(sf::RenderWindow& window, int cellSize)
{
    sf::Color wallColor = sf::Color::Black;
    float lineThickness = 1.5f; // thin clean lines

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            float px = static_cast<float>(x * cellSize);
            float py = static_cast<float>(y * cellSize);

            // Background for cell
            sf::RectangleShape cellBg(sf::Vector2f(cellSize, cellSize));
            cellBg.setPosition(sf::Vector2f(px, py));

            cellBg.setFillColor(sf::Color(240, 240, 255)); // light color
            window.draw(cellBg);

            // Top wall
            if (grid[y][x].walls[0])
            {
                sf::RectangleShape wall(sf::Vector2f(cellSize, lineThickness));
                wall.setPosition(sf::Vector2f(px, py)); 

                wall.setFillColor(wallColor);
                window.draw(wall);
            }

            // Right wall
            if (grid[y][x].walls[1])
            {
                sf::RectangleShape wall(sf::Vector2f(lineThickness, cellSize));
                wall.setPosition(sf::Vector2f(px + cellSize - lineThickness, py));
                wall.setFillColor(wallColor);
                window.draw(wall);
            }

            // Bottom wall
            if (grid[y][x].walls[2])
            {
                sf::RectangleShape wall(sf::Vector2f(cellSize, lineThickness));
                wall.setPosition(sf::Vector2f(px, py + cellSize - lineThickness));

                wall.setFillColor(wallColor);
                window.draw(wall);
            }

            // Left wall
            if (grid[y][x].walls[3])
            {
                sf::RectangleShape wall(sf::Vector2f(lineThickness, cellSize));
                wall.setPosition(sf::Vector2f(px, py));

                wall.setFillColor(wallColor);
                window.draw(wall);
            }
        }
    }

    
 // Draw purple exploration path
    for (auto& p : exploredPath) {
        sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));
        rect.setPosition(sf::Vector2f(  p.first * static_cast<float>(cellSize),  p.second * static_cast<float>(cellSize) ));

        rect.setFillColor(sf::Color(200, 100, 255, 120)); // transparent purple
        window.draw(rect);
    }

    // Draw final solution path (different color if you want)
    for (auto& p : path) {
        sf::RectangleShape rect(sf::Vector2f(cellSize, cellSize));
        rect.setPosition(sf::Vector2f(  p.first * static_cast<float>(cellSize), p.second * static_cast<float>(cellSize) ));

        rect.setFillColor(sf::Color(200, 200, 255, 150)); // transparent blue
        window.draw(rect);
    }

}

bool Maze:: canMove(int x, int y, int nx, int ny) {
    if (nx < 0 || nx >= width || ny < 0 || ny >= height) return false;

    // Determine direction
    if (nx == x && ny == y - 1 && !grid[y][x].walls[0]) return true; // up
    if (nx == x + 1 && ny == y && !grid[y][x].walls[1]) return true; // right
    if (nx == x && ny == y + 1 && !grid[y][x].walls[2]) return true; // down
    if (nx == x - 1 && ny == y && !grid[y][x].walls[3]) return true; // left

    return false;
}

