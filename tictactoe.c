#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

typedef struct
{
    char name[30];
    char symbol;
}
player;

// GRID TOTAL BOX
const int N = 3;

char tab = '\t';

char board[3][3] = {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
};

player players[2];

char COMPUTER_AI;

int numOfplayer, winner;

void delay(int seconds);
void information();
void draw_board();
void draw_line();
void two_player_gameplay();
int check_win();
int check_minimax_win();
void show_the_winner(int result);
void human_move();
void computer_move();
int minimax(int depth, bool isMaximizing);

int main(void)
{
    printf("Welcome to Tic-Tac-Toe game!\n\n");

    information(); 
    
    if (numOfplayer == 2)
    { 
        two_player_gameplay();
    }
    else
    {
        // IF user choose to be X, move first
        if (players[0].symbol == 'X')
        {
            human_move();
        }
        else
        {
            computer_move();
        }
    }

    return 0;
}

// FUNCTION TO HANDLE HUMAN MOVE
void human_move()
{
    int choice, found, result;
    char mark, char_choice;

    draw_board();

    // Keep prompt user get the valid board number
    do
    {
        printf("\t\t\t\t");
        printf("%s : ", players[0].name);
        scanf("%i", &choice);
    
        // Get player symbol
        mark = players[0].symbol;
            
        // Always reset found to 0
        found = 0;

        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
            {
                // Convert user choice from int to char to compare with board array
                char_choice = choice + '0';
                    
                // Check if number user choose is still exist in board, then it's legal to change it with user symbol
                if (board[row][col] == char_choice)
                {
                    // After change it, increment found if the board valid
                    board[row][col] = mark;
                    found++;
                    
                    // Break the loop
                    row = col = N;
                    break;
                }
            }
        }
    
    }
    while ((choice < 1 || choice > 9) || found == 0);
    
    // Check if there's a winner
    // IF It's 2, game still running, computer turn to move
    // Otherwise, call show the winner function
    result = check_win();
    if (result == 2)
    {
        computer_move();
    }
    else
    {
        show_the_winner(result);
    }
}

// FUNCTION TO HANDEL COMPUTER MOVE
void computer_move()
{
    char board_number;
    int move_i, move_j;

    // Set best score to minus INFINITY
    float bestScore = -INFINITY;

    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < N; j++)
        {
            // CHECK IF BOARD IS EMPTY
            if (board[i][j] != 'X' && board[i][j] != 'O')
            {
                // Get the real number on board
                board_number = board[i][j];

                // Change the board temporary
                // So we can call minimax to calculate it
                board[i][j] = COMPUTER_AI;    
                float score = minimax(0, false);

                // Reset to default board number
                board[i][j] = board_number;

                // AS maximizing player, IF score GREATER Than best score,
                // Change the best score, store current board position to be placed
                if (score > bestScore)
                {
                    bestScore = score;
                    move_i = i;
                    move_j = j;
                }
            }           
        }
    }
    // Placed the best position
    board[move_i][move_j] = COMPUTER_AI;
    
    // Check win, if it's still running, human turn to move
    int result = check_win();
    if (result == 2)
    {
        human_move();
    }
    else
    {
        show_the_winner(result);
    }
}

