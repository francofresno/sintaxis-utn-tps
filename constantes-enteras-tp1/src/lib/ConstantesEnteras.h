#ifndef LIB_CONSTANTESENTERAS_H_
#define LIB_CONSTANTESENTERAS_H_

// ** PROTOTIPOS **

void evaluarEstadoFinal ( int, FILE* );
void escribirEnArchivo ( char, FILE* );
int elegirEstadoSegunTablaDeEstados ( FILE*, FILE* );

// ** DESARROLLO **

void constantesEnterasProcesarArchivos(FILE *entryFile, FILE *resultsFile) {

	int estadoFinal =  elegirEstadoSegunTablaDeEstados(entryFile,resultsFile);

	evaluarEstadoFinal(estadoFinal, resultsFile);
}

int elegirEstadoSegunTablaDeEstados(FILE* entryFile, FILE* resultsFile) {
	char c = '0';
	int estado = 0;

	int tablaDeEstados[7][6] = {{2,1,1,6,6,6},
						   	   {1,1,1,6,6,6},
							   {3,3,6,6,4,6},
							   {3,3,6,6,6,6},
							   {5,5,5,5,6,6},
							   {5,5,5,5,6,6},
							   {6,6,6,6,6,6}};

	while((c = fgetc(entryFile)) != EOF){

		if ( c != ',') {
			switch (c) {
				case '0':
					estado = tablaDeEstados[estado][0];
					break;
				case '1' ... '7':
					estado = tablaDeEstados[estado][1];
					break;
				case '8' ... '9':
					estado = tablaDeEstados[estado][2];
					break;
				case 'a' ... 'f':
				case 'A' ... 'F':
					estado = tablaDeEstados[estado][3];
					break;
				case 'x':
				case 'X':
					estado = tablaDeEstados[estado][4];
					break;
				default:
					estado = tablaDeEstados[estado][5];
					break;
			}
			escribirEnArchivo(c, resultsFile);
		} else {
			evaluarEstadoFinal(estado, resultsFile);
			estado = 0;
		}
	}
	return estado;
}

void escribirEnArchivo(char c, FILE* resultsFile) {
	fprintf(resultsFile,"%c",c);
}

void evaluarEstadoFinal(int estado, FILE* resultsFile) {
	switch (estado) {
		case 0:
			// Si termina en una ',' no escribe nada
			break;
		case 1:
			fprintf(resultsFile,"\tDecimal\n");
			break;
		case 2:
		case 3:
			fprintf(resultsFile,"\tOctal\n");
			break;
		case 5:
			fprintf(resultsFile,"\tHexadecimal\n");
			break;
		default:
			fprintf(resultsFile,"\tNo reconocido\n");
			break;
	}
}

#endif
