#include <iostream>
#include <conio.h>
#include <windows.h>
#include <time.h>
#include <vector>
#include <fstream>
#include <algorithm>

using namespace std;

const int WIDTH = 10, HEIGHT = 20;
int score = 0;
int highScore = 0;
vector<vector<int>> field(HEIGHT, vector<int>(WIDTH, 0));

struct Point { int x, y; };
vector<Point> a(4), b(4);

// Different Tetromino shapes
vector<vector<int>> figures = {
    {1,3,5,7}, // I-shape
    {2,4,5,7}, // Z-shape
    {3,5,4,6}, // S-shape
    {3,5,4,7}, // T-shape
    {2,3,5,7}, // L-shape
    {3,5,7,6}, // J-shape
    {2,3,4,5}, // O-shape
};

// Function to load high score from file
void loadHighScore() {
    ifstream inFile("highscore.txt");
    if (inFile) {
        inFile >> highScore;
        inFile.close();
    }
}

// Function to save high score to file
void saveHighScore() {
    ofstream outFile("highscore.txt");
    if (outFile) {
        outFile << highScore;
        outFile.close();
    }
}

// Function to check if the tetromino is within bounds and not colliding
bool check() {
    for (int i = 0; i < 4; i++)
        if (a[i].x < 0 || a[i].x >= WIDTH || a[i].y >= HEIGHT || field[a[i].y][a[i].x])
            return false;
    return true;
}

// Function to display game instructions
void showInstructions() {
    system("cls");
    cout << "========== TETRIS GAME ==========\n";
    cout << "Controls:\n";
    cout << "Left Arrow  - Move Left\n";
    cout << "Right Arrow - Move Right\n";
    cout << "Up Arrow    - Rotate\n";
    cout << "Down Arrow  - Speed Up\n";
    cout << "Space       - Hard Drop\n";
    cout << "ESC         - Pause Game\n";
    cout << "\nScoring:\n";
    cout << "5 points for each new piece\n";
    cout << "100 points for each completed line\n";
    cout << "\nGame speeds up as you score more points!\n";
    cout << "\nPress any key to start...";
    _getch();
}

// Function to render the game board and tetrominoes
void draw() {
    system("cls");
    cout << "Score: " << score << "  High Score: " << highScore << endl;

    for (int i = 0; i < HEIGHT; i++) {
        for (int j = 0; j < WIDTH; j++) {
            bool occupied = false;
            for (int k = 0; k < 4; k++)
                if (a[k].x == j && a[k].y == i) { occupied = true; break; }
            
            if (occupied) cout << "[]";
            else if (field[i][j]) cout << "[]";
            else cout << " .";
        }
        cout << endl;
    }
}

// Function to drop the tetromino instantly (hard drop)
void hardDrop() {
    while (check()) {
        for (int i = 0; i < 4; i++) a[i].y++;
    }
    for (int i = 0; i < 4; i++) {
        a[i].y--;
        field[a[i].y][a[i].x] = 1;
    }
}

int main() {
    srand(time(0));
    int dx = 0, speed = 500;
    bool rotate = false, newPiece = true, paused = false;
    
    loadHighScore();
    showInstructions();

    while (true) {
        // Generate a new Tetromino
        if (newPiece) {
            int n = rand() % 7;
            for (int i = 0; i < 4; i++) {
                a[i].x = figures[n][i] % 2 + WIDTH / 2 - 1;
                a[i].y = figures[n][i] / 2;
            }
            if (!check()) break;
            newPiece = false;
            score += 5;
        }

        // Handle player input
        if (_kbhit()) {
            char key = _getch();
            
            if (key == 27) { 
                paused = !paused;
                if (paused) {
                    system("cls");
                    cout << "Game Paused! Press ESC to Resume." << endl;
                    while (_getch() != 27);
                    paused = false;
                }
            }
            else if (key == 75) dx = -1;
            else if (key == 77) dx = 1;
            else if (key == 72) rotate = true;
            else if (key == 80) speed = 50;
            else if (key == 32) hardDrop();
        }

        // Move the piece horizontally
        for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].x += dx; }
        if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];

        // Rotate the piece
        if (rotate) {
            Point p = a[1]; // Center of rotation
            for (int i = 0; i < 4; i++) {
                int y = a[i].y - p.y;
                int x = a[i].x - p.x;
                a[i].x = (p.x - y);
                a[i].y = (p.y + x);
            }
            if (!check()) for (int i = 0; i < 4; i++) a[i] = b[i];
        }

        // Move the piece down
        for (int i = 0; i < 4; i++) { b[i] = a[i]; a[i].y += 1; }
        if (!check()) {
            for (int i = 0; i < 4; i++) field[b[i].y][b[i].x] = 1;
            newPiece = true;
        }

        // Check for complete lines
        int k = HEIGHT - 1;
        for (int i = HEIGHT - 1; i >= 0; i--) {
            int count = 0;
            for (int j = 0; j < WIDTH; j++)
                if (field[i][j]) count++;
        
            if (count == WIDTH) {
                for (int j = 0; j < WIDTH; j++)
                    field[i][j] = 0;
                score += 100;
            } else {
                for (int j = 0; j < WIDTH; j++)
                    field[k][j] = field[i][j];
                k--;
            }
        }

        draw();
        
        // Adjust game speed based on score
        if (score > 100 && score < 400) {
            speed = 200;
        }
        else if (score >= 400) {
            speed = 75;
        }
        
        Sleep(speed);
        dx = 0; rotate = false; speed = 500;
    }

    // Update high score if needed
    if (score > highScore) {
        highScore = score;
        saveHighScore();
    }

    cout << "Game Over! Final Score: " << score << endl;
    cout << "High Score: " << highScore << endl;
    cout << "Press any key to exit...";
    _getch();
    return 0;
}
