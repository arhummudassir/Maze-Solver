/*
    ADT that represents the VA's memory implemented as a queue of Strings

    String Format 
    [0] = xPosition;
    [1] = yPosition;
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "memory.h"

#define MAX_SIZE 1000

int top = -1;

Memory_t mem[MAX_SIZE];

void push(int x, int y, bool markPheremone) 
{
    top++;
    mem[top].xCoord = x;
    mem[top].yCoord = y;
    mem[top].isNull = false;
    mem[top].isPheremone = markPheremone;
}

void pop(int *x, int *y, bool *isMarked) 
{
    *x = mem[top].xCoord;
    *y = mem[top].yCoord;
    *isMarked = mem[top].isPheremone;
    mem[top].isNull = true;
    top--;
}

void peek(Memory_t *data_out) 
{
    data_out = &mem[top];
}

bool isMarked(int x, int y)
{
    for (int i = 0; i < top; i++)
    {
        if (mem[i].xCoord == x && mem[i].yCoord == y)
        {
            if (mem[i].isPheremone)
            {
                return true;
            }
        }
    }
}

/*
    Sets all structs back to default values and marks it as a null struct
*/
void clear()
{
    top = -1;

    for (int i = 0; i < MAX_SIZE; i++)
    {
        mem[i].xCoord = -1;
        mem[i].yCoord = -1;
        mem[i].isPheremone = false;
        mem[i].isNull = true;
    }
}

void printStack()
{
    printf("\n------------ Stack ----------------");

    for (int i = 0; i < top; i++)
    {
        printf("\n X coord : %d Y coord : %d Is marked %d" , mem[i].xCoord, mem[i].yCoord, mem[i].isPheremone);
    }
}

bool is_empty() 
{
    return (top == -1);
}

bool is_full() 
{
    return (top == MAX_SIZE - 1);
}