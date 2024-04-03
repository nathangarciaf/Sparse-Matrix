#include "matriz.h"
#include <stdio.h>
#include <stdlib.h>

//O(n*j), inserção em uma lista encadeada é O(1) caso seja feito a esquerda, e caso seja feita a direita, temos como O(n), tendo n como numero de itens da lista encadeada, e como fazemos isso j vezes, sendo j o numero de valores, temos a complexidade de O(n*j)
Matriz* matriz_read_bin(char* path_matriz){
		FILE* file_matriz = fopen(path_matriz,"rb");
		int qtd_col = 0, qtd_lin = 0,col = 0, lin = 0;
		float v = 0;
		fread(&qtd_lin,sizeof(int),1,file_matriz);
		fread(&qtd_col,sizeof(int),1,file_matriz);
		Matriz* m = matriz_create(qtd_lin,qtd_col);
		while(!feof(file_matriz)){
				fread(&col,sizeof(int),1,file_matriz);
				fread(&lin,sizeof(int),1,file_matriz);
				fread(&v,sizeof(float),1,file_matriz);
				matriz_insert_value(m, lin, col,v);
		}
		fclose(file_matriz);
		return m;
}

//O(n), criar uma matriz e inicializar as cabeças de n listas encadeadas como NULL
Matriz* matriz_create(int linha, int coluna){
    Matriz* m = (Matriz*)malloc(1 * sizeof(Matriz));
    m->qtd_colunas = coluna;
    m->qtd_linhas = linha;

    m->colunas = (Cell**)malloc(sizeof(Cell*) * (coluna+1));
    for(int i = 0; i <= m->qtd_colunas; i++){
        m->colunas[i] = NULL;
    }
    
    m->linhas = (Cell**)malloc(sizeof(Cell*) * (linha+1));
    for(int j = 0; j <= m->qtd_linhas; j++){
        m->linhas[j] = NULL;
    }

    return m;
}

//O(n^2), no pior caso, temos n listas encadeadas, que serão adicionados os itens de uma matriz com n itens em uma nova matriz, com isso, temos O(n^3)
Matriz* matriz_scalar_multiplication(Matriz* m,float c){
    Matriz* mult = matriz_create(m->qtd_linhas,m->qtd_colunas);
    for(int i = 0; i < m->qtd_linhas; i++){
        Cell* celula_atual = m->linhas[i];
        while(celula_atual != NULL){
            matriz_insert_value(mult,celula_atual->linha,celula_atual->coluna,celula_atual->valor*c);
            celula_atual = celula_atual->prox_coluna;
        }
    }
    return mult;
}

//O(n^2), no pior caso, temos n listas encadeadas, que serão adicionados os itens de uma matriz com n itens em uma nova matriz, com isso, temos O(n^3)
Matriz* matriz_sum_matriz(Matriz* m1,Matriz* m2){
    if(m1->qtd_colunas != m2->qtd_colunas || m1->qtd_linhas != m2->qtd_linhas){
        printf("Impossivel somar as matrizes, tamanhos distintos!!!\n");
        exit(1);
    }

    Matriz* sum_m = matriz_create(m1->qtd_linhas,m1->qtd_colunas);
    for(int i = 0; i < m1->qtd_linhas; i++){
        Cell* save_m1 = m1->linhas[i];
        Cell* save_m2 = m2->linhas[i];

        while(save_m1 != NULL || save_m2 != NULL){
            if(save_m1 == NULL){
                matriz_insert_value(sum_m,i,save_m2->coluna,save_m2->valor);
                save_m2 = save_m2->prox_coluna;
                continue;
            }
            else if(save_m2 == NULL){
                matriz_insert_value(sum_m,i,save_m1->coluna,save_m1->valor);
                save_m1 = save_m1->prox_coluna;
                continue;
            }

            if(save_m2->coluna == save_m1->coluna){
                matriz_insert_value(sum_m,i,save_m1->coluna,save_m1->valor+save_m2->valor);
                save_m1 = save_m1->prox_coluna;
                save_m2 = save_m2->prox_coluna;
            }
            else{
                if(save_m1->coluna > save_m2->coluna){
                    matriz_insert_value(sum_m,i,save_m2->coluna,save_m2->valor);
                    save_m2 = save_m2->prox_coluna;
                }
                else{
                    matriz_insert_value(sum_m,i,save_m1->coluna,save_m1->valor);
                    save_m1 = save_m1->prox_coluna;
                }
            }
        }
    }
    return sum_m;
}

