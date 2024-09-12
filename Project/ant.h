#ifndef ANT_H
#define ANT_H

#include <stdbool.h>

#define MAX_MAZE_LENGTH 100

void setOutputFilePtr(FILE *file);
void printMaze();

void mark();
void move_f();
void move_b();
void move_l();
void move_r();
void cwl();
void cwr();
void cwf();
void cwb();

void resetItch();

bool getLeft_itch();
bool getRight_itch();
bool getForward_itch();
bool getBack_itch();

void bjpi();
void cjpi();
void backtrack();
void rp(int n, int t);
bool isMazeComplete();

void readMaze(FILE *maze_text);

void getCurCol(int *var);
void getCurRow(int *var);

void setStart(int x, int y);
void setEnd(int x, int y);

#endif