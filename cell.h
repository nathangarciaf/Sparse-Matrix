#ifndef CELL_H
#define CELL_H
#include <stdio.h>
#include <stdlib.h>

typedef struct cell
{
    struct cell *prox_linha; 
    struct cell *prox_coluna;
    float valor;
    int coluna,linha;
} Cell;

Cell * cell_create(int lin, int col, float v);
Cell * _cell_get(Cell* c, int col);
void _cell_trade_value(Cell* c, int col, float v);
void cell_print(Cell* n);
void cell_destroy(Cell * n);
#endif