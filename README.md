# 🕹️ Tetris Game in C++

## 📋 Table of Contents
- [About the Project](#about-the-project)  
- [Features](#features)  
- [Technologies Used](#technologies-used)  
- [Getting Started](#getting-started)  
- [Controls](#controls)  
- [Code Breakdown](#code-breakdown)  
- [Screenshots](#screenshots)  
- [How to Contribute](#how-to-contribute)  
- [License](#license)  

---

## 📌 About the Project
This is a **classic Tetris game** implemented in C++. The game features **real-time controls**, **score tracking**, **high score persistence**, and **game speed adjustments based on performance**. The goal is to **stack falling Tetrominoes**, clear lines, and achieve the highest score possible.

---

## 🎯 Features
✅ **Classic Tetris gameplay** with seven Tetromino shapes.  
✅ **Score and High Score tracking** (high score saved to a file).  
✅ **Hard drop feature** (press `SPACE` to drop pieces instantly).  
✅ **Game speed increases** as score increases.  
✅ **Pause feature** (press `ESC` to pause and resume the game).  

---

## 🛠️ Technologies Used
- **C++ Standard Library**
- **Windows.h** → For controlling game speed using `Sleep()`  
- **Conio.h** → For real-time keyboard input (`_kbhit()` and `_getch()`)  
- **fstream** → For saving and loading high scores  

---

## 🚀 Getting Started

### 📥 Prerequisites
To run this project, you need:
- **Windows OS**  
- **G++ compiler** (MinGW or any C++ compiler for Windows)  

### 🔧 Installation and Execution

1. Clone the repository:
```bash
git clone https://github.com/DivyModi17/tetris-cpp.git
```

2. Navigate to the project folder:
```bash
cd tetris-cpp
```

3. Compile the code:
```bash
g++ -o tetris tetris.cpp -std=c++11
```

4. Run the game:
```bash
tetris
```

✅ **Note:** This game uses **Windows-specific libraries** (`windows.h` and `conio.h`). It will only run on Windows machines.

---

## 🎮 Controls
- `←` → Move Left  
- `→` → Move Right  
- `↑` → Rotate  
- `↓` → Speed Up  
- `SPACE` → Instantly Drop the Piece  
- `ESC` → Pause / Resume  

---

## 🛠️ Code Breakdown

### 1️⃣ **Tetromino Shapes**
```cpp
vector<vector<int>> figures = {
    {1,3,5,7}, // I-shape
    {2,4,5,7}, // Z-shape
    {3,5,4,6}, // S-shape
    {3,5,4,7}, // T-shape
    {2,3,5,7}, // L-shape
    {3,5,7,6}, // J-shape
    {2,3,4,5}, // O-shape
};
```
- The **Tetromino shapes** are stored as integer arrays, representing positions on a 2×4 grid.

### 2️⃣ **Loading and Saving High Score**
```cpp
void loadHighScore() {
    ifstream inFile("highscore.txt");
    if (inFile) {
        inFile >> highScore;
        inFile.close();
    }
}

void saveHighScore() {
    ofstream outFile("highscore.txt");
    if (outFile) {
        outFile << highScore;
        outFile.close();
    }
}
```
- **Reads and writes the high score** to a text file to preserve it across game sessions.

### 3️⃣ **Collision Detection**
```cpp
bool check() {
    for (int i = 0; i < 4; i++)
        if (a[i].x < 0 || a[i].x >= WIDTH || a[i].y >= HEIGHT || field[a[i].y][a[i].x])
            return false;
    return true;
}
```
- Ensures that the Tetromino **does not move outside the board** or overlap with existing blocks.

### 4️⃣ **Game Loop**
```cpp
while (true) {
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
}
```
- Spawns a **random Tetromino** and positions it in the middle of the board.

### 5️⃣ **Hard Drop Mechanism**
```cpp
void hardDrop() {
    while (check()) {
        for (int i = 0; i < 4; i++) a[i].y++;
    }
    for (int i = 0; i < 4; i++) {
        a[i].y--;
        field[a[i].y][a[i].x] = 1;
    }
}
```
- Drops the piece **instantly** to the bottom of the board.

---

## 🖼️ Screenshots
### 📊 In-Game Board
```
Score: 300   High Score: 600  
+----------+  
|          |  
|    []    |  
|   [][]   |  
|          |  
+----------+  
```

### 🚫 Game Over Screen
```
GAME OVER  
Final Score: 1200   High Score: 3000  
Press any key to exit.
```

---

## 🔥 How to Contribute
1. Fork the repository.  
2. Clone your fork:  
```bash
git clone https://github.com/DivyModi17/tetris-cpp.git
```
3. Create a new branch:  
```bash
git checkout -b feature-name
```
4. Make changes and create a pull request.

---
