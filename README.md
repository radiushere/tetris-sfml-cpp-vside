**1. Introduction** <br>
This document provides an overview of the implementation of a Tetris game using C++ and the SFML (Simple and Fast Multimedia Library) framework. Tetris is a classic tile-matching puzzle game where players manipulate pieces to fit them into rows, clearing rows as they complete them. This project implements core Tetris mechanics, including piece spawning, movement, rotation, and line clearing, as well as a basic scoring system.
________________________________________
**2. Project Overview** <br>
The Tetris game is implemented using: <br>
•	Language: C++ <br>
•	Library: SFML for rendering graphics and handling input<br>
•	Grid: A 2D array to manage the game state<br>
•	Piece Logic: Structs for handling individual Tetris pieces<br>
Project Goals:<br>
•	Implement a fully playable Tetris game. <br>
•	Render the game grid and pieces using SFML.<br>
•	Handle game logic like piece collisions, rotations, and line clearing.<br>
•	Include a scoring system and game over conditions.<br>
________________________________________
**3. Key Features** <br>
•	Dynamic Piece Movement: Pieces can move left, right, and down, as well as rotate. <br>
•	Line Clearing: Complete rows are cleared, and the rows above them drop. <br>
•	Collision Detection: Prevents pieces from overlapping or moving out of bounds. <br>
•	Scoring System: Players score points for clearing rows. <br>
•	Game Over Condition: The game ends if pieces reach the top of the grid. <br>
•	Grid Rendering: Visual representation of the playfield and pieces. <br>
________________________________________
**4. Code Structure** <br>
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
**5. Explanation of Key Components** <br>
Piece Movement and Rotation <br>
Each piece is defined by four coordinates (tiles) that can move or rotate: <br>
struct Piece { <br>
    Point a, b, c, d; // Four tiles of the piece <br>
}; <br>
•	Movement: The piece coordinates are updated based on player input or timer. <br>
•	Rotation: Rotation is handled by transforming the piece's tiles around a pivot point. <br>
Grid and Collision Detection <br>
•	colliders: Tracks locked tiles in the playfield. A value of 2 indicates a locked block. <br>
•	Collision detection checks if the new position of the piece overlaps with existing locked blocks or boundaries. <br>
Line Clearing <br>
When a row is completely filled: <br>
1.	The row is cleared by shifting rows above it down. <br>
2.	The score counter is incremented. <br>
Game Over Condition <br>
If any tile in the topmost row is filled, the game ends: <br>
for (size_t i = 0; i < 12; i++) { <br>
    if (colliders[0][i] == 2) { <br>
        gameState = GAMEOVER; <br>
    } <br>
} <br>
________________________________________
**6. How the Game Works** <br>
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
**7. Conclusion** <br>
This project implements a basic but functional version of Tetris using C++ and SFML. It demonstrates essential game development concepts such as grid-based logic, collision detection, and rendering with a graphical library. With further enhancements, this project could evolve into a polished and engaging game experience.
________________________________________
**8. Images**
<br>
![image](https://github.com/user-attachments/assets/4053c4c1-6646-427c-9cb7-cc482b692d99)
<br>
![image](https://github.com/user-attachments/assets/4349a7c2-594c-4287-bc8f-1be9bca769ba)
<br>
![image](https://github.com/user-attachments/assets/a1b00811-e62e-4c99-a0be-509a8a3ee738)


 
