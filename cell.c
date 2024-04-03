#include "cell.h"

Cell * cell_create(int lin, int col, float v)
{
    Cell * c = (Cell*)malloc(1 * sizeof(Cell));
    c->coluna = col;
    c->linha = lin;
    c->prox_coluna = NULL;
    c->prox_linha = NULL;
    c->valor = v;
    return c;
}

void _cell_trade_value(Cell* c, int col, float v){
    while(c != NULL){
        if(c->coluna == col){
            c->valor = v;
        }
        c = c->prox_coluna;
    }
}

Cell* _cell_get(Cell* c, int col){
    while(c != NULL){
        if(c->coluna == col){
            return c;
        }
        c = c->prox_coluna;
    }
    return 0;
}

void cell_print(Cell* c)
{
    printf("Celula %dx%d: %.2f\n",c->linha,c->coluna,c->valor);
}

void cell_destroy(Cell * c)
{
    free(c);
}