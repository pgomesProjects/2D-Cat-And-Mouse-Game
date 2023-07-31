#include <conio.h>
#include <iostream>
using std::cout;
using std::endl;

//Headers
#include "Maze.h"
#include "Mouse.h"

//Function prototypes
void Update(Maze& currentMaze, Mouse& currentPlayer);
void PrintGameBoard(Maze& currentMaze);

int main() {

    Maze* newMaze = new Maze(20, 20, 2, 1);
    Mouse playerMouse;

	playerMouse.SetPosition(*newMaze, newMaze->GetEntrance());

	cout << "\nI printed a fucking array now love me. :] \n" << endl;

    Update(*newMaze, playerMouse);

	return 0;
}

void Update(Maze& currentMaze, Mouse& currentPlayer) {
    char key;

    PrintGameBoard(currentMaze);

    bool gameActive = true;

    while (gameActive) {
        // Wait for a key press without the need to press Enter
        key = _getch();

        // Clear the console screen
        system("cls");

        switch (key) {
        case 'w':
            currentPlayer.Move(currentMaze, -1, 0);
            break;
        case 'a':
            currentPlayer.Move(currentMaze, 0, -1);
            break;
        case 's':
            currentPlayer.Move(currentMaze, 1, 0);
            break;
        case 'd':
            currentPlayer.Move(currentMaze, 0, 1);
            break;
        case 'q':
            gameActive = false;
            break;
        }

        if(gameActive)
            PrintGameBoard(currentMaze);
    }
}

void PrintGameBoard(Maze& currentMaze) {
    currentMaze.Print();
    cout << "\nPress WASD to move. Press Q to quit the game." << endl;
}
