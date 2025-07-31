# Pac-Man Clone in C with raylib

This is a classic Pac-Man game clone created as a university project for a first-semester programming course. The game is written entirely in C and uses the wonderful `raylib` library for graphics, audio, and input handling.

## 🌟 Features

* **Classic Gameplay:** Navigate the maze, eat all the pellets, and avoid the ghosts!
* **Ghost Enemies:** Face off against Blinky, Pinky, Inky, and Clyde, each with their own unique (though simple) AI.
* **Power Pellets:** Turn the tables on the ghosts by eating power pellets and chase them down for extra points.
* **Scoring System:** Rack up points for eating pellets, power pellets, and ghosts. Your high score is saved for future sessions.
* **Sound Effects & Music:** Features classic sound effects for munching, death, and more, plus background music to keep the tension high.
* **Multiple Screens:** Includes a start menu, game over screen, and a victory screen.
* **Map Loading:** The game level is loaded from an external `.txt` file, allowing for easy map creation and modification.

## 🎮 How to Play

The objective is to clear the maze of all pellets without getting caught by the ghosts.

* **Move Pac-Man:** Use the **Arrow Keys** (`UP`, `DOWN`, `LEFT`, `RIGHT`) to navigate.
* **Start Game:** Press **Start** on the main menu to begin.

## 🛠️ Getting Started

To compile and run this project on your local machine, you'll need a C compiler (like GCC) and the `make` utility.
The compiled file is in the repository, too.

### Prerequisites

* A C compiler (e.g., GCC/MinGW for Windows)
* `make` build automation tool

### Compilation

The project includes a `makefile` that simplifies the compilation process.

1.  **Clone the repository** or download the source files to your computer.

2.  **Open a terminal** or command prompt and navigate to the root directory of the project.

3.  **Run the `make` command:**
    ```sh
    make
    ```
    This command will compile the source code and create an executable file named `PACMAN.exe`.

### Running the Game

Once the compilation is complete, you can run the game by executing the generated file:

* **On Windows:**
    ```sh
    PACMAN.exe
    ```
* **On Linux/macOS** (if compiled on that platform):
    ```sh
    ./pacman
    ```

## 📂 Project Structure


.
├── include/          # Header files for libraries (raylib)
├── lib/              # Static libraries (raylib)
├── resources/        # Game assets
│   ├── Audio/        # Sound effects and music
│   ├── maps/         # Level map files
│   └── sprites/      # Character and UI sprites
├── LICENSE           # Project license
├── makefile          # Build script for the project
├── PACMAN.c          # Main game source code
├── PACMAN.exe        # Compiled game executable (for Windows)
└── README.md         # This file


## 📜 License

This project is licensed under the MIT License - see the [LICENSE](LICENSE) file for details.

---

*This README was generated with assistance from Gemini.*