// MINIMAX FUNCTION
int minimax(int depth, bool isMaximizing)
{
    // Base case
    // Return static evaluation after get the winner
    int result = check_minimax_win();
    if (result != 2)
    {
        return result;
    }

    // IF Maximizing player turn to analyze
    if (isMaximizing)
    {
        // SET best score to minus infinity
        float bestScore = -INFINITY;

        // ITERATE THROUGH BOARD
        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
            {
                // Check if the positon in board is empty
                if (board[row][col] != 'X' && board[row][col] != 'O')
                {
                    // Get the real number on board
                    char board_number = board[row][col];

                    // Change the current position in board as MAXIMIZING (COMPUTER) symbol
                    // Call minimax recursively, minimizing turn
                    board[row][col] = COMPUTER_AI;
                    float score = minimax(depth + 1, false);

                    // Reset to default board number
                    board[row][col] = board_number;
                    
                    // AS maximizing player, find the MAX score, store into best score
                    if (score > bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
    // OTHERWISE, MINIMIZING TURN to analyze
    else
    {
        // SET best score to +INFINITY
        float bestScore = INFINITY;

        for (int row = 0; row < N; row++)
        {
            for (int col = 0; col < N; col++)
            {
                if (board[row][col] != 'X' && board[row][col] != 'O')
                {
                    char board_number = board[row][col];

                    // Change the current position in board as MAXIMIZING (COMPUTER) symbol, temporary
                    // Call minimax recursively, maximizing turn
                    board[row][col] = players[0].symbol;
                    float score = minimax(depth + 1, true);
                    
                    // Reset to default board number
                    board[row][col] = board_number;

                    // AS Minimizing, get the Minimum score, store it to best score
                    if (score < bestScore)
                    {
                        bestScore = score;
                    }
                }
            }
        }
        return bestScore;
    }
}

// TWO PLAYER GAMEPLAY
void two_player_gameplay() 
{
    int player = 0;
    int choice, found, result;
    char mark, char_choice;
 
    do 
    {
        draw_board();

        // PROMPT current player to move
        printf("\t\t\t\t");
        printf("%s : ", players[player % 2].name);
        scanf("%i", &choice);

        // Get player symbol
        mark = players[player % 2].symbol;

        // Iterate through board to check and replace the board with user symbol
        for (int row = 0; row < N; row++) 
        {
            for (int col = 0; col < N; col++)
            {
                // Convert user choice from int to char to compare with board array
                char_choice = choice + '0';
                
                // Check if number user choose is still exist in board, then it's legal to change it with user symbol
                if (board[row][col] == char_choice)
                {
                    // After change it, increment player to the next
                    board[row][col] = mark;
                    player++;

                    // Break the loop
                    row = col = 3;
                    break;
                }
            }
        }

        // Call function to check if there's already winner
        result = check_win();
    } 
    while ((choice < 1 || choice > 9) || result == 2);

    draw_board();

    show_the_winner(result);
}

// FUNCTION TO ASK USER BEFORE STARTING GAME
void information()
{
    // KEEP prompt user until enter valid number of player
    do
    {
        printf("How many player will play (MAX is 2): ");
        scanf("%i", &numOfplayer);
    }
    while (numOfplayer > 2);
    printf("\n");

    // If there's only one player
    if(numOfplayer < 2)
    {
        printf("Enter your name: ");
        scanf("%s", players[0].name);
        getchar();

        // Keep prompt user until enter valid symbol
        do
        {
            printf("X or O: ");
            scanf("%c", &players[0].symbol);
            getchar();
        }
        while ((players[0].symbol != 'X' && players[0].symbol != 'x') && 
                (players[0].symbol != 'O' && players[0].symbol != 'o'));    

        // Assign symbol to user and computer
        players[0].symbol = toupper(players[0].symbol);
        COMPUTER_AI = (players[0].symbol == 'X' ? 'O' : 'X');
    }
    // Otherwise, two player
    else
    {
        for (int i = 0; i < 2; i++)
        {
            // Get user name
            printf("Enter Player %i name: ", i + 1);
            scanf("%s", players[i].name);
            getchar();
            
            printf("\n");
        
        }

        // First player get X symbol
        // Second player get O symbol    
        players[0].symbol = toupper('X');
        players[1].symbol = ((toupper(players[0].symbol) == 'X') ? 'O' : 'X');
    }

    printf("\n\n");
}

// FUNCTION TO CHECK IF THERE IS WINNER 
/*
    Return 1 means X is winning.
    Return -1 means O is winning.
    Return 0 means game is draw.
    Return 2 means game still running.
*/
int check_win()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 1; j <= 1; j++)
        {
            // CHECK THREE in a row on HORIZONTAL Board
            if (board[i][j - 1] == board[i][j] && board[i][j] == board[i][j + 1])
            {
                if (board[i][j] == 'X')
                {
                    return 1;
                }
                else
                {
                    return -1;
                }
            }
            // CHECK THREE in a row on VERTICAL Board
            else if (board[j - 1][i] == board[j][i] && board[j][i] == board[j + 1][i])
            {
                if (board[j][i] == 'X')
                {
                    return 1;
                }
                else
                {
                    return -1;
                }
            }
            // CHECK THREE in a row on SLASH Board || 1 - 5- 9 or 3 - 5 - 7
            else if (board[j - 1][j - 1] == board[j][j] && board[j][j] == board[j + 1][j + 1])
            {
                if (board[j][j] == 'X')
                {
                    return 1;
                }
                else
                {
                    return -1;
                }
            }
            else if (board[j - 1][j + 1] == board[j][j] && board[j][j] == board[j + 1][j - 1])
            {
                if (board[j][j] == 'X')
                {
                    return 1;
                }
                else
                {
                    return -1;
                }
            }
            // CHECK IF BOARD ALREADY FULL, AND NO ONES WIN (DRAW)
            else if (board[j - 1][j - 1] != '1' && board[j - 1][j] != '2' && board[j - 1][j + 1] != '3' && 
                     board[j][j - 1] != '4' && board[j][j] != '5' && board[j][j + 1] != '6' &&
                     board[j + 1][j - 1] != '7' && board[j + 1][j] != '8' && board[j + 1][j + 1] != '9')
                     {
                         return 0;
                     }
        }
    }
    // IF there's no three symbol in a row yet, game still running
    return 2;
}

// FUNCTION TO CHECK THE WINNER || ONLY SPECIFY FOR MINIMAX FUNCTION
// HANDLE DIFFERENT RETURN BETWEEN X and O
/*
    When user decide to play as X: O is computer as maximizing player
    So, it always return 1 for best score
    When user decide to play as O: X is computer as maximizing player
    So, it ALSO always return 1 for best score

    -1 is ONLY score for minimizing player: Human.
*/ 
int check_minimax_win()
{
    for (int i = 0; i < N; i++)
    {
        for (int j = 1; j <= 1; j++)
        {
            // CHECK THREE in a row on HORIZONTAL Board
            if (board[i][j - 1] == board[i][j] && board[i][j] == board[i][j + 1])
            {
                // IF user decide to play as O
                if (players[0].symbol == 'O')
                {   
                    // Computer as maximizing player, X return 1 as best score
                    // O return -1 as minimizing score 
                    if (board[i][j] == 'X')
                    {
                        return 1;
                    }
                    else
                    {
                        return -1;
                    }
                }

                // IF user decide to play as X
                if (players[0].symbol == 'X')
                {
                    // REVERSE THE RETURN VALUE (NOT CONDITION)
                    // Computer as maximizing player, X return -1 as minimizing score
                    // O return 1 as maximizing score 
                    if (board[i][j] == 'X')
                    {
                        // X as minimizing
                        return -1;
                    }
                    else
                    {
                        // O as maximizing
                        return 1;
                    }
                }    
            }
            // CHECK THREE in a row on VERTICAL Board
            else if (board[j - 1][i] == board[j][i] && board[j][i] == board[j + 1][i])
            {
                if (players[0].symbol == 'O')
                {
                    // Computer as maximizing player, X return 1 as best score
                    // O return -1 as minimizing score 
                    if (board[j][i] == 'X')
                    {
                        return 1;
                    }
                    else
                    {
                        return -1;
                    }
                }

                if (players[0].symbol == 'X')
                {
                    // REVERSE THE RETURN VALUE (NOT CONDITION)
                    // Computer as maximizing player, X return -1 as minimizing score
                    // O return 1 as maximizing score
                    if (board[j][i] == 'X')
                    {
                        return -1;
                    }
                    else
                    {
                        return 1;
                    }
                }    
            }
            // CHECK THREE in a row on SLASH Board || 1 - 5- 9 or 3 - 5 - 7
            else if (board[j - 1][j - 1] == board[j][j] && board[j][j] == board[j + 1][j + 1])
            {
                if (players[0].symbol == 'O')
                {
                    // Computer as maximizing player, X return 1 as best score
                    // O return -1 as minimizing score 
                    if (board[j][j] == 'X')
                    {
                        return 1;
                    }
                    else
                    {
                        return -1;
                    }
                }

                if (players[0].symbol == 'X')
                {
                    // REVERSE THE RETURN VALUE (NOT CONDITION)
                    // Computer as maximizing player, X return -1 as minimizing score
                    // O return 1 as maximizing score
                    if (board[j][j] == 'X')
                    {
                        return -1;
                    }
                    else
                    {
                        return 1;
                    }
                }
            }
            else if (board[j - 1][j + 1] == board[j][j] && board[j][j] == board[j + 1][j - 1])
            {
                if (players[0].symbol == 'O')
                {
                    // Computer as maximizing player, X return 1 as best score
                    // O return -1 as minimizing score
                    if (board[j][j] == 'X')
                    {
                        return 1;
                    }
                    else
                    {
                        return -1;
                    }
                }

                if (players[0].symbol == 'X')
                {
                    // REVERSE THE RETURN VALUE (NOT CONDITION)
                    // Computer as maximizing player, X return -1 as minimizing score
                    // O return 1 as maximizing score
                    if (board[j][j] == 'X')
                    {
                        return -1;
                    }
                    else
                    {
                        return 1;
                    }
                }    
            }
            // CHECK IF BOARD ALREADY FULL, AND NO ONES WIN (DRAW)
            else if (board[j - 1][j - 1] != '1' && board[j - 1][j] != '2' && board[j - 1][j + 1] != '3' && 
                     board[j][j - 1] != '4' && board[j][j] != '5' && board[j][j + 1] != '6' &&
                     board[j + 1][j - 1] != '7' && board[j + 1][j] != '8' && board[j + 1][j + 1] != '9')
                     {
                         return 0;
                     }
        }
    }
    // IF there's no three symbol in a row yet, game still running
    return 2;
}

// FUNCTION TO SHOW THE WINNER
void show_the_winner(int result)
{
    // AS one player only
    if (numOfplayer < 2)
    {
        // CHECK IF the user symbol match with the result
        if ((players[0].symbol == 'X' && result == 1) || (players[0].symbol == 'O' && result == -1))
        {
            draw_board();
            printf("\n\t\t\t\t\t    ---THE WINNER IS %s---\n\n\n", players[0].name);
        }
        // MAKE SURE COMPUTER PLAY AS X(1) OR O (-1)
        else if (result == -1 || result == 1)
        {
            draw_board();
            printf("\n\t\t\t\t\t\t ---YOU LOSE---\n\n\n");
        }
        // TIES
        else 
        {
            draw_board();
            printf("\n\t\t\t\t\t     ---THE GAME IS DRAW---\n\n\n");
        }
    }
    // TWO PLAYER GAMEPLAY
    else
    {
        // The end of game conditions
        for (int i = 0; i < 2; i++)
        {
            if (result == 1) 
            {
                if (players[i].symbol == 'X')
                {
                    printf("\n\t\t\t\t\t    ---THE WINNER IS %s---\n\n\n", players[i].name);
                    break;
                }
            }
            if (result == -1) 
            {
                if (players[i].symbol == 'O')
                {
                    printf("\n\t\t\t\t\t    ---THE WINNER IS %s---\n\n\n", players[i].name);
                    break;
                }
            }
            if (result == 0)
            {
                printf("\n\t\t\t\t\t     ---THE GAME IS DRAW---\n\n\n");
                break;
            }
        }
    }
}

// FUNCTION TO DRAW TICTACTOE BOARD
void draw_board()
{
    system("clear");

    printf("\n\n");
    printf("\t\t\t\tEnter the number on board to choose your place!\n\n\n");

    if (numOfplayer < 2)
    {
        printf("\t\t\t\t");
        printf("%s : %c", players[0].name, toupper(players[0].symbol));
    }
    else
    {
        printf("\t\t\t\t");
        printf("(Player 1) %s : %c\n", players[0].name, toupper(players[0].symbol));
        printf("\t\t\t\t");
        printf("(Player 2) %s : %c\n", players[1].name, toupper(players[1].symbol));
    }
    printf("\n\n");

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            // Print extra vertical bar on top only when for first column
            if (col == 0)
            {
                printf("\t\t\t\t\t\t");
                printf("     |     |     ");
                printf("\n");
                printf("\t\t\t\t\t\t");
            }
            
            // Print the number on each board column--Horizontally
            printf("  %c  ", board[row][col]);

            // Print vertical bar at the end of number || EXCEPT for the last number
            if (col != 2)
            {
                printf("|");
            }
            
        }
        printf("\n");

        // Print horizontal bar only for 2 column
        if (row != 2)
        {
            printf("\t\t\t\t\t\t");
            printf("_____|_____|_____");
            printf("\n");
        }

        // Print extra vertical bar on below
        if (row == 2)
        {
            printf("\t\t\t\t\t\t");
            printf("     |     |     ");
            printf("\n");  
        }
    }
    printf("\n\n");
}

// void delay(int seconds)
// {
//     // Converting time into milli_seconds
//     int milli_seconds = 1000 * seconds;
  
//     // Storing start time
//     clock_t start_time = clock();
  
//     // looping till required time is not achieved
//     while (clock() < start_time + milli_seconds);
// }