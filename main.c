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
bool winCondition(char pos[], char sign);
int computerMove(char pos[], int turn, int difficulty);

int main()
{
    int turn = 0;
    char sign;
    char pos[9];
    for (int i = 0; i < 9; i++)
    {
        pos[i] = i + '1';
    }
    int index;
    int difficulty;
    srand(time(NULL)); // seed rand() with time

    printf("TIC TAC TOE\n");
    drawBoard(pos);
    for (int i = 0; i < 9; i++)
    {
        pos[i] = ' ';
    }
    while (true)
    {
        // Difficulty setting
        printf("Choose a difficulty for opponent\n");
        printf("Easy (1), Normal (2), Hard (3): ");
        scanf("%d", &difficulty);

        // Game loop
        while (true)
        {
            // system("cls");
            drawBoard(pos);

            if (turn == 9) // All moves made
            {
                printf("Tie!\n");
                return 0;
            }
            // Alternate player move
            if (turn % 2 == 0)
            {
                sign = 'X';
                printf("Your move (1-9): ");

                // Read input and check for valid number
                if (scanf("%d", &index) != 1)
                {
                    printf("Invalid input. Please enter a number between 1 and 9.\n");
                    printf("Press Enter to continue...");
                    while (getchar() != '\n')
                        ;      // Clear input buffer
                    getchar(); // Wait for Enter key
                    continue;
                }
                while (getchar() != '\n')
                    ; // Clear input buffer

                // Check if valid input
                if (index < 1 || index > 9)
                {
                    printf("Invalid input! Enter 1-9.\n");
                    printf("Press Enter to continue...");
                    getchar(); // Wait for Enter key
                    continue;
                }
                // Check if position is occupied
                if (pos[index - 1] == 'X' || pos[index - 1] == 'O')
                {
                    printf("Position already taken!");
                    printf("Press Enter to continue...");
                    getchar(); // Wait for Enter key
                    continue;
                }
                // Accept player input
                pos[index - 1] = sign;
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
                drawBoard(pos);
                if (turn % 2 == 0)
                {
                    printf("You have won!\n");
                }
                else
                {
                    printf("You lost!\n");
                }
                return 0;
            }
            turn++;
        }

        printf("Play again? y/n: ");
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
            for (int i = 0; i < 9; i++)
            {
                pos[i] = ' ';
            }
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
bool winCondition(char pos[], char sign)
{
    // Check for horizontal wins
    for (int i = 0; i < 7; i+=3)
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
    int size=9-turn;
    
    // Allocate array for available moves
    int* availableMoves = malloc(size * sizeof(int));     

    // Collect indices of empty positions
    // printf("Available moves: ");
    int index = 0;
    for (int i = 0; i < 9; i++) {
        if (pos[i] == ' ') {
            availableMoves[index] = i;
            // printf("%d ", i + 1);
            index++;
        }
    }
    printf("\n");

    // printf("Choosing move: ");
    int move = 0;
    switch(difficulty)
    {
    case 1:
        move = availableMoves[rand() % size];
        // printf("%d \n", move + 1);
        return move;
    case 2:
        move = availableMoves[rand() % size];
        // printf("%d \n", move + 1);
        return move;
    case 3:
        move = availableMoves[rand() % size];
        // printf("%d \n", move + 1);
        return move;
    default:
        break;
    }
}
