**1. Introduction**
This document provides an overview of the implementation of a Tetris game using C++ and the SFML (Simple and Fast Multimedia Library) framework. Tetris is a classic tile-matching puzzle game where players manipulate pieces to fit them into rows, clearing rows as they complete them. This project implements core Tetris mechanics, including piece spawning, movement, rotation, and line clearing, as well as a basic scoring system.
________________________________________
**2. Project Overview**
The Tetris game is implemented using:
•	Language: C++
•	Library: SFML for rendering graphics and handling input
•	Grid: A 2D array to manage the game state
•	Piece Logic: Structs for handling individual Tetris pieces
Project Goals:
•	Implement a fully playable Tetris game.
•	Render the game grid and pieces using SFML.
•	Handle game logic like piece collisions, rotations, and line clearing.
•	Include a scoring system and game over conditions.
________________________________________
**3. Key Features**
•	Dynamic Piece Movement: Pieces can move left, right, and down, as well as rotate.
•	Line Clearing: Complete rows are cleared, and the rows above them drop.
•	Collision Detection: Prevents pieces from overlapping or moving out of bounds.
•	Scoring System: Players score points for clearing rows.
•	Game Over Condition: The game ends if pieces reach the top of the grid.
•	Grid Rendering: Visual representation of the playfield and pieces.
________________________________________
**4. Code Structure**
Main Components
1.	Piece Handling: 
o	PIECE_TYPE: Enum for different Tetris shapes (e.g., I, O, T, L).
o	CreatePiece(): Function to generate a new piece of a given type.
2.	Grid and Colliders: 
o	grid: 2D array used for rendering the playfield.
o	colliders: 2D array that tracks locked pieces.
3.	Game Logic: 
o	Movement, rotation, collision detection, and line clearing logic.
4.	Rendering: 
o	SFML sf::Sprite objects used to draw pieces and grid elements.
________________________________________
**5. Explanation of Key Components**
Piece Movement and Rotation
Each piece is defined by four coordinates (tiles) that can move or rotate:
struct Piece {
    Point a, b, c, d; // Four tiles of the piece
};
•	Movement: The piece coordinates are updated based on player input or timer.
•	Rotation: Rotation is handled by transforming the piece's tiles around a pivot point.
Grid and Collision Detection
•	colliders: Tracks locked tiles in the playfield. A value of 2 indicates a locked block.
•	Collision detection checks if the new position of the piece overlaps with existing locked blocks or boundaries.
Line Clearing
When a row is completely filled:
1.	The row is cleared by shifting rows above it down.
2.	The score counter is incremented.
Game Over Condition
If any tile in the topmost row is filled, the game ends:
for (size_t i = 0; i < 12; i++) {
    if (colliders[0][i] == 2) {
        gameState = GAMEOVER;
    }
}
________________________________________
**6. How the Game Works**
Initialization
1.	The game initializes a grid and creates the first Tetris piece.
2.	The rendering window is opened using SFML.
Game Loop
1.	Input Handling: 
o	Player input (left, right, rotate) is processed.
2.	Piece Movement: 
o	Pieces move downward based on a timer.
o	Collisions are checked, and pieces lock in place if they reach the bottom or another piece.
3.	Line Clearing: 
o	Full rows are cleared, and the remaining blocks fall down.
4.	Rendering: 
o	The current state of the grid and the active piece are drawn to the screen.
End of Game
•	When the game over condition is met, the game stops, and a "Game Over" message is displayed.
________________________________________
**7. Conclusion**
This project implements a basic but functional version of Tetris using C++ and SFML. It demonstrates essential game development concepts such as grid-based logic, collision detection, and rendering with a graphical library. With further enhancements, this project could evolve into a polished and engaging game experience.
________________________________________
**8. Images**
Main Menu:
![image](https://github.com/user-attachments/assets/4053c4c1-6646-427c-9cb7-cc482b692d99)


Game Scene:
![image](https://github.com/user-attachments/assets/4349a7c2-594c-4287-bc8f-1be9bca769ba)

Game Scene:
![image](https://github.com/user-attachments/assets/90826ec8-8254-4b5e-bed8-16cfe7b2b41c)

 
