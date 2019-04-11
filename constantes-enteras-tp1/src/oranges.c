#include<stdio.h>
#include<stdlib.h>
#include "lib/ConstantesEnteras.h"

int main(){
	FILE* entryFile = fopen("text.txt","r");
	FILE* resultsFile = fopen("newText.txt","w");
	constantesEnterasProcesarArchivos(entryFile, resultsFile);

	fclose(entryFile);
	fclose(resultsFile);

	return 0;
}



