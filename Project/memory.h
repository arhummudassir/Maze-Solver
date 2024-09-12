#ifndef MEMORY_H
#define MEMORY_H

#include <stdbool.h>

typedef struct{
    int xCoord;
    int yCoord;
    bool isPheremone;
    bool isNull;
} Memory_t;

void push(int x, int y, bool markPheremone); 
void pop(int *x, int *y, bool *isMarked);
void peek(Memory_t *data_out);
void clear();
bool is_empty();
bool is_full();
bool isMarked(int x, int y);
void printStack();

#endif