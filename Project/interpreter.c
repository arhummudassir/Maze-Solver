#include <stdio.h>
#include <stdlib.h>

#include "ant.h"
#include "memory.h"
#include "interpreter.h"

#define MAX_NUMBER_OF_STEPS 300

/*
    The program is a file scanner that reads through the intelligence file and transcribes the FSM
    into a 2d array as well as 

*/

/* Function prototypes */
void findNum(FILE *intelligence, int *num);
void printintelligence(int** instructions, int rows, int width);
void do_Nothing(void);

void do_Nothing(void) {};

/* This function list is the output table for the FSM */
void (*output[])() = {
    do_Nothing,
    move_l,
    move_r,
    move_f,
    move_b,
    backtrack,
};

/*
    Runs the interpreter and state machine
*/
void run_interpreter(FILE *intelligence)
{

    printf("\nInterpreter is running");

    // Read first row for number of rows
    int numRows;
    findNum(intelligence, &numRows);

    // Read second row for number of cols
    int numCols;
    findNum(intelligence, &numCols);

    // Declare dynamic 2d array to store FSM

    int **next_state_table = (int**)malloc(numRows * sizeof(int*));
    for (int i = 0; i < numRows; i++)
    {
        next_state_table[i] = (int*)malloc(numCols * sizeof(int));
    }

    /* Initialize array for good measure */
    for (int i = 0; i < numRows; i++)
    {
        for (int j = 0; j < numCols; j++)
        {
            next_state_table[i][j] = 0;
        }
    }


    /*
        Read through intelligence file to transcribe the FSM into a 2d array
        S denotes a state and the number after it denotes the value
        SN or state NULL is given the value 0; The number has to be right 
        after 'S' for this to work correctly
    */
    for (int i = 0; i < numRows; i++)
    {
        int col_Index = 0;
        char c; 
        while ((c = fgetc(intelligence)) != '\n')
        {
            if (c == 'S')
            {
                int val = (char)fgetc(intelligence) - (char)'0';
                next_state_table[i][col_Index] = val;
                col_Index++;
            }
        }
    }

    printintelligence(next_state_table, numRows, numCols);

    int currentState = 0;
    int nextState = 0;

    /* Keep running the FSM until the maze is complete */
    /* Max iteration to stop program running if maze is unsolvable */
    int tempIndex = 0;
    while (!(isMazeComplete()) && tempIndex < MAX_NUMBER_OF_STEPS)
    {
        int currentState = nextState;
        int col;

        resetItch();

        // Check left, right, forward, and backwards 
        cwl();
        cwr();
        cwf();
        cwb();

        if (getLeft_itch())
        {
            printf("\n>>Interpreter has seen left itch");
            col = 0;
        } 
        else if (getRight_itch())
        {
            printf("\n>>Interpreter has seen right itch");
            col = 1;
        } 
        else if (getForward_itch())
        {
            printf("\n>>Interpreter has seen forward itch");
            col = 2;
        }
        else if (getBack_itch())
        {
            printf("\n>>Interpreter has seen back itch");
            col = 3;
        }
        else
        {
            printf("\nNo itch seen, using backtrack");
            col = 4;
        }

        int x;
        int y;

        getCurCol(&y);
        getCurRow(&x);

        nextState = next_state_table[currentState][col];

        printf("\nCurrent Position %d , %d" , x, y);
        
        printf("\nState machine Next State : %d", nextState);
        printf("\n");
        printStack();
        printMaze();
        printf("\nCurrent Iteration : %d" , tempIndex);

        output[nextState]();
        tempIndex++;

    }

    //printf("\nMaze completed");

}

void printintelligence(int** instructions, int rows, int width)
{

    printf("\n");
    printf("---------------------- Micheals intelligence ----------------------");
    printf("\n");

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < width; j++)
        {
            printf("%d" , instructions[i][j]);
        }

        printf("\n");
    }

    printf("\n");
    printf("--------------------------------------------------------------------");
    printf("\n");
}

void findNum(FILE *intelligence, int *num)
{
    // Read a row of the file until \0 is hit, read and store the number
    // I can do this because there is a defined file format
    char c;
    char number[4];
    int index = 0;
    while ((c = fgetc(intelligence)) != '\n')
    {
        number[index] = c;
        index++;
    }

    //  Manually add null terminate to avoid funky behavior
    number[index+1] = '\0';

    // Convert number string to an int value
    int numRows = atoi(number);
    *num = numRows;
}