//O(n^2), no pior caso, temos n listas encadeadas, que serão multiplicados os itens de duas matrizes com n itens em uma nova matriz, com isso, temos O(n^3)
Matriz* matriz_mult_point_to_point(Matriz* m1,Matriz* m2){
    if(m1->qtd_colunas != m2->qtd_colunas || m1->qtd_linhas != m2->qtd_linhas){
        printf("Impossivel multiplicar as matrizes ponto a ponto, tamanhos distintos!!!\n");
        exit(1);
    }

    Matriz* multp_m = matriz_create(m1->qtd_linhas,m1->qtd_colunas);
    for(int i = 0; i < m1->qtd_colunas; i++){
        Cell* save_m1 = m1->linhas[i];
        Cell* save_m2 = m2->linhas[i];

        while(save_m1 != NULL && save_m2 != NULL){
            if(save_m2->coluna == save_m1->coluna){
                matriz_insert_value(multp_m,i,save_m1->coluna,save_m1->valor*save_m2->valor);
                save_m1 = save_m1->prox_coluna;
                save_m2 = save_m2->prox_coluna;
            }
            else{
                if(save_m1->coluna > save_m2->coluna){
                    save_m2 = save_m2->prox_coluna;
                }
                else{
                    save_m1 = save_m1->prox_coluna;
                }
            }
        }
    }
    return multp_m;
}

//O(n^2), percorremos n listas encadeadas, e cada lista adicionamos n itens de uma matriz ja existente em uma nova matriz
Matriz* matriz_transpose(Matriz* m){
    Matriz* trp_m = matriz_create(m->qtd_colunas,m->qtd_linhas);
    for(int i = 0; i < m->qtd_linhas; i++){
        Cell* save_m = m->linhas[i];
        while(save_m != NULL){
            matriz_insert_value(trp_m,save_m->coluna,save_m->linha,save_m->valor);
            save_m = save_m->prox_coluna;
        }
    }

    return trp_m;
}

//O(n^2), percorremos n listas encadeadas, e cada lista adicionamos n itens de uma matriz ja existente em uma nova matriz
Matriz* matriz_multiplication(Matriz* m1, Matriz *m2){
    if(m1->qtd_colunas != m2->qtd_linhas){
        printf("Impossivel multiplicar as matrizes, colunas de A sao diferentes das linhas de B\n");
        exit(1);
    }

    Matriz* mult = matriz_create(m1->qtd_linhas,m2->qtd_colunas);
    for(int i = 0; i < m1->qtd_linhas; i++){
        for(int j = 0; j < m2->qtd_colunas; j++){
            Cell* celula_m1 = m1->linhas[i];
            Cell* celula_m2 = m2->colunas[j];
            float valor_total = 0;
            while(celula_m1 != NULL && celula_m2 != NULL){
                if(celula_m1->coluna == celula_m2->linha){
                    valor_total += (celula_m1->valor*celula_m2->valor);
                    celula_m1 = celula_m1->prox_coluna;
                    celula_m2 = celula_m2->prox_linha;
                }
                else{
                    if(celula_m1->coluna > celula_m2->linha){
                        celula_m2 = celula_m2->prox_linha;
                    }
                    else{
                        celula_m1 = celula_m1->prox_coluna;
                    }
                }
            }
            matriz_insert_value(mult,i,j,valor_total);
        }
    }
    return mult;
}

//O(n^2), percorremos n listas encadeadas a fim de achar duas para realizar a trocar, e inserimos n valores de uma matriz ja existente em uma nova
Matriz* matriz_swap_rows(Matriz* m,int lin1, int lin2){
    if(lin1 > m->qtd_linhas-1 || lin2 > m->qtd_linhas-1){
        printf("Linha inexistente na matriz, impossivel realizar troca!\n");
        exit(1);
    }
    Matriz* sr_m = matriz_create(m->qtd_linhas,m->qtd_colunas);
    for(int i = 0; i < m->qtd_linhas; i++){
        if(i == lin1){
            Cell* celula_l2 = m->linhas[lin2];
            while(celula_l2 != NULL){
                matriz_insert_value(sr_m,lin1, celula_l2->coluna,celula_l2->valor);
                celula_l2 = celula_l2->prox_coluna;
            }
        }
        else if(i==lin2){
            Cell* celula_l1 = m->linhas[lin1];
            while(celula_l1 != NULL){
                matriz_insert_value(sr_m,lin2,celula_l1->coluna,celula_l1->valor);
                celula_l1 = celula_l1->prox_coluna;
            }
        }
        else{
            Cell* celula_atual = m->linhas[i];
            while(celula_atual != NULL){
                matriz_insert_value(sr_m,celula_atual->linha,celula_atual->coluna,celula_atual->valor);
                celula_atual = celula_atual->prox_coluna;
            }
        }
    }
    return sr_m;
}

