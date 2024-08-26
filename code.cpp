#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Function to display the game board
void displayBoard(int robotX, int robotY, int goalX, int goalY, const vector<vector<char>>& board) {
    for (int i = 0; i < board.size(); i++) {
        for (int j = 0; j < board[i].size(); j++) {
            if (i == robotY && j == robotX)
                cout << "R "; // R represents the robot
            else if (i == goalY && j == goalX)
                cout << "G "; // G represents the goal
            else
                cout << board[i][j] << " "; // . represents empty space, X represents obstacles
        }
        cout << endl;
    }
}

// Function to move the robot
void moveRobot(int &robotX, int &robotY, char direction, int gridSize, const vector<vector<char>>& board) {
    int newX = robotX, newY = robotY;
    switch (direction) {
        case 'w':
            newY--;
            break;
        case 's':
            newY++;
            break;
        case 'a':
            newX--;
            break;
        case 'd':
            newX++;
            break;
        default:
            cout << "Invalid move! Use w/a/s/d to move." << endl;
            return;
    }
    if (newX >= 0 && newX < gridSize && newY >= 0 && newY < gridSize && board[newY][newX] != 'X') {
        robotX = newX;
        robotY = newY;
    } else {
        cout << "Move blocked by obstacle or out of bounds!" << endl;
    }
}

// Function to generate a random position
pair<int, int> generateRandomPosition(int gridSize, const vector<vector<char>>& board) {
    int x, y;
    do {
        x = rand() % gridSize;
        y = rand() % gridSize;
    } while (board[y][x] == 'X');
    return {x, y};
}

int main() {
    srand(time(0));
    int gridSize = 5; // Size of the game board
    vector<vector<char>> board(gridSize, vector<char>(gridSize, '.'));

    // Place obstacles
    board[1][1] = 'X';
    board[2][3] = 'X';
    board[3][1] = 'X';

    // Generate random start and goal positions
    pair<int, int> startPos, goalPos;
    do {
        startPos = generateRandomPosition(gridSize, board);
        goalPos = generateRandomPosition(gridSize, board);
    } while (startPos == goalPos);

    int robotX = startPos.first, robotY = startPos.second;
    int goalX = goalPos.first, goalY = goalPos.second;

    char move;
    bool gameRunning = true;
    int moves = 0;

    cout << "Welcome to CodeQuest: The C++ Adventure!" << endl;
    cout << "Move your robot using w (up), a (left), s (down), d (right)." << endl;
    cout << "Your goal is to reach the goal position (G)!" << endl;

    while (gameRunning) {
        // Display the game board
        displayBoard(robotX, robotY, goalX, goalY, board);

        // Get the player's move
        cout << "Enter your move (w/a/s/d): ";
        cin >> move;

        // Move the robot based on player input
        moveRobot(robotX, robotY, move, gridSize, board);
        moves++;

        // Check if the robot has reached the goal position
        if (robotX == goalX && robotY == goalY) {
            cout << "Congratulations! You've reached the goal and completed the level!" << endl;
            cout << "Total moves: " << moves << endl;
            gameRunning = false;
        }
    }

    return 0;
}
