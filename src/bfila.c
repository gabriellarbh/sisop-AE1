
/********************************************************************
	Programa de teste da Biblioteca de Filas
	Vers. 1.0 - 3/3/16
********************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "fila2.h"

int	vetor[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

int	Verifica(PFILA2 fila, int value);
void	printGrade(int current);

#define	TOTAL_COUNT	10	// Numero total de testes

int main() {
	int	err;
	int	i,n;
	FILA2	fila;
	int	correctCount;
	
	correctCount = 0;
	
	// Inicializa a fila
	if (CreateFila2(&fila)) {
		printf ("Erro: não conseguiu criar a fila\n");
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printf ("Ok: CreateFila2\n");
	
	// Teste de fila vazia
	n = FirstFila2(&fila);
	if (n==0) {
		printf ("Erro: FirstFila2 should return an error as queue is empty.\n");
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printf ("Ok: FirstFila2 returned empty queue information.\n");
	
	// Preenche a fila com 5 itens
	for (i=0; i<5; ++i) {
		if (AppendFila2(&fila, (void *)(vetor+i))) {
			printf ("Error: could not append item to the queue\n");
			printGrade(correctCount);
			exit(0);
		}
	}
	correctCount++;
	printf ("Ok: 5 itens appended (AppendFila2)\n");
	
	// Teste de First
	// Verifica se posicionou no inicio da fila
	// Verifica se pegou o elemento correto
	if (FirstFila2(&fila)) {
		printf ("Error: FirstFila2 is NOT working\n");
		printGrade(correctCount);
		exit(0);
	}	
	correctCount++;
	printf ("Ok: First queue returned correctly.\n");
	
	// Essa é aprimeira vez que o Verifica é chamado. Então, vale 1 ponto!
	if (Verifica(&fila, 0)) {
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printf ("Ok: GetAtIteratorFila2 got correct item.\n");

	// Teste de Last
	// Verifica se posicionou no final da fila
	if (LastFila2(&fila)) {
		printf ("Error: LastFila2 is NOT working\n");
		printGrade(correctCount);
		exit(0);
	}	
	if (Verifica(&fila, 4)) {
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printf ("Ok: Last queue item was correctly read.\n");
	
	// Teste de Next
	FirstFila2(&fila);
	for (n=i=0; i<5; ++i) {
		n += (*(int *)GetAtIteratorFila2(&fila));
		err = NextFila2(&fila);
		if (err) {
			printf ("Error: NextFila2 is NOT working\n");
			printGrade(correctCount);
			exit(0);
		}
	}
	if (n!=10) {
		printf ("Error: NextFila2 IS NOT pointing to next item ot the queue.\n");
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printf ("Ok: NextFila2 is working\n");

	// Teste de insersao no meio da lista
	FirstFila2(&fila);
	NextFila2(&fila);
	NextFila2(&fila);	
	if (InsertAfterIteratorFila2(&fila, (void *)(vetor+9))) {
		printf ("Error: InsertAfterIteratorFila2 is NOT working\n");
		printGrade(correctCount);
		exit(0);
	}
	FirstFila2(&fila);
	NextFila2(&fila);
	NextFila2(&fila);	
	NextFila2(&fila);
	if (Verifica(&fila, 9)) {
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printf ("Ok: InsertAfterIteratorFila2 is working\n");
	
	// Teste de DELETE
	FirstFila2(&fila);
	NextFila2(&fila);
	NextFila2(&fila);	
	NextFila2(&fila);

	if (DeleteAtIteratorFila2(&fila)) {
		printf ("Error: DeleteAtIteratorFila2 is NOT working\n");
		printGrade(correctCount);
		exit(0);
	}
	if (Verifica(&fila, 3)) {
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printf ("Ok: DeleteAtIteratorFila2 is working\n");
	
	// Clear fila2 to verify empty queue
	FirstFila2(&fila);
	for (i=0; i<10; ++i) {
		if (DeleteAtIteratorFila2(&fila))
			break;
	}
	if (AppendFila2(&fila, (void *)(&vetor[7]))) {
		printf ("Error: Could not append item after clear queue\n");
		printGrade(correctCount);
		exit(0);
	}
	FirstFila2(&fila);
	err = Verifica(&fila, 7);
	if (err) {
		switch(err) {
			case -1: printf ("Error: GetAtIteratorFila2 IS NOT working, after clear fila2\n"); break;
			case -2: printf ("Error: GetAtIteratorFila2 is getting a wrong item, after clear fila2\n"); break;
		}
		printGrade(correctCount);
		exit(0);
	}
	correctCount++;
	printf ("Ok: Clear queue is working properlly\n");
	
	
	printf ("SEM ERRO!\n");
	printGrade(correctCount);
	exit(0);
}


int	Verifica(PFILA2 fila, int value) {
	
	int *p;
	p = (int *)GetAtIteratorFila2(fila);
	if (p==NULL) {
		return -1;
	}
	if (*p!=value) {
		printf ("VERIFICA %d==%d?\n", value, *p);
		return -2;
	}
	return 0;
}


void	printGrade(int current) {
	printf ("GRADE IS (%d/%d): %d\n", current, TOTAL_COUNT, (100*current)/TOTAL_COUNT);
}



