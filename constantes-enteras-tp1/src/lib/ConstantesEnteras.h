#ifndef LIB_CONSTANTESENTERAS_H_
#define LIB_CONSTANTESENTERAS_H_

// ** PROTOTIPOS **

void evaluarEstadoFinal ( int, FILE* );
void escribirEnArchivo ( char, FILE* );
int elegirEstadoSegunTablaDeEstados ( char, FILE*, FILE* );

// ** DESARROLLO **

void constantesEnterasProcesarArchivos(FILE *originalTxt, FILE *newTxt) {
	char c = '0';
	int estadoFinal =  elegirEstadoSegunTablaDeEstados(c,originalTxt,newTxt);

	evaluarEstadoFinal(estadoFinal, newTxt);
}

int elegirEstadoSegunTablaDeEstados(char c, FILE* originalTxt, FILE* newTxt) {
	int estado = 0;

	int tablaDeEstados[7][6] = {{2,1,1,6,6,6},
						   	   {1,1,1,6,6,6},
							   {3,3,6,6,4,6},
							   {3,3,6,6,6,6},
							   {5,5,5,5,6,6},
							   {5,5,5,5,6,6},
							   {6,6,6,6,6,6}};

	while((c = fgetc(originalTxt)) != EOF){

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
			escribirEnArchivo(c, newTxt);
		} else {
			evaluarEstadoFinal(estado, newTxt);
			estado = 0;
		}
	}
	return estado;
}

void escribirEnArchivo(char c, FILE* newTxt) {
	fprintf(newTxt,"%c",c);
}

void evaluarEstadoFinal(int estado, FILE* newTxt) {
	switch (estado) {
		case 0:
			// Si termina en una ',' no escribe nada
			break;
		case 1:
			fprintf(newTxt,"\tDecimal\n");
			break;
		case 2:
		case 3:
			fprintf(newTxt,"\tOctal\n");
			break;
		case 5:
			fprintf(newTxt,"\tHexadecimal\n");
			break;
		default:
			fprintf(newTxt,"\tNo reconocido\n");
			break;
	}
}

#endif
