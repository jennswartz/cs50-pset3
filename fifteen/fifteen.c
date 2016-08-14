/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */

#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9
#define EMPTY_TILE 0

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// initialize tile coordinates
int x;
int y;


// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();

        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(500000);
        }

        // sleep thread for animation's sake
        usleep(500000);
    }

    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(2000000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).
 */



void init(void)
{
    // Initialize variable fill_grid that stores value to begin populating the grid (one less than d * d)
    int fill_grid = (d * d) - 1;

    // Set values of x and y, which will be the x and y axis coordinates used when making moves
    x = d - 1;
    y = d - 1;

    // Create outer loop and inner loop to interate through and create 2D array [row][column]; use numbers in fill_grid to populate the array
    for(int row = 0; row < d; row++)
    {
        for(int column = 0; column < d; column++)
        {
            board[row][column] = fill_grid;
            fill_grid--;
        }
    }
    // If the height and width are even, swap numbers one and two
    if ((d * d) % 2 == 0)
    {
        int swap = board[d - 1][d - 2];
        board[d - 1][d - 2] = board[d - 1][d - 3];
        board[d - 1][d - 3] = swap;
    }
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{

    // Create two loops to print the board[row][column]
    for(int row = 0; row < d; row++)
    {
        for(int column = 0; column < d; column++)
        {
            // If the values are greater than zero, print with empty space padding
            if(board[row][column] > EMPTY_TILE)
            {
                printf(" %2d ", board[row][column]);
            }

            // If the value is zero, print _ placeholder.
            else if(board[row][column] == EMPTY_TILE)
            {
                printf(" __");
            }
        }
        // print line break after reach row so format is a box
        printf("\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false.
 */

bool move(int tile)
{

    // Create two loops to iterate over board[row][column]
    for(int row = 0; row < d; row++)
    {
        for(int column = 0; column < d; column++)
        {
            // Find the tile that equals the board[row][column]
            if (board[row][column] == tile)
            {

                // Look to see if the empty space is down, up, left or right
                if (((row == x) && (column == y - 1 || column == y + 1)) || ((column == y) && (row == x - 1 || row == x + 1)))
                {

                    // Swap tile and the zero; reset values of x and y;
                    board[x][y] = tile;
                    board[row][column] = EMPTY_TILE;
                    x = row;
                    y = column;
                    return true;
                }
            }
        }
    }
    return false;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration),
 * else false.
 */
bool won(void)
{
    // Set variable for filling grid starting at one and increasing each loop
    int fill_grid = 1;

    // Create two loops for column and row
    for(int row = 0; row < d; row++)
    {
        for(int column = 0; column < d; column++)
        {
            // Check the values in the board array to the grid values in fill_grid; checks that zero tile is in correct place
            if(board[row][column] == fill_grid)
            {
                fill_grid++;

                if(fill_grid == d * d && board[d - 1][d - 1] == 0)
                {
                    return true;
                }
            }
        }
    }
    return false;
}