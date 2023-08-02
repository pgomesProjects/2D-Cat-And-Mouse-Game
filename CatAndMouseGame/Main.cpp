/*
*   2D Cat n' Mouse Maze Game C++ Sample
*   Author: Peter Gomes
*   Date: 8/2/23
*/

#include <conio.h>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::pair;

//Headers
#include "Maze.h"
#include "Mouse.h"
#include "Cat.h"
#include "Food.h"

//Function prototypes
void StartScreen();
void GameLoop(Maze& currentMaze, Mouse& currentPlayer, Cat& currentCat);
void RefreshGameBoard(Maze& currentMaze, Cat& currentCat, int score);
void WinScreen();
void GameOverScreen();

//Constant game variables
const int MAX_FOOD_PIECES = 10;
const int MINIMUM_CAT_SPAWN_DISTANCE = 10;
const int MINIMUM_FOOD_SPAWN_DISTANCE = 10;
const int CAT_MOVEMENT_COOLDOWN = 2;

int main() {

    //Initialize the maze, player, and cat with some values
    Maze* newMaze = new Maze(20, 20, 2, 1);
    Mouse* playerMouse = new Mouse(1, 0.05f);
    Cat* enemyCat = new Cat(1, 0.25f);

    //Add food to the maze
    for (int i = 0; i < MAX_FOOD_PIECES; i++) {
        pair<int, int> foodPos = newMaze->GetEmptyPositionInMaze(playerMouse->GetPosition(), MINIMUM_FOOD_SPAWN_DISTANCE);
        Food newFood(foodPos.first, foodPos.second);
        newFood.PlaceFood(*newMaze);
    }

    //Set the positions of the player and the
    playerMouse->SetPosition(*newMaze, newMaze->GetEntrance());
    enemyCat->SetPosition(*newMaze, newMaze->GetEmptyPositionInMaze(playerMouse->GetPosition(), MINIMUM_CAT_SPAWN_DISTANCE));

    //Display the starting screen
    StartScreen();

    //Enter the game loop
    GameLoop(*newMaze, *playerMouse, *enemyCat);

	return 0;
}

/// <summary>
/// Performs the game loop logic for when the game is active.
/// </summary>
/// <param name="currentMaze">The data for the game's maze.</param>
/// <param name="currentPlayer">The data for the player object.</param>
/// <param name="currentCat">The data for the cat object.</param>
void GameLoop(Maze& currentMaze, Mouse& currentPlayer, Cat& currentCat) {

    //Char to keep track of player input
    char key;

    //Game state bool variables
    bool gameActive = true;
    bool gameOver = false;
    bool gameWin = false;

    int movementCooldown = 0;

    //Player score
    int score = 0;

    //Display game board on start
    RefreshGameBoard(currentMaze, currentCat, score);

    //Game loop
    while (gameActive) {

        bool inputValid = false;

        // Wait for a key press without the need to press Enter
        key = _getch();

        //Try to move the player if they press the right button. If they press 'Q', quit the game immediately
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

        //If the player has successfully performed movement
        if (inputValid) {

            if (gameActive) {

                //If the player found food, add to the player's score
                if (currentPlayer.CheckForFood(currentMaze))
                    score++;

                //If the cooldown for the cat to move has been reached, move the cat
                if (movementCooldown >= CAT_MOVEMENT_COOLDOWN - 1) {
                    movementCooldown = 0;
                    //Move the cat and check to see if they caught the player
                    gameOver = currentCat.CheckForMovement(currentMaze);
                }
                else {
                    movementCooldown++;
                }

                //Check to see if the player won the game by collecting all of the food
                gameWin = score >= MAX_FOOD_PIECES;
            }

            //If the player was caught, produce a game over state
            if (gameOver) {
                GameOverScreen();
                break;
            }

            //If the player collected all food, produce a game win state
            if (gameWin) {
                WinScreen();
                break;
            }

            RefreshGameBoard(currentMaze, currentCat, score);
        }
    }
}

/// <summary>
/// Displays the game board and appropriate information.
/// </summary>
/// <param name="currentMaze">The data for the maze to display the maze on the console.</param>
/// <param name="currentCat">The data for the cat to display the status of the cat's behavior.</param>
/// <param name="score">The player's score to show their progress.</param>
void RefreshGameBoard(Maze& currentMaze, Cat& currentCat, int score) {
    system("cls");  //Refresh console

    //Print the maze data
    currentMaze.Print();

    //Display information
    cout << "\nScore: " << score << " / " << MAX_FOOD_PIECES << endl;
    cout << "\Cat Status: " << (currentCat.CanSmellPlayer() ? "Tracking Scent" : "Wandering") << endl;
    cout << "\nPress WASD to move. Press Q to quit the game." << endl;
}

/// <summary>
/// Displays a start screen when the program is run which explains the game's rules.
/// </summary>
void StartScreen() {
    char key;

    string startText[] =
    {
        "   ______           __                  _            __  ___                             ",
        "  / ____/  ____ _  / /_          ____  ( )          /  |/  /  ____   __  __   _____  ___ ",
        " / /      / __ `/ / __/         / __ \ |/          / /|_/ /  / __ \\ / / / /  / ___/ / _ \\",
        "/ /___   / /_/ / / /_          / / / /            / /  / /  / /_/ // /_/ /  (__  ) /  __/",
        "\\____/   \\__,_/  \\__/         /_/ /_/            /_/  /_/   \\____/ \\__,_/  /____/  \\___/ ",
        "                                                                                         ",
        "You are a mouse in a randomly generated maze, trying to collect enough food to survive the night. However, a cat patrols the lanes to thwart you of your plans.",
        "Whenever you move a couple of spaces in the maze, the cat moves 1 to 2 spaces in the maze as well.",
        "Whenever you roam around the maze, you leave an invisible scent trail in which the cat can pick up and follow, so be careful.",
        "\n===KEY===",
        "# - Wall",
        ". - Empty Space",
        "M - You (the player)",
        "C - The Cat",
        "F - Food (collectable)"
    };

    for (const auto& line : startText)
        cout << line << endl;

    cout << "\nPress any key to start." << endl;
    key = _getch();
    system("cls");
}

/// <summary>
/// Displays a game win screen when the game win state is met.
/// </summary>
void WinScreen() {
    char key;
    system("cls");

    string gameWinText[] =
    {"__  __                       _       __    _             __",
     "\\ \\/ /  ____   __  __       | |     / /   (_)   ____    / /",
     " \\  /  / __ \\ / / / /       | | /| / /   / /   / __ \\  / / ",
     " / /  / /_/ // /_/ /        | |/ |/ /   / /   / / / / /_/  ",
     "/_/   \\____/ \\__,_/         |__/|__/   /_/   /_/ /_/ (_)   ",
     "                                                           "
    };

    for (const auto& line : gameWinText)
        cout << line << endl;

    cout << "Press any key to quit the game." << endl;
    key = _getch();
}

/// <summary>
/// Displays a game over screen when the game lose state is met.
/// </summary>
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