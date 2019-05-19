/*
 * tuna.c
 *
 *  Created on: Apr 17, 2019
 *      Author: lotus
 */

#include<stdio.h>
#include<stdlib.h>

struct nodo{
	struct nodo *sig;
	char estado;
};

typedef struct nodo nodo;

//COLA
void initCola(nodo** top) {
	(*top)->estado = '$';
	(*top)->sig = NULL;
	return;
}

void queue(char elemento, nodo** top){
	nodo *tmp = *top;
	if(tmp->estado == '$')
		tmp->estado = elemento;
	else{
		(*top) = malloc(sizeof(nodo));
		(*top)->estado = elemento;
		(*top)->sig = tmp;
	}
}

char unqueue(nodo** top) {
	nodo* tmp = (*top);
	nodo* anterior = NULL;
	char k;

	if(!tmp)
		return '\n';

	while(tmp->sig) {
		anterior = tmp;
		tmp = tmp->sig;
	}

	k = tmp->estado;
	if(tmp == (*top)) {
		free(tmp);
		(*top)= NULL;
	}
	else {
	  free(tmp);
	  anterior->sig = NULL;
	}

	return k;
}

//PILA
void push(char nuevoEstado, nodo **top){
	nodo *tmp;
	tmp = malloc(sizeof(nodo));
	tmp->estado = nuevoEstado;
	tmp->sig = (*top);
	(*top) = tmp;
}

void initialize(nodo **top){
	(*top)->estado = '$';
	(*top)->sig = NULL;
	push('E', &(*top));
}

int isEmpty(nodo *top){
	return top==NULL;
}

char pop(nodo **top){
	if(isEmpty(*top))
		return -1;
	char estadoADevolver;
	nodo *tmp;
	tmp = (*top);
	estadoADevolver = (*top)->estado;
	(*top) = (*top)->sig;
	free(tmp);
	return estadoADevolver;
}

char showTop(nodo *top){
	return top->estado;
}

//ESTADOS
void estadoSuma(int *ant, int *num, char *elemento, char condicionSalida, nodo **cuenta);

char estadoE1(char expresion, nodo **pila, nodo **cuenta){
	if(('0'<= expresion && expresion <= '9') || expresion == '('){
		push('e',&(*pila));
		push('T',&(*pila));
		return expresion;
	}else if(expresion == ')'){
		queue(')', cuenta);
		pop(&(*pila));
		return 32;
	}else if(expresion == '\n')
		return 32;
	printf("Error (estadoE1)\n");
	return -1;
}

char estadoE2(char expresion, nodo **pila, nodo **cuenta){
	if(expresion == '+'){
		queue(expresion,&(*cuenta));
		push('e',&(*pila));
		push('T',&(*pila));
		return 32;
	}else if(('0'<= expresion && expresion <= '9') || expresion == '(' || expresion == '*'){
		return expresion;
	}else if(expresion == '\n'){
		return 32;
	}else if(expresion == ')'){
		queue(')', cuenta);
		pop(&(*pila));
		return 32;
	}
	printf("Error (estadoE2)\n");
	return -1;
}

char estadoT1(char expresion, nodo **pila, nodo **cuenta){
	if(('0'<= expresion && expresion <= '9') || expresion == '('){
		push('t',&(*pila));
		push('F',&(*pila));
		return expresion;
	}
	printf("Error (estadoT1)\n");
	return -1;
}

char estadoT2(char expresion, nodo **pila, nodo **cuenta){
	if(expresion == '*'){
		queue(expresion,&(*cuenta));
		push('t',&(*pila));
		push('F',&(*pila));
		return 32;
	}else if(('0'<= expresion && expresion <= '9') || expresion == '(' || expresion == '+' || expresion == '\n' || expresion == ')'){
		return expresion;
	}
	printf("Error (estadoT2)\n");
	return -1;
}

char estadoF(char expresion, nodo **pila, nodo **cuenta){
	if('0'<= expresion && expresion <= '9'){
		push('N',&(*pila));
		return expresion;
	}else if(expresion == '('){
		queue(expresion,&(*cuenta));
		push(')',&(*pila));
		push('E',&(*pila));
		return 32;
	}
	printf("Error (estadoF)\n");
	return -1;
}

