#ifndef MAZE
#define MAZE

#include <vector>
#include <SFML/Graphics.hpp>
using namespace std;

// x-y are the coordinates 
// dy-dx are the direction given 
//nx-ny are the neighbours new and next move 

//enum direction { dir_top = 0, dir_right, dir_bottom, dir_left };
//int dx[4] = { 0, 1, 0, -1 };
//int dy[4] = { -1, 0, 1, 0 };
//int opposite[4] = { dir_bottom, dir_left , dir_top , dir_right  };

struct cell
{
    bool walls[4];
    bool visited;       // For generation
    bool visitedSolve = false;   // For solving
};


class Maze
{
private:
    int width, height;
    int cellSize = 20;
    vector<vector <cell>> grid; // instead of grid  and creates a 2d grid cell  

    vector<pair<int, int>> directions = {{0, -1}, {1, 0}, {0, 1}, {-1, 0}};

    vector<vector<int>> maze;
    vector<vector<bool>> visited;
    vector<pair<int, int>> exploredPath; // full DFS exploration order


    void generateMazeIterative(int startX, int startY, sf::RenderWindow& window); // recursive backtracking
    bool solveDFS(int x, int y, int endX, int endY, vector<pair<int, int>>& path, sf::RenderWindow& window);
    bool isValid(int x, int y);


public:
    vector <pair <int, int>> path; // solution path we want 
    Maze(int w, int h); // for grid 

    // 1. Maze generation
    void generate(int startX, int startY, sf::RenderWindow& window);

    // 2. Maze solving
    void solve(sf::RenderWindow& window); // bool to return true or false to see if we found the path out or not 

    //// 3. Display functions (ASCII)
   // void displayMaze();// printing the maze walls 
   // void displayPath();// printing the path itself 

    //SFML
    void draw(sf::RenderWindow& window, int cellSize);

    bool canMove(int x, int y, int nx, int ny);

    const vector<vector<cell>>& getGrid() const { return grid; }



};

#endif // MAZE
