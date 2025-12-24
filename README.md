# Tic Tac Toe with Minimax AI

An unbeatable Tic Tac Toe game built in C, featuring an AI opponent powered by the **Minimax algorithm**. Play against a perfect AI that never loses, or challenge a friend in two-player mode.

## 📸 Screenshots

### 1. Welcome Screen and Choose Number of Player
![Screenshot (35)](https://github.com/user-attachments/assets/d4aba134-8078-47cb-ad62-82248fbe06b4)

### 2. Enter player 1 name (if play multiplayer, also enter player 2 name)
![Screenshot (36)](https://github.com/user-attachments/assets/627777bb-3bc6-49cd-86b2-a5918cfcf215)

### 3. Player 1 (x) choose place on board by enter number on box
![Screenshot (37)](https://github.com/user-attachments/assets/9387eb2e-dd03-43ce-a328-6946035951d0)

### 4. Player 2 (o) also choose
![Screenshot (38)](https://github.com/user-attachments/assets/d4567ca7-80b0-4563-abae-d7e5edf1941a)

### 5. The Winner is Player 1!
![Screenshot (39)](https://github.com/user-attachments/assets/d3664aaf-9b78-4cd7-9374-c139b610ab8c)


## 🎮 Features

### Game Modes
- **Single Player** - Face an unbeatable AI using Minimax algorithm
- **Two Player** - Classic player vs player on the same computer
- **Choose Your Symbol** - Play as X or O in single-player mode

### AI Intelligence
- **Minimax Algorithm** - Complete game tree exploration
- **Perfect Play** - AI makes optimal moves every time
- **Adaptive Evaluation** - Adjusts strategy based on player's symbol choice
- **Guaranteed Outcome** - AI will win or draw, never lose

### User Experience
- Clean terminal-based UI with ASCII board
- Input validation (only accepts 1-9 for valid positions)
- Occupied position detection
- Clear winner announcement

## 🧠 Minimax Algorithm Explained

The AI uses the **Minimax algorithm**, a decision-making algorithm for two-player zero-sum games.

### How It Works

```
For each possible move:
  1. Simulate making that move
  2. Recursively evaluate all possible future game states
  3. Assume opponent plays optimally
  4. Choose the move that maximizes AI's minimum guaranteed score
```

### Algorithm Flow

```c
minimax(depth, isMaximizing):
    if (game over):
        return score  // +1 (AI win), -1 (human win), 0 (draw)
    
    if (isMaximizing):  // AI's turn
        bestScore = -∞
        for each empty position:
            place AI symbol
            score = minimax(depth+1, false)
            bestScore = max(score, bestScore)
        return bestScore
    
    else:  // Human's turn (minimizing)
        bestScore = +∞
        for each empty position:
            place human symbol
            score = minimax(depth+1, true)
            bestScore = min(score, bestScore)
        return bestScore
```

### Scoring System

The evaluation function returns:
- **+1** - AI wins (maximizing player)
- **-1** - Human wins (minimizing player)
- **0** - Draw

**Key Insight**: The score is reversed based on who chose X:
```c
// If human plays as O, AI is X (maximizing)
if (board[i][j] == 'X') return 1;  // AI wins
else return -1;                     // Human wins

// If human plays as X, AI is O (maximizing)
if (board[i][j] == 'X') return -1; // Human wins
else return 1;                      // AI wins
```

### Complexity

- **Time Complexity**: O(9!) = O(362,880) in worst case (first move)
- **Space Complexity**: O(9) for recursion depth
- **Optimization**: Early terminal state detection reduces actual evaluations
- **Result**: Instant response on modern hardware

## 🛠️ Technology Stack

- **Language**: C (C99 standard)
- **Algorithm**: Minimax with depth-first search
- **Data Structure**: 2D array for game board
- **Math Library**: `math.h` for INFINITY constants

## 📋 Prerequisites

```bash
# Ubuntu/Debian
sudo apt-get install build-essential

# macOS (Xcode Command Line Tools)
xcode-select --install

# Fedora/RHEL
sudo dnf install gcc
```

## 🚀 Installation & Running

Since there's no Makefile, compile directly with GCC:

### Quick Start

```bash
# Clone the repository
git clone https://github.com/yourusername/tictactoe-minimax.git
cd tictactoe-minimax

# Compile
gcc -std=c99 -Wall -Wextra -o tictactoe tictactoe.c -lm

# Run
./tictactoe
```

### Compilation Flags Explained

- `-std=c99` - Use C99 standard (for `bool` type, `INFINITY`)
- `-Wall -Wextra` - Enable all warnings for code quality
- `-o tictactoe` - Output executable named "tictactoe"
- `-lm` - Link math library (required for `INFINITY`)

### Optional: Create a Makefile

You can create a `Makefile` for easier compilation:

```makefile
# Makefile for Tic Tac Toe

CC = gcc
CFLAGS = -std=c99 -Wall -Wextra -Wno-unused-parameter
MATHFLAG = -lm

.PHONY: tictactoe clean

tictactoe: tictactoe.c
	$(CC) $(CFLAGS) tictactoe.c -o tictactoe $(MATHFLAG)

clean:
	rm -f tictactoe
```

Then simply run:
```bash
make tictactoe
```

## 📖 How to Play

### Starting the Game

1. Run the executable: `./tictactoe`
2. Choose number of players (1 or 2)

### Single Player Mode

```
How many player will play (MAX is 2): 1

Enter your name: Alice
X or O: X
```

- If you choose **X**, you move first
- If you choose **O**, AI moves first

### Making Moves

The board is numbered 1-9:

```
     |     |     
  1  |  2  |  3  
_____|_____|_____
     |     |     
  4  |  5  |  6  
_____|_____|_____
     |     |     
  7  |  8  |  9  
     |     |     
```

Enter the number (1-9) to place your symbol.

### Game Outcomes

```
// Human wins (rare against AI!)
---THE WINNER IS ALICE---

// AI wins (most common)
---YOU LOSE---

// Draw (possible with perfect play from both)
---THE GAME IS DRAW---
```

## 🗂️ Code Structure

```c
// Player data
typedef struct {
    char name[30];
    char symbol;
} player;

// Game state
char board[3][3];           // 3x3 game board
player players[2];          // Player information
char COMPUTER_AI;           // AI's symbol

// Core functions
void human_move();          // Handle player input
void computer_move();       // AI makes optimal move
int minimax(int, bool);     // Minimax algorithm
int check_win();            // Check game state
```

## 🎯 Algorithm Deep Dive

### Why Is It Unbeatable?

The Minimax algorithm explores **every possible game state**:

```
Current Board → [9 possible moves]
    ├─ Move 1 → [8 possible responses]
    │   ├─ Response 1 → [7 possible moves]
    │   │   └─ ... (continues until game ends)
    │   └─ Response 8 → ...
    └─ Move 9 → [8 possible responses]
        └─ ...
```

For **each possible move**, the AI:
1. Simulates the entire future game
2. Assumes you play perfectly
3. Calculates the guaranteed outcome
4. Chooses the move with the best guaranteed result

### Example: AI's First Move

If you play X in the center (position 5), the AI evaluates all 8 corners/edges:

```c
// Pseudo-evaluation for each AI move
Position 1 (corner): minimax → score = 0 (draw with perfect play)
Position 2 (edge):   minimax → score = 0 (draw with perfect play)
Position 3 (corner): minimax → score = 0 (draw with perfect play)
...
// AI picks any position that guarantees at least a draw
```

### Can You Beat It?

**No** - if the AI plays first or responds to your first move optimally.

**Draw is possible** - with perfect play from both sides, the game always draws. The AI guarantees this outcome.

## 🧪 Testing the AI

Try these scenarios:

### Test 1: Can You Win as First Player?
```
You: X (position 5 - center)
AI: O (responds with corner)
Try to win... (you won't!)
```

### Test 2: Can AI Lose as First Player?
```
AI: X (optimal opening)
You: O (try any strategy)
AI will win or draw
```

### Test 3: Force a Draw
```
Both players play perfectly:
- Center on first move
- Block all winning moves
- Result: Draw
```

## ⚡ Performance

- **First move calculation**: ~0.01 seconds
- **Mid-game calculation**: ~0.001 seconds (fewer positions to evaluate)
- **Total game states explored**: Up to 362,880 (9!)
- **Actual evaluations**: Fewer due to early termination

## ⚠️ Known Limitations

- Runs only on Unix-like systems (uses `system("clear")`)
- No save/load game functionality
- No difficulty levels (always plays perfectly)
- No move history or undo feature
- Terminal must support ANSI escape sequences

## 🔧 Possible Improvements

- [ ] Add Alpha-Beta pruning to reduce evaluations
- [ ] Implement difficulty levels (random moves occasionally)
- [ ] Add move history and undo
- [ ] Create ncurses-based UI
- [ ] Add game statistics tracking
- [ ] Port to other platforms (Windows)
- [ ] Implement Monte Carlo Tree Search (MCTS) as alternative AI
- [ ] Add opening book for instant first moves
- [ ] Network multiplayer support
- [ ] Animated move transitions

## 🤝 Contributing

Contributions welcome! Ideas:

1. **Alpha-Beta Pruning** - Optimize minimax by pruning branches
2. **Difficulty Modes** - Add "Easy" and "Medium" difficulty
3. **GUI Version** - Create graphical interface
4. **Move Suggestions** - Highlight best move for learning
5. **Animated Board** - Add visual effects for moves

## 📝 License

This project is open source and available under the [MIT License](LICENSE).

## 👤 Author

**Kevin Mahendra**
- GitHub: [@thekevinkun](https://github.com/thekevinkun)
- Email: kevinmahendra.idn@gmail.com
- LinkedIn: [https://www.linkedin.com/in/kevinmahendra1997/](https://www.linkedin.com/in/kevinmahendra1997/)

## 🙏 Acknowledgments

- Built while learning C and game theory
- Minimax algorithm based on classic AI game theory
- Inspired by unbeatable Tic Tac Toe implementations

## 📚 Learning Resources

Key concepts in this project:

- **Minimax Algorithm**: [Stanford CS221](https://stanford.edu/~cpiech/cs221/handouts/kminimax.html)
- **Game Theory**: [Wikipedia - Minimax](https://en.wikipedia.org/wiki/Minimax)
- **Recursion in C**: [Recursive Functions](https://www.programiz.com/c-programming/c-recursion)
- **Zero-Sum Games**: [Game Theory Basics](https://www.investopedia.com/terms/z/zero-sumgame.asp)

## 🎓 Educational Value

This project demonstrates:

✅ **Recursion** - Deep recursive tree traversal  
✅ **Algorithm Design** - Classic AI game-playing algorithm  
✅ **Game Theory** - Optimal decision-making in adversarial games  
✅ **State Space Search** - Exploring all possible game states  
✅ **Backtracking** - Reverting board state after evaluation  
✅ **Optimization** - Early termination on winning states  

Perfect for:
- Learning game AI programming
- Understanding recursion deeply
- Preparing for algorithm interviews
- Building portfolio projects

## 🏆 Challenge

**Can you modify the code to make the AI beatable?**

Try implementing:
- Random move occasionally (difficulty: easy)
- Depth-limited minimax (difficulty: medium)
- Only evaluate first N moves (difficulty: hard)

---

**Note**: This implementation proves the AI cannot lose. Tic Tac Toe is a "solved game" - with perfect play, the result is always a draw or win for the first player who plays perfectly.

