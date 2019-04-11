#include<stdio.h>
#include<stdlib.h>
#include "lib/ConstantesEnteras.h"

int main(){
	FILE* originalTxt = fopen("text.txt","r");
	FILE* newTxt = fopen("newText.txt","w");
// HOLA QUE TAL COMO TE VA
	constantesEnterasProcesarArchivos(originalTxt, newTxt);

	fclose(originalTxt);
	fclose(newTxt);

	return 0;
}



