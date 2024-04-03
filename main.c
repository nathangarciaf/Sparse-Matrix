#include "matriz.h"
int main(int argc, char ** argv){
		if(argc > 1){
				printf("ARQUIVO BINARIO ENCONTRADO\n\n");
				Matriz* m_bin = matriz_read_bin(argv[1]); 
				printf("MATRIZ LIDA DO BINARIO ESPARSA:\n");
    		matriz_print_sparse(m_bin);
    		printf("\n");
    		printf("MATRIZ LIDA DO BINARIO FORMATO DENSO:\n");
    		matriz_print_dense(m_bin);
    		printf("\n");
				matriz_destroy(m_bin);
		}
		else{
				printf("ARQUIVO BINARIO NAO ENCONTRADO!\nSERA GERADO UM ARQUIVO BINARIO AO FINAL DO PROGRAMA PARA TESTE DA FUNCIONALIDADE DE LEITURA. RODE NOVAMENTE O PROGRAMA\n\n");
		}
	
    Matriz* m = matriz_create(2, 3);
    matriz_insert_value(m,0,0,2);
    matriz_insert_value(m,0,1,1);
    matriz_insert_value(m,1,1,1);
    matriz_insert_value(m,1,2,9);

    printf("MATRIZ 1 ESPARSA:\n");
    matriz_print_sparse(m);
    printf("\n");
    printf("MATRIZ 1 FORMATO DENSO:\n");
    matriz_print_dense(m);
    printf("\n");

    matriz_insert_value(m,0,0,0);

    printf("MATRIZ M ESPARSA COM 0X0 ATUALIZADA:\n");
    matriz_print_sparse(m);
    printf("\n");
    printf("MATRIZ MZ FORMATO DENSO COM 0X0 ATUALIZADA:\n");
    matriz_print_dense(m);
    printf("\n");

    printf("FUNCAO GET VALUE DA MATRIZ 1:\n");
    float v1 = matriz_get_value(m,1,0);
    float v2 = matriz_get_value(m,1,2);
    printf("VALOR DA CELULA %dx%d:%.2f\nVALOR DA CELULA %dx%d:%.2f\n\n",1,0,v1,1,2,v2);

    Matriz * m2 = matriz_create(3, 2);
    matriz_insert_value(m2,0,0,3);
    matriz_insert_value(m2,1,0,1);
    matriz_insert_value(m2,2,0,2);
    matriz_insert_value(m2,0,1,4);

    printf("MATRIZ 2 ESPARSA:\n");
    matriz_print_sparse(m2);
    printf("\n");
    printf("MATRIZ 2 FORMATO DENSO:\n");
    matriz_print_dense(m2);
    printf("\n");

    Matriz * m3 = matriz_create(2, 3);
    matriz_insert_value(m3,0,0,21);
    matriz_insert_value(m3,1,0,3);
    matriz_insert_value(m3,0,2,9);
    matriz_insert_value(m3,0,1,15);

    printf("MATRIZ 3 ESPARSA:\n");
    matriz_print_sparse(m3);
    printf("\n");
    printf("MATRIZ 3 FORMATO DENSO:\n");
    matriz_print_dense(m3);
    printf("\n");

    Matriz* add_m = matriz_sum_matriz(m,m3);
    printf("MATRIZ SOMA M1+M3 ESPARSA:\n");
    matriz_print_sparse(add_m);
    printf("\n");
    printf("MATRIZ SOMA M1+M3 FORMATO DENSO:\n");
    matriz_print_dense(add_m);
    printf("\n");

    printf("MATRIZ MULT PONTO A PONTO M1XM3 ESPARSA:\n");
    Matriz* mult_ptp_m = matriz_mult_point_to_point(m,m3);
    matriz_print_sparse(mult_ptp_m);
    printf("\n");
    printf("MATRIZ MULT PONTO A PONTO M1XM3 FORMATO DENSO:\n");
    matriz_print_dense(mult_ptp_m);
    printf("\n");

    printf("MATRIZ TRANSPOSTA DE 1:\n");
    Matriz* trp = matriz_transpose(m);
    matriz_print_dense(trp);
    printf("\n");

    printf("MATRIZ MULTIPLICACAO 1X2:\n");
    Matriz* mult = matriz_multiplication(m,m2);
    matriz_print_dense(mult);
    printf("\n");

    printf("MATRIZ MULT 1X2 - MULT POR ESCALAR 2:\n");
    Matriz* mult_m = matriz_scalar_multiplication(mult,2);
    matriz_print_dense(mult_m);
    printf("\n");

    printf("MATRIZ MULT 1X2 - LINHA TROCADA:\n");
    Matriz* sr_m = matriz_swap_rows(mult,1,0);
    matriz_print_dense(sr_m);
    printf("\n");

    printf("MATRIZ MULT 1X2 - COLUNA TROCADA:\n");
    Matriz* sc_m = matriz_swap_collum(mult,0,1);
    matriz_print_dense(sc_m);
    printf("\n");

    printf("MATRIZ TESTE PARA SLICE:\n");
    Matriz * slice_t = matriz_create(4, 4);
    matriz_insert_value(slice_t,1,2,2);
    matriz_insert_value(slice_t,1,3,10);
    matriz_insert_value(slice_t,2,1,5);
    matriz_insert_value(slice_t,0,0,13);
    matriz_insert_value(slice_t,1,0,92);
    matriz_insert_value(slice_t,1,3,4);
    matriz_insert_value(slice_t,2,2,3);
    matriz_insert_value(slice_t,3,3,62);
    matriz_print_dense(slice_t);
    printf("\n");

    printf("MATRIZ SLICE:\n");
    Matriz* slice = matriz_slice(slice_t,0,0,2,2);
    matriz_print_dense(slice);
		printf("\n");

    printf("MATRIZ PARA CONVOLUCAO:\n");
		Matriz* m_conv = matriz_create(6,6);
		matriz_insert_value(m_conv,0,0,3);
		matriz_insert_value(m_conv,0,1,3);
		matriz_insert_value(m_conv,0,2,4);
		matriz_insert_value(m_conv,0,3,4);
		matriz_insert_value(m_conv,0,4,7);
		matriz_insert_value(m_conv,1,0,9);
		matriz_insert_value(m_conv,1,1,7);
		matriz_insert_value(m_conv,1,2,6);
		matriz_insert_value(m_conv,1,3,5);
		matriz_insert_value(m_conv,1,4,8);
		matriz_insert_value(m_conv,1,5,2);
		matriz_insert_value(m_conv,2,0,5);
    matriz_print_dense(m_conv);
    printf("\n");

    printf("MATRIZ KERNEL:\n");
		Matriz* kernel = matriz_create(3,3);
		matriz_insert_value(kernel,0,2,-1);
		matriz_insert_value(kernel,0,0,1);
		matriz_insert_value(kernel,1,0,1);
		matriz_insert_value(kernel,1,2,-1);
		matriz_insert_value(kernel,2,0,1);
		matriz_insert_value(kernel,2,2,-1);
    matriz_print_dense(kernel);
    printf("\n");
	
    printf("MATRIZ CONVOLUCIONADA:\n");
		Matriz* conv_m = matriz_convolution(m_conv,kernel);
		matriz_print_dense(conv_m);

		printf("ESCREVENDO A MATRIZ 1 EM ARQUIVO BINÁRIO...\n");
    matriz_write_bin(m);

		matriz_destroy(conv_m);
		matriz_destroy(m_conv);
		matriz_destroy(kernel);
    matriz_destroy(slice_t);
    matriz_destroy(slice);
    matriz_destroy(mult);
    matriz_destroy(trp);
    matriz_destroy(mult_m);
    matriz_destroy(sc_m);
    matriz_destroy(sr_m);
    matriz_destroy(m);
    matriz_destroy(m2);
    matriz_destroy(m3);
    matriz_destroy(add_m);
    matriz_destroy(mult_ptp_m);
    return 0;
}