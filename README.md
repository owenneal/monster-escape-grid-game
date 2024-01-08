# monster-escape-grid-game
Implemented a grid-based game using C++ for the "Outlast the Baddies & Avoid the Abyss" project as part of the CS 211 course at UIC. The project involved designing a grid structure utilizing a template class Grid<T> for dynamic memory allocation and management. The grid represents a game board where elements such as heroes, monsters, bats, abysses, walls, and an escape ladder are strategically placed.

Utilized object-oriented programming principles to create an abstract base class BoardCell and derived classes (Hero, Monster, Bat, Abyss, Wall, Nothing, and EscapeLadder) to represent various entities on the game board. These classes encapsulate functionality such as displaying characters, handling movements, and determining the type of each board cell.

The game involves the player controlling a hero on the grid, making strategic moves to outlast monsters and avoid falling into abysses. The program supports dynamic board sizes, random placement of obstacles, and user input for controlling the hero's movements.

Implemented essential features including grid initialization, player input handling, and dynamic memory management for grid elements. Utilized concepts such as polymorphism, inheritance, and encapsulation to create a modular and extensible design.

Successfully incorporated a random number generator to generate diverse game scenarios, providing a challenging and dynamic gaming experience.