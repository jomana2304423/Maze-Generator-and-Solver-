# Maze Generator & Solver (SFML/ C++)

##  Project Description
This project is a C++ application that **generates and solves mazes** using the SFML graphics library for visualization.  

The program:
- Generates a maze of any size specified by the user using recursive backtracking .
- Solves the maze using a pathfinding algorithm using Depth-first search .
- Displays the maze and the solution path in a graphical window.

You can see the maze generation process and the final solved path rendered in real-time.

---
### How to run it :
1-Enter maze width and height in the console when prompted.

2-View the maze and solution in the SFML window.

3-Close the window to exit the application.

### Here's a video illustration :
https://github.com/user-attachments/assets/8a1e4406-b7e5-4fbd-89b9-ec18de69780d



### **Building with Visual Studio**
1. Install SFML 3.0 and extract it somewhere on your PC.
2. In Visual Studio:
   - Open your project.
   - Go to **Project Properties → VC++ Directories** and set:
     - **Include Directories** to SFML's `include` folder.
     - **Library Directories** to SFML's `lib` folder.
   - Go to **Linker → Input** and add the required `.lib` files (for example, `sfml-graphics.lib`, `sfml-window.lib`, `sfml-system.lib`).
   - Make sure you copy the SFML `.dll` files into your project’s output directory.
3. Build the project (Ctrl+Shift+B).
4. Run the application (F5).

### Why generating using  Recursive Backtracking?

- Produces perfect mazes (no loops, exactly one path between any two points).

- Simple to implement and visualize.

### How it works:

1-Start at a random cell.

2-Mark it as visited.

3-Randomly choose an unvisited neighbor, remove the wall between the two cells, and move to that neighbor.

4-Repeat until all cells are visited (using recursion or an explicit stack).


### Why solving using DFS?

- Simple to implement.

- Finds a valid path quickly.

- Works well for perfect mazes.

### How it works:

1-Start at the entrance cell.

2-Explore each direction recursively until you find the goal.

3-If you reach a dead end, backtrack until another path is found.

4-Keep track of visited cells to avoid infinite loops.
