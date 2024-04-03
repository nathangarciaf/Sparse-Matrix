#ifndef MATRIZ_H
#define MATRIZ_H

#include "cell.h"

typedef struct matriz{
    int qtd_linhas, qtd_colunas;
    Cell **colunas, **linhas;
} Matriz;

//O(n*j), inserção em uma lista encadeada é O(1) caso seja feito a esquerda, e caso seja feita a direita, temos como O(n), tendo n como numero de itens da lista encadeada, e como fazemos isso j vezes, sendo j o numero de valores, temos a complexidade de O(n*j)
Matriz* matriz_read_bin();

//O(2n), criar uma matriz e inicializar todas as cabeças das listas encadeadas como NULL
Matriz *matriz_create();

//O(n^3), no pior caso, criamos e inicializamos uma matriz, com isso, temos n listas encadeadas, que serão adicionados os itens de uma matriz com n itens em uma nova matriz, com isso, temos O(n^3)
Matriz* matriz_scalar_multiplication(Matriz* m,float c);

//O(n^3), no pior caso, criamos e inicializamos uma matriz, com isso, temos n listas encadeadas, que serão adicionados os itens de uma matriz com n itens em uma nova matriz, com isso, temos O(n^3)
Matriz* matriz_sum_matriz(Matriz* m1,Matriz* m2);

//O(n^3), no pior caso, criamos e inicializamos uma matriz, com isso, temos n listas encadeadas, que serão multiplicados os itens de duas matrizes com n itens em uma nova matriz, com isso, temos O(n^3)
Matriz* matriz_mult_point_to_point(Matriz* m1,Matriz* m2);

//O(n^3), criamos e inicializamos uma matriz, percorremos n listas encadeadas, e cada lista adicionamos n itens de uma matriz ja existente em uma nova matriz
Matriz* matriz_transpose(Matriz* m);

//O(n^3), criamos e inicializamos uma matriz, percorremos n listas encadeadas, e cada lista adicionamos n itens de uma matriz ja existente em uma nova matriz
Matriz* matriz_multiplication(Matriz* m1, Matriz *m2);

//O(n^3), criamos e inicializamos uma matriz, percorremos n listas encadeadas a fim de achar duas para realizar a trocar, e inserimos n valores de uma matriz ja existente em uma nova
Matriz* matriz_swap_rows(Matriz* m,int lin1, int lin2);

//O(n^3), criamos e inicializamos uma matriz, percorremos n listas encadeadas a fim de achar duas para realizar a trocar, e inserimos n valores de uma matriz ja existente em uma nova
Matriz* matriz_swap_collum(Matriz* m,int col1, int col2);

//O(n^3), criamos e inicializamos uma matriz, percorremos n listas encadeadasr, e inserimos n valores de uma matriz ja existente em uma nova
Matriz* matriz_slice(Matriz* m, int l1, int c1, int l2, int c2);

/*O(n^3) + (O(n^2)+ O(n^2) + O(n^2) + O(n))* n^2, resumindo, O(n^3) eh da funcao matriz insert matriz, e a 
segunda parte eh a soma de todas as funcoes realizadas dentro de duas iteracoes com complexidade O(n^2)*/
Matriz* matriz_convolution(Matriz* m, Matriz* k);

//O(n), buscar um item dentro de uma lista encadeada e retornar o valor
float matriz_get_value(Matriz* m, int lin, int col);

//O(n*j), percorre n listas encadeadas com acesso a todos os j itens da lista
float _matriz_sum_cells(Matriz* m);

/*O(n^3), duas iteracoes para adicionar todos os valores n*n da matriz m_insert em m, e junto a complexidade
da funcao insert value, temos O(n^3)*/
void matriz_insert_matriz(Matriz*m,Matriz* m_insert, int lin_i, int col_i);

//O(n), percorremos uma lista encadeada de n itens até o final
void matriz_print_sparse(Matriz* m);

//O(n*j), percorremos uma lista encadeada inteira, n vezes (numero de listas encadeadas), portanto, tendo j como numero de itens na lista encadeada e tendo n listas encadeadas, temos O(n*j). No pior caso, tendo a matriz quadrada completamente preenchida, temos O(n^2)
void matriz_print_dense(Matriz* m);

//O(2n), pois dentro da função set collum e da função set row nós percorremos uma lista encadeada a fim de procurar se o endereço referente a celula em questão existe, ai inserimos o valor, e como ambas as funções agem do mesmo jeito, e cada uma é a procura de um item numa lista encadeada e logo em seguida insere, temos que cada uma é O(n), portanto ambas juntas temos O(2n).
void matriz_insert_value(Matriz * mat,int lin, int col, float valor);

//O(n), buscar um item dentro de uma lista encadeada, porem no melhor caso (lista encadeada vazia), temos O(1).
void _matriz_set_collum(Matriz * mat,Cell* n, int lin, int col);

//O(n), buscar um item dentro de uma lista encadeada, porem no melhor caso (lista encadeada vazia), temos O(1).
void _matriz_set_row(Matriz * mat,Cell* n, int lin, int col);

//O(n), percorremos uma lista encadeada de n itens até encontrar o item que desejamos para remove-lo

void _matriz_delete_cell(Matriz * mat,Cell* c, int lin, int col);

//O(n*j), percorremos uma lista encadeada inteira, n vezes (numero de listas encadeadas), portanto, tendo j como numero de itens na lista encadeada e tendo n listas encadeadas, temos O(n*j). No pior caso, tendo a matriz quadrada completamente preenchida, temos O(n^2)
void matriz_write_bin(Matriz* m);

//O(n^2), percorremos n listas encadeadas, e liberamos memorias dos n itens alocados
void matriz_destroy(Matriz *m);

#endif