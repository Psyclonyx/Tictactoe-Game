#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>
#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#define IS_WINDOWS 1
#else
#include <unistd.h>
#define IS_WINDOWS 0
#endif

void drawBoard(char pos[]);
char *clearBoard(char pos[]);
int readMove(char pos[]);
void clearBuffer();
bool winCondition(char pos[], char sign);
int computerMove(char pos[], int turn, int difficulty);
int randomMove(int size, int *availableMoves);
int checkMovesOneDeep(char pos[], int size, int *availableMoves, char sign);
int checkMovesTwoDeep(char pos[], int size, int *availableMoves, char sign);

int main()
{
    int turn = 0;
    char sign;
    char pos[9];

    // Initialize positions with numbers 1-9
    for (int i = 0; i < 9; i++)
    {
        pos[i] = i + '1';
    }
    int difficulty;
    srand(time(NULL)); // seed rand() with time

    while (true)
    {
        system("clear");
        printf("TIC TAC TOE\n");
        drawBoard(pos);
        clearBoard(pos);
        printf("Choose a difficulty for opponent\n"); // Difficulty setting
        printf("Easy (1), Normal (2), Hard (3), Expert (4): ");
        while (scanf("%d", &difficulty) != 1 || difficulty < 1 || difficulty > 4)
        {
            printf("Invalid input. Please enter 1-3: ");
            clearBuffer();
        }
        clearBuffer();

        // Game loop
        while (true)
        {
            system("clear");
            drawBoard(pos);

            if (turn == 9) // All moves made
            {
                printf("Tie!\n");
                break;
            }

            // Alternate player move
            if (turn % 2 == 0)
            {
                sign = 'X';
                printf("Your move (1-9): ");

                // Read input and check for valid number
                int move = readMove(pos);
                if (move != -1) // 1-9 is valid
                {
                    pos[move - 1] = 'X'; // Accept player input
                }
                else
                {
                    continue; // Invalid move, skip turn
                }
            }
            else
            {
                sign = 'O';
                printf("Computer's turn...\n");
                sleep(1);
                pos[computerMove(pos, turn, difficulty)] = sign;
            }
            // Check for win condition
            if (winCondition(pos, sign))
            {
                system("clear");
                drawBoard(pos);
                (turn % 2 == 0) ? printf("You have won!\n") : printf("Computer has won!\n");
                break;
            }
            turn++;
        }

        printf("Play again? y/n: ");
        // while (getchar() != '\n'); // clear buffer
        char input;
        scanf(" %c", &input);
        while (input != 'y' && input != 'n')
        {
            printf("Please enter y or n: ");
            scanf(" %c", &input);
        }

        if (input == 'y')
        {
            turn = 0;
            clearBoard(pos);
        }
        else
        {
            return 0;
        }
    }
    return 0;
}

