/*
*   2D Cat n' Mouse Maze Game C++ Sample
*   Date: 3/17/26
*/

#include <conio.h>
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::pair;

//Headers
#include "AudioManager.h"
#include "console.h"
#include "Maze.h"
#include "Mouse.h"
#include "Cat.h"
#include "Food.h"

//Function prototypes
void PreloadSounds();
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

AudioManager audioManager;

const pair<int, int> MAZE_DIMENSIONS = {30, 35};

int main() {
    //Preload the audio for the game
    PreloadSounds();

    //Initialize the maze, player, and cat with some values
    Maze* newMaze = new Maze(MAZE_DIMENSIONS.first, MAZE_DIMENSIONS.second, 2, 1);
    Mouse* playerMouse = new Mouse(1, 0.2f);
    Cat* enemyCat = new Cat(1, 0.125f);

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
    audioManager.PlaySound("GameMusic");
    GameLoop(*newMaze, *playerMouse, *enemyCat);

	return 0;
}

/// <summary>
/// Preloads the sounds that will be used in the game.
/// </summary>
void PreloadSounds() {
    //Music
    audioManager.CreateSound("GameMusic", "Audio/BGM/game_music.wav", true);

    //SFX
    audioManager.CreateSound("Pickup", "Audio/SFX/food_pickup.wav");
    audioManager.CreateSound("Move", "Audio/SFX/player_move.wav");
    audioManager.CreateSound("Win", "Audio/SFX/win_sfx.wav");
    audioManager.CreateSound("Lose", "Audio/SFX/lose_sfx.wav");
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

        //Update the audio manager
        audioManager.Update();

        bool inputValid = false;

        // Wait for a key press without the need to press Enter
        key = _getch();

        //Try to move the player if they press the right button. If they press 'Q', quit the game immediately
        switch (key) {
        //Up Movement
        case 'w':
            inputValid = currentPlayer.Move(currentMaze, -1, 0);
            break;
        //Left Movement
        case 'a':
            inputValid = currentPlayer.Move(currentMaze, 0, -1);
            break;
        //Down Movement
        case 's':
            inputValid = currentPlayer.Move(currentMaze, 1, 0);
            break;
        //Right Movement
        case 'd':
            inputValid = currentPlayer.Move(currentMaze, 0, 1);
            break;
        //Quit Application
        case 'q':
            gameActive = false;
            inputValid = true;
            break;
        }

        //If the player has successfully performed movement
        if (inputValid) {

            if (gameActive) {

                //Play the player movement sound
                if (audioManager.IsSoundPlaying("Move"))
                    audioManager.StopSound("Move");
                audioManager.PlaySound("Move");

                //If the player found food, add to the player's score
                if (currentPlayer.CheckForFood(currentMaze)) {
                    if (audioManager.IsSoundPlaying("Pickup"))
                        audioManager.StopSound("Pickup");
                    audioManager.PlaySound("Pickup");
                    score++;
                }

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
    console::ClearScreen();  //Refresh console

    //Print the maze data
    currentMaze.Print();

    //Display information
    cout << "\nScore: " << score << " / " << MAX_FOOD_PIECES << endl;
    cout << "\nCat Status: " << (currentCat.CanSmellPlayer() ? "Tracking Scent" : "Wandering") << endl;
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
        " / /      / __ `/ / __/         / __ \\ |/          / /|_/ /  / __ \\ / / / /  / ___/ / _ \\",
        "/ /___   / /_/ / / /_          / / / /            / /  / /  / /_/ // /_/ /  (__  ) /  __/",
        "\\____/   \\__,_/  \\__/         /_/ /_/            /_/  /_/   \\____/ \\__,_/  /____/  \\___/ ",
        "                                                                                         ",
        "You are a mouse in a randomly generated maze, trying to collect enough food to survive the night. However, a cat patrols the lanes to thwart you of your plans.",
        "Whenever you move a couple of spaces in the maze, the cat moves 1 to 2 spaces in the maze as well.",
        "Whenever you roam around the maze, you leave an invisible scent trail in which the cat can pick up and follow, so be careful.",
        "\n===KEY===",
        " - Wall",
        ". - Empty Space",
        " - The Mouse (Player)",
        " - The Cat",
        " - Food (collectable)"
    };

    for (int i = 0; i < sizeof(startText) / sizeof(startText[0]); i++) {
        //Get the line of text
        string line = startText[i];

        switch (i) {
        //Print the title in teal
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
            console::PrintColorText(line, console::TEAL);
            cout << endl;
            break;
        //Show the wall symbol
        case 10:
            console::PrintColorText("#", Maze::wallColor);
            cout << line << endl;
            break;
        //Show the player symbol
        case 12:
            console::PrintColorText("M", Maze::mouseColor);
            cout << line << endl;
            break;
        //Show the cat symbol          
        case 13:
            console::PrintColorText("C", Maze::catColor);
            cout << line << endl;
            break;
        //Show the food symbol
        case 14:
            console::PrintColorText("F", Maze::foodColor);
            cout << line << endl;
            break;
        //Print normally
        default:
            cout << line << endl;
            break;
        }
    }

    cout << "\nPress any key to start." << endl;
    key = _getch();
    console::ClearScreen();  //Refresh console
}

/// <summary>
/// Displays a game win screen when the game win state is met.
/// </summary>
void WinScreen() {
    char key;
    console::ClearScreen();  //Refresh console

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

    //Stop the game music
    if (audioManager.IsSoundPlaying("GameMusic"))
        audioManager.StopSound("GameMusic");

    //Play the win SFX
    audioManager.PlaySound("Win");
    cout << "Press any key to quit the game." << endl;
    key = _getch();
}

/// <summary>
/// Displays a game over screen when the game lose state is met.
/// </summary>
void GameOverScreen() {
    char key;
    console::ClearScreen();  //Refresh console

    string gameOverText [] = 
    {"   ______                                    ____                      ",
     "  / ____/  ____ _   ____ ___   ___          / __ \\ _   __  ___    _____",
     " / / __   / __ `/  / __ `__ \\ / _ \\        / / / /| | / / / _ \\  / ___/",
     "/ /_/ /  / /_/ /  / / / / / //  __/       / /_/ / | |/ / /  __/ / /    ",
     "\\____/   \\__,_/  /_/ /_/ /_/ \\___/        \\____/  |___/  \\___/ /_/     ",
    "                                                                       "};

    for (const auto& line : gameOverText)
        cout << line << endl;

    //Stop the game music
    if (audioManager.IsSoundPlaying("GameMusic"))
        audioManager.StopSound("GameMusic");

    //Play the lose SFX
    audioManager.PlaySound("Lose");
    cout << "Press any key to quit the game." << endl;
    key = _getch();
}