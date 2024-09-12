#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#include "ant.h"
#include "memory.h"

#define MAX_SIZE 100

int row;
int col;

// TODO: Implement a way to find start and end coordinates
int currow ;
int curcol;
int itch;

// TODO: Implement a way to find the exit coordinates
int exit_X;
int exit_Y;

bool itch_r;
bool itch_l;
bool itch_b;
bool itch_f;

FILE *out_f;

char maze[MAX_MAZE_LENGTH][MAX_MAZE_LENGTH];

void setStart(int x, int y)
{
    currow = x;
    curcol = y;
}

void setEnd(int x, int y)
{
    exit_X = x;
    exit_Y = y;
}

void setOutputFilePtr(FILE *file)
{
    out_f = file;
}

void readMaze(FILE *maze_text)
{
    // Read maze
    char c;
    while ((c = fgetc(maze_text)) != EOF && row < MAX_SIZE) { 
        if (c != '\n') {
            maze[row][col] = c;
            col++;
        } else {
            row++;
            col = 0;
        }
    }

    //fclose(inp_f);

    // Mark starting point
    mark();

    /* Print the maze */
    printMaze();
    
}

void printMaze()
{
    printf("Maze:\n");
    for(int i = 0; i <= row; i++)
    {
        for(int j = 0; j < col; j++)
        {
            printf("%c ", maze[i][j]);
        }
        printf("\n");
    }
}

void getCurCol(int *var)
{
    *var = curcol;
}

void getCurRow(int *var)
{
    *var = currow;
}

bool getLeft_itch()
{
    return itch_l;
}

bool getRight_itch()
{
    return itch_r;
}

bool getForward_itch()
{
    return itch_f;
}

bool getBack_itch()
{
    return itch_b;
}

bool isMazeComplete()
{
    if ((currow == exit_X) && (curcol == exit_Y))
    {
        printf("\n ----------------- MAZE COMPLETE ---------------------");
        return 1;
    }
}

void resetItch()
{
    itch_r = 0;
    itch_l = 0;
    itch_b = 0;
    itch_f = 0;
}

void mark() {
    maze[currow][curcol] = '+';
    fprintf(out_f,"MARK\n");
}

void move_f() {
    mark();
    currow++;
    push(currow, curcol, true);
    printf("\nMoving forward");
    fprintf(out_f,"MOVE_F\nMARK\n");
}

void move_b() {
    mark();
    currow--;
    push(currow, curcol, true);
    printf("\nMoving backward");
    fprintf(out_f,"MOVE_B\nMARK\n");
}

void move_l() {
    mark();
    curcol--;
    push(currow, curcol, true);
    printf("\nMoving left");
    fprintf(out_f,"MOVE_L\nMARK\n");
}

void move_r() {
    mark();
    curcol++;
    push(currow, curcol, true);
    printf("\nMoving right");
    fprintf(out_f,"MOVE_R\nMARK\n");
}

void cwl() {
    itch_l = 0;

    if (maze[currow][curcol - 1] != '*' && maze[currow][curcol - 1] != '+') 
    {
        // if (!(isMarked(currow, curcol - 1)))
        // {
            printf("\nLeft character seen %c" , maze[currow][curcol - 1]);
            itch_l = 1;
        //}       
    }

    // itch = 0;
    // for (int i = 0; i < MAX_MAZE_LENGTH; i++) {
    //     if (curcol - i != '*' || curcol - i != '+') 
    //         itch++;
    // }

    fprintf(out_f,"CWL\n");
}

void cwr() {
    itch_r = 0;

    if (maze[currow][curcol + 1] != '*' && maze[currow][curcol + 1] != '+') 
    {
        // if (!(isMarked(currow, curcol + 1)))
        // {
            printf("\nRight character seen %c" , maze[currow][curcol + 1]);
            itch_r = 1;
        //}       
    }

    // itch = 0;
    // for (int i = 0; i < MAX_MAZE_LENGTH; i++) {
    //     if (curcol + i != '*' || curcol + i != '+') 
    //         itch++;
    // }

    fprintf(out_f,"CWR\n");
}

void cwf() {
    itch_f = 0;

    if (maze[currow + 1][curcol] != '*' && maze[currow + 1][curcol] != '+') 
    {
        // if (!(isMarked(currow + 1, curcol)))
        // {
            itch_f = 1;
        //}       
    }

    // itch = 0;
    // for (int i = 0; i < MAX_MAZE_LENGTH; i++) {
    //     if (currow + i != '*' || currow + i != '+') 
    //         itch++;
    // }

    fprintf(out_f,"CWF\n");
}

void cwb() {
    itch_b = 0;

    if (maze[currow - 1][curcol] != '*' && maze[currow - 1][curcol] != '+') 
    {
        // if (!(isMarked(currow - 1, curcol)))
        // {
            itch_b = 1;
        //}       
    }

    // itch = 0;
    // for (int i = 0; i < MAX_MAZE_LENGTH; i++) {
    //     if (currow - i != '*' || currow +- i != '+') 
    //         itch++;
    // }

    fprintf(out_f,"CWB\n");
}

void bjpi() {
    if(cwl)
        curcol -= itch;
    else if(cwr)
        curcol += itch;
    else if(cwf)
        currow += itch;
    else if(cwb)
        currow -= itch;

    itch = 0;

    fprintf(out_f,"BJPI\n");
}

void cjpi() {
    if(cwl)
        curcol -= 1;
    else if(cwr)
        curcol += 1;
    else if(cwf)
        currow += 1;
    else if(cwb)
        currow -= 1;
    
    itch = 0;

    fprintf(out_f,"CJPI\n");
}

void backtrack() {
    
    int x;
    int y;
    bool isMarked;

    pop(&x, &y, &isMarked); 

    currow = x;
    curcol = y;

    printf("\n------ Back tracking func call ----------");
    
    fprintf(out_f,"BACKTRACK\n");
}

void rp(int n, int t) {
    fprintf(out_f,"RP: ");

    for(int i = 0; i < t; i++)
    {
        for(int j = 0; j < n; j++)
        {
            switch(n)
            {
                case 1: move_f();
                    fprintf(out_f,"MOVE_F ");
                    break;
                case 2: move_b(); 
                    fprintf(out_f,"MOVE_B ");
                    break;
                case 3: move_l(); 
                    fprintf(out_f,"MOVE_L ");
                    break;
                case 4: move_r();
                    fprintf(out_f,"MOVE_R ");
                    break;
                default:
                    break;
            }
        }
    }
    fprintf(out_f,"\n");
}