//O(n^2), percorremos n listas encadeadas a fim de achar duas para realizar a trocar, e inserimos n valores de uma matriz ja existente em uma nova
Matriz* matriz_swap_collum(Matriz* m,int col1, int col2){
    Matriz* sc_m = matriz_create(m->qtd_linhas,m->qtd_colunas);
    if(col1 > m->qtd_colunas-1 || col1 > m->qtd_colunas-1){
        printf("Coluna inexistente na matriz, impossivel realizar troca!\n");
        exit(1);
    }

    for(int i = 0; i < m->qtd_colunas; i++){
        if(i == col1){
            Cell* celula_l2 = m->colunas[col2];
            while(celula_l2 != NULL){
                matriz_insert_value(sc_m,celula_l2->linha,col1,celula_l2->valor);
                celula_l2 = celula_l2->prox_linha;
            }
        }
        else if(i==col2){
            Cell* celula_l1 = m->colunas[col1];
            while(celula_l1 != NULL){
                matriz_insert_value(sc_m,celula_l1->linha,col2,celula_l1->valor);
                celula_l1 = celula_l1->prox_linha;
            }
        }
        else{
            Cell* celula_atual = m->colunas[i];
            while(celula_atual != NULL){
                matriz_insert_value(sc_m,celula_atual->linha,celula_atual->coluna,celula_atual->valor);
                celula_atual = celula_atual->prox_linha;
            }
        }
    }
    return sc_m;
}

//O(n^2), percorremos n listas encadeadasr, e inserimos n valores de uma matriz ja existente em uma nova
Matriz* matriz_slice(Matriz* m, int l1, int c1, int l2, int c2){
		if(c1 < 0 || l1 < 0 || c2 >= m->qtd_colunas || l2 >= m->qtd_linhas){
			printf("Pontos nos quais se deseja realizar o corte sao inexistentes na matriz!\n");
			exit(1);
		}
	
    Matriz* slice = matriz_create((l2+1)-l1,(c2+1)-c1);
    for(int i = l1; i <= l2; i++){
        Cell* celula_atual = m->linhas[i];
        while(celula_atual != NULL){
            if(celula_atual->coluna >= c1 && celula_atual->coluna <= c2){
                matriz_insert_value(slice,i - l1, (celula_atual->coluna - c1) ,celula_atual->valor);
            }
            celula_atual = celula_atual->prox_coluna;
        }
    }
    return slice;
}

/*O(n^3) + (O(n^2)+ O(n^2) + O(n^2) + O(n))* n^2, resumindo, O(n^3) eh da funcao matriz insert matriz, e a 
segunda parte eh a soma de todas as funcoes realizadas dentro de duas iteracoes com complexidade O(n^2)*/
Matriz* matriz_convolution(Matriz* m, Matriz* k){
    if(k->qtd_linhas % 2 == 0 || k->qtd_colunas % 2 == 0){
        printf("Impossivel gerar a convolucao, a linha ou a coluna do kernel eh par!\n");
        exit(1);
    }
    int lin_dif = (k->qtd_linhas-1)/2;
    int col_dif = (k->qtd_colunas-1)/2;
    Matriz* m_expand = matriz_create(m->qtd_linhas+(2*lin_dif), m->qtd_colunas+(2*col_dif));
    matriz_insert_matriz(m_expand,m,lin_dif,col_dif);
    
    Matriz* m_conv = matriz_create(m->qtd_linhas,m->qtd_colunas);
    //iteraçoes para passar por todos os itens da matriz incluindo os zeros
    for(int i = 0; i < m->qtd_linhas; i++){
        for(int j = 0; j < m->qtd_colunas; j++){
            Matriz* slice_for_conv = matriz_slice(m_expand,i,j,i+(k->qtd_linhas-1),j+(k->qtd_colunas-1));
            Matriz* slice_mult_kernel = matriz_mult_point_to_point(slice_for_conv,k);
            float soma_celulas_slice = _matriz_sum_cells(slice_mult_kernel);

            matriz_insert_value(m_conv,i,j,soma_celulas_slice);
            matriz_destroy(slice_for_conv);
            matriz_destroy(slice_mult_kernel);
        }
    }
    matriz_destroy(m_expand);
    return m_conv;
}

