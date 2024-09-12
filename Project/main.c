/*
    Arhum Mudassir
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ant.h"
#include "memory.h"
#include "interpreter.h"

int main()
{
    /* Opens Maze file*/ 
    /* Opens Michael's Intelligence file*/
    /* Opens Output file where all the actions performed by Michael are stored chronologically*/

    FILE *inp_f = fopen("maze.txt", "r");
    if (inp_f == NULL) 
    {
        printf("Error: File maze.txt cannot be opened\n");
        exit(1);
    }

    FILE *intel_f = fopen("Intelligence.txt", "r");
    if (intel_f == NULL) 
    {
        printf("Error: File Intelligence.txt cannot be opened\n");
        exit(1);
    }

    FILE *out_f = fopen("output.txt", "w");
    if(out_f == NULL)
    {
        printf("Error: File output.txt cannot be opened\n");
        exit(1);
    }

    setOutputFilePtr(out_f);

    /* Reads the maze from the maze text file and transcribes it to an array*/
    /* The maze character array is stored in ant.c */
    readMaze(inp_f);

    int start_x;
    int start_y;
    int end_x;
    int end_y;

    printf("\nTop Left is (X,Y) = (0,0) and Bottom Right is (x,y) = (X_Max, Y_Max)");
    printf("\nInput Starting Position X Coord: ");
    scanf("%d", &start_x); getchar();

    printf("\nInput Starting Position Y Coord: ");
    scanf("%d", &start_y); getchar();

    printf("\nInput Ending Position X Coord: ");
    scanf("%d", &end_x); getchar();

    printf("\nInput Ending Position Y Coord: ");
    scanf("%d", &end_y); getchar();

    setStart(start_x, start_y);
    setEnd(end_x, end_y);

    run_interpreter(intel_f);

    fclose(inp_f);
    fclose(intel_f);
    fclose(out_f);

    //return 0;
}