void drawBoard(char pos[])
{
    printf("\n %c | %c | %c \n", pos[0], pos[1], pos[2]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n", pos[3], pos[4], pos[5]);
    printf("---+---+---\n");
    printf(" %c | %c | %c \n\n", pos[6], pos[7], pos[8]);
}
char *clearBoard(char pos[])
{
    // Clear the board by setting all positions to ' '
    for (int i = 0; i < 9; i++)
    {
        pos[i] = ' ';
    }
}

int readMove(char pos[])
{
    int index = -1; // Initialize index to an invalid value
    // Check if input is valid
    if (scanf("%d", &index) != 1)
    {
        printf("Invalid input. Please enter a number between 1 and 9.\n");
        printf("Press Enter to continue...");
        clearBuffer();
        getchar(); // Wait for Enter key
        return -1; // Return invalid index
    }
    clearBuffer();
    // Check if valid input
    if (index < 1 || index > 9)
    {
        printf("Invalid input! Enter 1-9.\n");
        printf("Press Enter to continue...");
        getchar(); // Wait for Enter key
        return -1; // Return invalid index
    }
    // Check if position is occupied
    if (pos[index - 1] == 'X' || pos[index - 1] == 'O')
    {
        printf("Position already taken!\n");
        printf("Press Enter to continue...");
        getchar(); // Wait for Enter key
        return -1; // Return invalid index
    }
    return index; // Return valid index (0-8)
}
void clearBuffer()
{
    // Clear input buffer
    while (getchar() != '\n')
        ;
}
bool winCondition(char pos[], char sign)
{
    // Check for horizontal wins
    for (int i = 0; i < 7; i += 3)
    {
        if (pos[i] == sign && pos[i + 1] == sign && pos[i + 2] == sign)
        {
            return true;
        }
    }
    // Check for vertical wins
    for (int i = 0; i < 3; i++)
    {
        if (pos[i] == sign && pos[i + 3] == sign && pos[i + 6] == sign)
        {
            return true;
        }
    }
    // Check for diagonal wins
    if (pos[0] == sign && pos[4] == sign && pos[8] == sign || pos[2] == sign && pos[4] == sign && pos[6] == sign)
    {
        return true;
    }
    // If no wins, game continues
    return false;
}
int computerMove(char pos[], int turn, int difficulty)
{
    int size = 9 - turn;

    // Allocate array for available moves
    int *availableMoves = malloc(size * sizeof(int));

    // Collect indices of empty positions
    // printf("Available moves: ");
    int index = 0;
    for (int i = 0; i < 9; i++)
    {
        if (pos[i] == ' ')
        {
            availableMoves[index] = i;
            // printf("%d ", i + 1);
            index++;
        }
    }
    printf("\n");
    int move = -1; // Default move if no winning move found
    switch (difficulty)
    {
    case 1:
        return randomMove(size, availableMoves);
    case 2:
        // Check for winning move
        move = checkMovesOneDeep(pos, size, availableMoves, 'O');
        if (move != -1)
        {
            return move; // Return winning move if found
        }
        // Check for losing move
        move = checkMovesOneDeep(pos, size, availableMoves, 'X');
        if (move != -1)
        {
            return move; // Return losing move if found
        }
        // If no winning or losing move, choose randomly
        return randomMove(size, availableMoves);
    case 3:
        // Check for winning move
        move = checkMovesOneDeep(pos, size, availableMoves, 'O');
        if (move != -1)
        {
            return move; // Return winning move if found
        }
        // Check for losing move
        move = checkMovesOneDeep(pos, size, availableMoves, 'X');
        if (move != -1)
        {
            return move; // Return losing move if found
        }
        // Check for losing move two moves ahead
        move = checkMovesTwoDeep(pos, size, availableMoves, 'X');
        if (move != -1)
        {
            return move; // Return losing move if found
        }
        // Check for winning move two moves ahead
        move = checkMovesTwoDeep(pos, size, availableMoves, 'O');
        if (move != -1)
        {
            return move; // Return winning move if found
        }
        // If no winning or losing move, choose randomly
        return randomMove(size, availableMoves);
    case 4:
        if (pos[4] == ' '){
            return 4;
        }
        // Check for winning move
        move = checkMovesOneDeep(pos, size, availableMoves, 'O');
        if (move != -1)
        {
            return move; // Return winning move if found
        }
        // Check for losing move
        move = checkMovesOneDeep(pos, size, availableMoves, 'X');
        if (move != -1)
        {
            return move; // Return losing move if found
        }
        // Check for losing move two moves ahead
        move = checkMovesTwoDeep(pos, size, availableMoves, 'X');
        if (move != -1)
        {
            return move; // Return losing move if found
        }
        // Check for winning move two moves ahead
        move = checkMovesTwoDeep(pos, size, availableMoves, 'O');
        if (move != -1)
        {
            return move; // Return winning move if found
        }
        // If no winning or losing move, choose randomly
        return randomMove(size, availableMoves);
    default:
        break;
    }
}
int randomMove(int size, int *availableMoves)
{
    int move = availableMoves[rand() % size];
    free(availableMoves);
    return move;
}
int checkMovesOneDeep(char pos[], int size, int *availableMoves, char sign)
{
    int move = -1; // Default move if no winning move found
    for (int i = 0; i < size; i++)
    {
        pos[availableMoves[i]] = sign; // Temporarily place 'O'
        if (winCondition(pos, sign))
        {
            move = availableMoves[i];
            pos[availableMoves[i]] = ' '; // Reset position
            free(availableMoves);
            return move;
        }
        pos[availableMoves[i]] = ' '; // Reset position
    }
    return move; // No winning move found
}
int checkMovesTwoDeep(char pos[], int size, int *availableMoves, char sign)
{
    int move = -1; // Default move if no winning move found
    for (int i = 0; i < size; i++)
    {
        pos[availableMoves[i]] = sign; // Temporarily place move
        // Check two moves ahead for losing move
        for (int j = 0; j < size; j++)
        {
            if (availableMoves[j] == availableMoves[i])
            {
                continue; // Skip the same move
            }
            pos[availableMoves[j]] = sign; // Temporarily place move
            if (winCondition(pos, sign))
            {
                move = availableMoves[i];
                pos[availableMoves[i]] = ' '; // Reset position
                pos[availableMoves[j]] = ' '; // Reset position
                free(availableMoves);
                return move;
            }
            pos[availableMoves[j]] = ' '; // Reset position
        }
        pos[availableMoves[i]] = ' '; // Reset position
    }
    return move; // No winning move found
}