/*O(n), dentro da função set collum e da função set row nós percorremos uma lista encadeada a fim de procurar se o endereço
referente a celula em questão existe, ai inserimos o valor, e como ambas as funções agem do mesmo jeito
e cada uma é a procura de um item numa lista encadeada e logo em seguida insere, temos que cada uma é O(n).*/
void matriz_insert_value(Matriz *mat, int lin, int col, float valor){
    if(valor != 0){
        Cell* c = _cell_get(mat->linhas[lin],col);
        if(c != NULL){
            _cell_trade_value(mat->linhas[lin],col,valor);
        }
        else{
            Cell* cell = cell_create(lin,col,valor);
            _matriz_set_collum(mat,cell,lin,col);
            _matriz_set_row(mat,cell,lin,col);
        }
    }
    else{
        Cell* c = _cell_get(mat->linhas[lin],col);
        if(c != NULL){
            _matriz_delete_cell(mat,c,lin,col);
        }
    }
}

/*O(n^3), duas iteracoes para adicionar todos os valores n*n da matriz m_insert em m, e junto a complexidade
da funcao insert value, temos O(n^3)*/
void matriz_insert_matriz(Matriz*m, Matriz* m_insert, int lin_i, int col_i){
    for(int i = lin_i; i <m->qtd_linhas-lin_i;i++){
        for(int j = col_i; j < m->qtd_colunas-col_i; j++){
            matriz_insert_value(m,i,j,matriz_get_value(m_insert,i-lin_i,j-col_i));
        }
    }
}

//O(n), buscar um item dentro de uma lista encadeada, porem no melhor caso (lista encadeada vazia), temos O(1).
void _matriz_set_collum(Matriz * mat, Cell* n, int lin, int col){
    if(mat->colunas[col] == NULL){
        mat->colunas[col] = n;
    }
    else{
        if(mat->colunas[col]->linha > lin){
            Cell* save_cell_col = mat->colunas[col];
            mat->colunas[col] = n;
            mat->colunas[col]->prox_linha = save_cell_col;
        }
        else{
            Cell* iter_cell_col = mat->colunas[col];
            if(iter_cell_col->prox_linha == NULL){
                iter_cell_col->prox_linha = n;
            }
            else{
                while(iter_cell_col->prox_linha->linha < lin){
                    iter_cell_col = iter_cell_col->prox_linha;
                    if(iter_cell_col->prox_linha == NULL)
                        break;
                 }
                Cell* save_cell_col = iter_cell_col->prox_linha;
                n->prox_linha = save_cell_col;
                iter_cell_col->prox_linha = n;
            }
        }
    }
}

//O(n), buscar um item dentro de uma lista encadeada, porem no melhor caso (lista encadeada vazia), temos O(1).
void _matriz_set_row(Matriz * mat, Cell* n, int lin, int col){
    if(mat->linhas[lin] == NULL){
        mat->linhas[lin] = n;
    }
    else{
        if(mat->linhas[lin]->coluna > col){
            Cell* save_cell_lin = mat->linhas[lin];
            mat->linhas[lin] = n;
            mat->linhas[lin]->prox_coluna = save_cell_lin;
        }
        else{
            Cell* iter_cell_lin = mat->linhas[lin];
            if(iter_cell_lin->prox_coluna==NULL){
                iter_cell_lin->prox_coluna = n;
            }
            else{
                while(iter_cell_lin->prox_coluna->coluna < col){
                    iter_cell_lin = iter_cell_lin->prox_coluna;
                    if(iter_cell_lin->prox_coluna == NULL)
                        break;
                }
                Cell* save_cell_lin = iter_cell_lin->prox_coluna;
                n->prox_coluna = save_cell_lin;
                iter_cell_lin->prox_coluna = n;
            }
        }
    }
}

//O(n), buscar um item dentro de uma lista encadeada e retornar o valor
float matriz_get_value(Matriz *m, int lin, int col){
    if(lin >= m->qtd_linhas || col >= m->qtd_colunas || lin < 0 || col < 0){
        printf("Celula inexistente na matriz, impossivel resgatar valor!\n");
        exit(1);
    }

    Cell* celula_atual = m->linhas[lin];
    while(celula_atual != NULL){
        if(celula_atual->coluna == col){
            return celula_atual->valor;
        }
        celula_atual = celula_atual->prox_coluna;
    }
    return 0;
}

