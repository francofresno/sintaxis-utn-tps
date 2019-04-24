/*
 ============================================================================
 Name        : gramatica_suma_resta.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

//PILA

struct nodo {
	struct nodo *sig;
	char estado;
};

typedef struct nodo nodo;

void push(char nuevoEstado, nodo **top) {
	nodo *tmp;
	tmp = malloc(sizeof(nodo));
	tmp->estado = nuevoEstado;
	tmp->sig = (*top);
	(*top) = tmp;
}

void initialize(nodo **top) {
	(*top)->estado = '$';
	(*top)->sig = NULL;
	push('E', &(*top));
}

int isEmpty(nodo *top) {
	return top == NULL;
}

char pop(nodo **top) {
	if (isEmpty(*top))
		return -1;
	char estadoADevolver;
	nodo *tmp;
	tmp = (*top);
	estadoADevolver = (*top)->estado;
	(*top) = (*top)->sig;
	free(tmp);
	return estadoADevolver;
}

char showTop(nodo *top) {
	return top->estado;
}

//ESTADOS

char estadoE1(char expresion, nodo **pila) {
	if (('0' <= expresion && expresion <= '9') || expresion == '(') {
		push('e', &(*pila));
		push('T', &(*pila));
		return expresion;
	} else if (expresion == ')') {
		pop(&(*pila));
		return 32;
	} else if (expresion == '\n')
		return 32;
	printf("Error (estadoE1)\n");
	return -1;
}

char estadoE2(char expresion, nodo **pila) {
	if (expresion == '+') {
		push('e', &(*pila));
		push('T', &(*pila));
		return 32;
	} else if (('0' <= expresion && expresion <= '9') || expresion == '('
			|| expresion == '*') {
		return expresion;
	} else if (expresion == '\n') {
		return 32;
	} else if (expresion == ')') {
		pop(&(*pila));
		return 32;
	}
	printf("Error (estadoE2)\n");
	return -1;
}

char estadoT1(char expresion, nodo **pila) {
	if (('0' <= expresion && expresion <= '9') || expresion == '(') {
		push('t', &(*pila));
		push('F', &(*pila));
		return expresion;
	}
	printf("Error (estadoT1)\n");
	return -1;
}

char estadoT2(char expresion, nodo **pila) {
	if (expresion == '*') {
		push('t', &(*pila));
		push('F', &(*pila));
		return 32;
	} else if (('0' <= expresion && expresion <= '9') || expresion == '('
			|| expresion == '+' || expresion == '\n' || expresion == ')') {
		return expresion;
	}
	printf("Error (estadoT2)\n");
	return -1;
}

char estadoF(char expresion, nodo **pila) {
	if ('0' <= expresion && expresion <= '9') {
		push('N', &(*pila));
		return expresion;
	} else if (expresion == '(') {
		push('E', &(*pila));
		push(')', &(*pila));
		return 32;
	}
	printf("Error (estadoF)\n");
	return -1;
}

char estadoN(char expresion, nodo **pila) {
	if ('0' <= expresion && expresion <= '9') {
		push('N', &(*pila));
		return 32;
	} else if (expresion == '(' || expresion == '+' || expresion == '\n'
			|| expresion == '*' || expresion == ')') {
		return expresion;
	}
	printf("Error (estadoN)\n");
	return -1;
}

//MAIN

int main(int argc, char **argv) {

	char input;
	char expresion;
	nodo *pila = malloc(sizeof(nodo));
	initialize(&pila);

	do {
		input = getchar();
		expresion = input;
		while (expresion != 32 && expresion != -1) {
			switch (pop(&pila)) {
			case 'E':
				expresion = estadoE1(input, &pila);
				break;
			case 'e':
				expresion = estadoE2(input, &pila);
				break;
			case 'T':
				expresion = estadoT1(input, &pila);
				break;
			case 't':
				expresion = estadoT2(input, &pila);
				break;
			case 'F':
				expresion = estadoF(input, &pila);
				break;
			case 'N':
				expresion = estadoN(input, &pila);
			}
		}
		if (expresion == -1) {
			printf("Error -1: expresion no aceptada\n");
			return -1;
		}
	} while (showTop(pila) != '$');

	while (!isEmpty(pila)) {
		printf("%c", pop(&pila));
	}
}