char estadoN(char expresion, nodo **pila, nodo **cuenta){
	if('0'<= expresion && expresion <= '9'){
		queue(expresion,&(*cuenta));
		push('N',&(*pila));
		return 32;
	}else if(expresion == '(' || expresion == '+' || expresion == '\n' || expresion == '*' || expresion == ')'){
		return expresion;
	}
	printf("Error (estadoN)\n");
	return -1;
}

void estadoMultiplicacion(int *ant, int *num, char *elemento, char condicionSalida, nodo **cuenta){
	int espera;
	int entrar = 1;
	do{
		(*elemento) = unqueue(&(*cuenta));
		if((*elemento) == condicionSalida && entrar == 1){
			(*num) *= (*ant);
		}else if((*elemento) >= '0' && (*elemento) <= '9'){
			(*num) = (*num)*10 + ((*elemento) - '0');
			entrar = 1;
		}else if((*elemento) == '*'){
			(*ant) *= (*num);
			(*num) = 0;
			estadoMultiplicacion(ant, num, elemento, condicionSalida, &(*cuenta));
			entrar = 1;
		}else if((*elemento) == '+'){
			(*ant) *= (*num);
			(*num) = 0;
			estadoSuma(ant, num, elemento, condicionSalida, &(*cuenta));
			entrar = 1;
		}else if((*elemento) == '('){
			espera = (*ant);
			(*ant) = 0;
			estadoSuma(ant,num,elemento,')',&(*cuenta));
			(*num) *= espera;
			(*ant) = 0;
			entrar = 0;
		}
	}while((*elemento) != condicionSalida);
}

void estadoSuma(int *ant, int *num, char *elemento, char condicionSalida, nodo **cuenta){
	int espera;
	int entrar = 1;
	do{
		(*elemento) = unqueue(&(*cuenta));
		if((*elemento) == condicionSalida && entrar == 1){
			(*num) += (*ant);
		}else if((*elemento) >= '0' && (*elemento) <= '9'){
			(*num) = (*num)*10 + ((*elemento) - '0');
			entrar = 1;
		}else if((*elemento) == '+'){
			(*ant) += (*num);
			(*num) = 0;
			estadoSuma(ant,num,elemento,condicionSalida,&(*cuenta));
			entrar = 1;
		}else if((*elemento) == '*'){
			espera = (*ant);
			(*ant) = (*num);
			(*num) = 0;
			estadoMultiplicacion(ant,num,elemento,condicionSalida,&(*cuenta));
			(*num) += espera;
			entrar = 1;
		}else if((*elemento) == '('){
			espera = (*ant);
			(*ant) = 0;
			estadoSuma(ant,num,elemento,')',&(*cuenta));
			(*num) += espera;
			(*ant) = 0;
			entrar = 0;
		}
	}while((*elemento) != condicionSalida);
}

//MAIN
int main(){

	//variables utilizadas para la pila de estados
	char input;
	char expresion;
	nodo *pila = malloc(sizeof(nodo));
	initialize(&pila);
	nodo *cuenta = malloc(sizeof(nodo));
	initCola(&cuenta);

	//variables utilizadas para la cola que va a ser la ecuacion
	int *ant = malloc(sizeof(int));
	*ant = 0;
	int *num = malloc(sizeof(int));
	*num = 0;
	char * elemento = malloc(sizeof(char));
	*elemento = 0;

	//Proceso de apilar y desapilar estados (determina si los caracteres ingresados son aceptados y compone la cola
	do{
		input = getchar();
		expresion = input;
		while(expresion != 32 && expresion != -1){
			switch(pop(&pila)){
				case 'E':
					expresion = estadoE1(input,&pila,&cuenta);
					break;
				case 'e':
					expresion = estadoE2(input,&pila,&cuenta);
					break;
				case 'T':
					expresion = estadoT1(input,&pila,&cuenta);
					break;
				case 't':
					expresion = estadoT2(input,&pila,&cuenta);
					break;
				case 'F':
					expresion = estadoF(input,&pila,&cuenta);
					break;
				case 'N':
					expresion = estadoN(input,&pila,&cuenta);
			}
		}
		if(expresion == -1){
			printf("Error -1: expresion no aceptada\n");
			return -1;
		}
	} while (showTop(pila) != '$');

	//pila se vacio correctamente
	while(!isEmpty(pila)){
		printf("%c", pop(&pila));
	}

	//realiza las operaciones sobre la cola, leyendo caracter a caracter
	estadoSuma(ant, num, elemento, '\n', &cuenta);

	printf("%i",*num);

	return 0;
}
