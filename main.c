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

    // Initialize positions with numbers 1-9
    for (int i = 0; i < 9; i++)
    {
        pos[i] = i + '1';
    }
    int index;
    int difficulty;
    srand(time(NULL)); // seed rand() with time

    while (true)
    {
        system("clear");
        printf("TIC TAC TOE\n");
        drawBoard(pos);
        for (int i = 0; i < 9; i++)
        {
            pos[i] = ' ';
        }
        // Difficulty setting
        printf("Choose a difficulty for opponent\n");
        printf("Easy (1), Normal (2), Hard (3): ");
        while (scanf("%d", &difficulty) != 1 || difficulty < 1 || difficulty > 3)
        {
            printf("Invalid input. Please enter 1, 2, or 3: ");
            while (getchar() != '\n')
                ;
        }
        while (getchar() != '\n')
            ;

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
                    printf("Position already taken!\n");
                    printf("Press Enter to continue...");
                    getchar(); // Wait for Enter key
                    continue;
                }
                // Accept player input
                pos[index - 1] = 'X';
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
                if (turn % 2 == 0)
                {
                    printf("You have won!\n");
                }
                else
                {
                    printf("You lost!\n");
                }
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

    // printf("Choosing move: ");
    int move = 0;
    switch (difficulty)
    {
    case 1:
        move = availableMoves[rand() % size];
        free(availableMoves);
        return move;
    case 2:
        // Check for winning move
        for (int i = 0; i < size; i++)
        {
            pos[availableMoves[i]] = 'O'; // Temporarily place 'O'
            if (winCondition(pos, 'O'))
            {
                move = availableMoves[i];
                pos[availableMoves[i]] = ' '; // Reset position
                free(availableMoves);
                return move;
            }
            pos[availableMoves[i]] = ' '; // Reset position
        }
        // Check for losing move
        for (int i = 0; i < size; i++)
        {
            pos[availableMoves[i]] = 'X'; // Temporarily place 'X'
            if (winCondition(pos, 'X'))
            {
                move = availableMoves[i];
                pos[availableMoves[i]] = ' '; // Reset position
                free(availableMoves);
                return move;
            }
            pos[availableMoves[i]] = ' '; // Reset position
        }
        // If no winning or losing move, choose randomly
        move = availableMoves[rand() % size];
        free(availableMoves);
        return move;
    case 3:
        // Check for winning move 1 move ahead
        for (int i = 0; i < size; i++)
        {
            pos[availableMoves[i]] = 'O'; // Temporarily place 'O'
            if (winCondition(pos, 'O'))
            {
                move = availableMoves[i];
                pos[availableMoves[i]] = ' '; // Reset position
                free(availableMoves);
                return move;
            }
            pos[availableMoves[i]] = ' '; // Reset position
        }
        // Check for losing move 1 move ahead
        for (int i = 0; i < size; i++)
        {
            pos[availableMoves[i]] = 'X'; // Temporarily place 'X'
            if (winCondition(pos, 'X'))
            {
                move = availableMoves[i];
                pos[availableMoves[i]] = ' '; // Reset position
                free(availableMoves);
                return move;
            }
            pos[availableMoves[i]] = ' '; // Reset position
        }
        // Check for losing move two moves ahead
        for (int i = 0; i < size; i++){
            pos[availableMoves[i]] = 'X'; // Temporarily place 'O'
            // Check two moves ahead for losing move
            for (int j = 0; j < size; j++)
            {
                if (availableMoves[j] == availableMoves[i])
                {
                    continue; // Skip the same move
                }
                pos[availableMoves[j]] = 'X'; // Temporarily place 'O'
                if (winCondition(pos, 'X'))
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
        // Check for winning move two moves ahead
        for (int i = 0; i < size; i++)
        {
            pos[availableMoves[i]] = 'O'; // Temporarily place 'O'
            // Check two moves ahead for winning move
            for (int j = 0; j < size; j++)
            {
                if (availableMoves[j] == availableMoves[i])
                    continue;                 // Skip the same move
                pos[availableMoves[j]] = 'O'; // Temporarily place 'O'
                if (winCondition(pos, 'O'))
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
        // If no winning or losing move, choose randomly
        move = availableMoves[rand() % size];
        free(availableMoves);
        return move;
    default:
        break;
    }
}