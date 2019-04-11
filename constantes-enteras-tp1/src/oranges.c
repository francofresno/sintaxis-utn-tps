#include<stdio.h>
#include<stdlib.h>
#include "lib/ConstantesEnteras.h"

int main(){
	FILE* entryFile = fopen("Entry.txt","r");
	FILE* resultsFile = fopen("Results.txt","w");
	constantesEnterasProcesarArchivos(entryFile, resultsFile);

	fclose(entryFile);
	fclose(resultsFile);

	return 0;
}