//O(n^2), percorre n listas encadeadas com acesso a todos os n itens da lista (pior caso = todas celulas preenchidas)
float _matriz_sum_cells(Matriz* m){
    float soma = 0;
    for(int i = 0; i < m->qtd_linhas; i++){
        Cell* celula_atual = m->linhas[i];
        while(celula_atual != NULL){
            soma += celula_atual->valor;
            celula_atual = celula_atual->prox_coluna;
        }
    }
    return soma;
}

//O(n), percorremos uma lista encadeada de n itens até o final
void matriz_print_sparse(Matriz* m){
    for(int i = 0; i < m->qtd_linhas; i++){
        Cell* celula_atual = m->linhas[i];
        while(celula_atual != NULL){
            cell_print(celula_atual);
            celula_atual = celula_atual->prox_coluna;
        }
    }
}

//O(n*j), percorremos uma lista encadeada inteira, n vezes (numero de listas encadeadas), portanto, tendo j como numero de itens na lista encadeada e tendo n listas encadeadas, temos O(n*j). No pior caso, tendo a matriz quadrada completamente preenchida, temos O(n^2)
void matriz_print_dense(Matriz* m){
    for(int i = 0; i < m->qtd_linhas; i++){
        int coluna_inicial = 0,coluna_atual = 0;
        Cell* celula_atual = m->linhas[i];
        while(celula_atual != NULL){
            coluna_atual = celula_atual->coluna;
            int col_dif = coluna_atual - coluna_inicial;
            for(int j = 0; j < col_dif; j++){
                printf("0.00 ");
            }
            printf("%.2f ",celula_atual->valor);
            celula_atual = celula_atual->prox_coluna;
            coluna_atual++;
            coluna_inicial = coluna_atual;
        }
        int qtd_col_unnused = m->qtd_colunas - coluna_atual;
        for(int x = 0; x < qtd_col_unnused; x++){
            printf("0.00 ");
        }
        printf("\n");
    }
}

//O(n), percorremos uma lista encadeada de n itens até encontrar o item que desejamos para remove-lo
void _matriz_delete_cell(Matriz * mat,Cell* c, int lin, int col){
    while(mat->linhas[lin] != NULL){
        if(mat->linhas[lin]->prox_coluna != NULL){
            if(mat->linhas[lin]->coluna == col){
                mat->linhas[lin] = c->prox_coluna;
                break;
            }   
        }
        else{
            mat->linhas[lin] = NULL;
            break;
        }
        mat->linhas[lin] = mat->linhas[lin]->prox_coluna;
	}

	while(mat->colunas[col] != NULL){
		if(mat->colunas[col]->prox_linha != NULL){
            if(mat->colunas[col]->linha == lin){
                mat->colunas[col] = c->prox_linha;
                break;
            }
        }
        else{
            mat->colunas[col] = NULL;
            break;
        }
        mat->colunas[col] = mat->colunas[col]->prox_linha;
	}

    free(c);
}

//O(n*j), percorremos uma lista encadeada inteira, n vezes (numero de listas encadeadas), portanto, tendo j como numero de itens na lista encadeada e tendo n listas encadeadas, temos O(n*j). No pior caso, tendo a matriz quadrada completamente preenchida, temos O(n^2)
void matriz_write_bin(Matriz* m){
		FILE* file_matriz = fopen("matriz.bin","wb");
		fwrite(&(m->qtd_linhas),1,sizeof(int),file_matriz);
		fwrite(&(m->qtd_colunas),1,sizeof(int),file_matriz);

		for(int i = 0; i < m->qtd_linhas; i++){
			Cell* celula_atual = m->linhas[i];
			while(celula_atual != NULL){
					fwrite(&(celula_atual->coluna),1,sizeof(int),file_matriz);
					fwrite(&(celula_atual->linha),1,sizeof(int),file_matriz);
					fwrite(&(celula_atual->valor),1,sizeof(float),file_matriz);
					celula_atual = celula_atual->prox_coluna;
			}
		}
		fclose(file_matriz);
}

//O(n^2), percorremos n listas encadeadas, e liberamos memorias dos n itens alocados
void matriz_destroy(Matriz* m){
    for(int i = 0; i < m->qtd_linhas; i++){
        Cell* celula_atual = m->linhas[i];
        while(celula_atual != NULL){
            Cell* celula_aux = celula_atual->prox_coluna;
            cell_destroy(celula_atual);
            celula_atual = celula_aux;
        }
    }
    free(m->colunas);
    free(m->linhas);
    free(m);
}