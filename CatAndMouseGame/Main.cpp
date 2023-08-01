#include <conio.h>
#include <iostream>
using std::cout;
using std::endl;

//Headers
#include "Maze.h"
#include "Mouse.h"
#include "Cat.h"

//Function prototypes
void Update(Maze& currentMaze, Mouse& currentPlayer, Cat& currentCat);
void RefreshGameBoard(Maze& currentMaze);
void GameOverScreen();

int main() {

    Maze* newMaze = new Maze(20, 20, 2, 1);
    Mouse* playerMouse = new Mouse(1);
    Cat* enemyCat = new Cat(1, 0.25f);

    playerMouse->SetPosition(*newMaze, newMaze->GetEntrance());
    enemyCat->SetPosition(*newMaze, newMaze->GetEmptyPositionInMaze(playerMouse->GetPosition(), 10));

    Update(*newMaze, *playerMouse, *enemyCat);

	return 0;
}

void Update(Maze& currentMaze, Mouse& currentPlayer, Cat& currentCat) {
    char key;

    RefreshGameBoard(currentMaze);

    bool gameActive = true;
    bool gameOver = false;

    while (gameActive) {
        bool inputValid = false;

        // Wait for a key press without the need to press Enter
        key = _getch();

        switch (key) {
        case 'w':
            inputValid = currentPlayer.Move(currentMaze, -1, 0);
            break;
        case 'a':
            inputValid = currentPlayer.Move(currentMaze, 0, -1);
            break;
        case 's':
            inputValid = currentPlayer.Move(currentMaze, 1, 0);
            break;
        case 'd':
            inputValid = currentPlayer.Move(currentMaze, 0, 1);
            break;
        case 'q':
            gameActive = false;
            inputValid = true;
            break;
        }

        if (inputValid) {
            if (gameActive) {
                gameOver = currentCat.CheckForMovement(currentMaze);
            }

            if (gameOver) {
                GameOverScreen();
                break;
            }

            // Clear the console screen
            system("cls");
            RefreshGameBoard(currentMaze);
        }
    }
}

void RefreshGameBoard(Maze& currentMaze) {
    currentMaze.Print();
    cout << "\nPress WASD to move. Press Q to quit the game." << endl;
}

void GameOverScreen() {
    char key;
    system("cls");

    string gameOverText [] = 
    {"   ______                                    ____                      ",
     "  / ____/  ____ _   ____ ___   ___          / __ \\ _   __  ___    _____",
     " / / __   / __ `/  / __ `__ \\ / _ \\        / / / /| | / / / _ \\  / ___/",
     "/ /_/ /  / /_/ /  / / / / / //  __/       / /_/ / | |/ / /  __/ / /    ",
     "\\____/   \\__,_/  /_/ /_/ /_/ \\___/        \\____/  |___/  \\___/ /_/     ",
    "                                                                       "};

    for (const auto& line : gameOverText)
        cout << line << endl;

    cout << "Press any key to quit the game." << endl;
    key = _getch();
}