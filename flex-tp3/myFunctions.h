#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct elemento{
  char id[50];
  int valor;
};
typedef struct elemento elemento;


struct nodo{
  elemento dato;
  struct nodo* sig;
};
typedef struct nodo nodo;

void encontrarEnLista(nodo** lista, char identificador[], int incremento, int fijar){
  nodo* paux = (*lista);
  while(paux && paux->sig){
    if(!strcmp(paux->dato.id, identificador)){
      if(!fijar)
        paux->dato.valor += incremento;
      return;
    }
    else
      paux = paux->sig;
  }

  if(!paux){
    (*lista) = malloc(sizeof(nodo));
    strcpy((*lista)->dato.id, identificador);
    (*lista)->dato.valor = incremento;
    (*lista)->sig = NULL;
  }
  else if(!strcmp(paux->dato.id, identificador)){
    if(!fijar)
        paux->dato.valor += incremento;
    return;
  }else{
    paux->sig = malloc(sizeof(nodo));
    strcpy(paux->sig->dato.id, identificador);
    paux->sig->dato.valor = incremento;
    paux->sig->sig = NULL;
  }
}

void borrarLista(nodo **lista){
  nodo* paux = (*lista);
  while(paux){
    free(paux);
    (*lista) = (*lista)->sig;
    paux = (*lista);
  }
}

void imprimirListaId(nodo **lista){
  nodo* paux = (*lista);
  if(paux)
    printf("-ID\n");
  while(paux){
    printf("El id %s aparece %i vez/veces\n", paux->dato.id, paux->dato.valor);
    paux = paux->sig;
  }
}

void imprimirListaLCadena(nodo **lista){
  nodo* paux = (*lista);
  if(paux){
    printf("-LITERAL CADENA\n");
    printf("Literal Cadena -> Tamaño sin comillas\n");
  }
  while(paux){
    printf("%s -> %i\n", paux->dato.id, paux->dato.valor);
    paux = paux->sig;
  }
}

void imprimirListaTipo(nodo **lista){
  nodo* paux = (*lista);
  if(paux)
    printf("-PALABRA RESERVADA: TIPO\n");
  while(paux){
    printf("%s\n", paux->dato.id);
    paux = paux->sig;
  }
}

void imprimirListaControl(nodo **lista){
  nodo* paux = (*lista);
  if(paux)
    printf("-PALABRA RESERVADA: CONTROL\n");
  while(paux){
    printf("%s\n", paux->dato.id);
    paux = paux->sig;
  }
}

void imprimirListaOtra(nodo **lista){
  nodo* paux = (*lista);
  if(paux)
    printf("-PALABRA RESERVADA: OTRA\n");
  while(paux){
    printf("%s\n", paux->dato.id);
    paux = paux->sig;
  }
}

void imprimirListaOctal(nodo **lista){
  nodo* paux = (*lista);
  if(paux){
    printf("-CONSTANTE OCTAL\n");
    printf("Valor octal -> Valor decimal\n");
  }
  while(paux){
    printf("%s -> %i\n", paux->dato.id, paux->dato.valor);
    paux = paux->sig;
  }
}

void imprimirListaHexa(nodo **lista){
  nodo* paux = (*lista);
  if(paux){
    printf("-CONSTANTE HEXADECIMAL\n");
    printf("Valor hexadecimal -> Valor decimal\n");
  }
  while(paux){
    printf("%s -> %i\n", paux->dato.id, paux->dato.valor);
    paux = paux->sig;
  }
}

void imprimirListaDecimal(nodo **lista, float acum){
  nodo* paux = (*lista);
  int mostrarAcum = 0;
  if(paux){
    printf("-CONSTANTE DECIMAL\n");
    printf("Valor decimal -> Veces que aparece\n");
    mostrarAcum = 1;
  }
  while(paux){
    printf("%s -> %i\n", paux->dato.id, paux->dato.valor);
    paux = paux->sig;
  }
  if(mostrarAcum)
    printf("Suma total %f\n", acum);
}

void imprimirListaReal(nodo **parteEntera, nodo **mantisa){
  nodo* paux1 = (*parteEntera);
  nodo* paux2 = (*mantisa);
  if(paux1){
    printf("-CONSTANTE REAL\n");
    printf("Valor entero :: mantisa\n");
  }
  while(paux1){
    printf("%i :: %i\n", paux1->dato.valor, paux2->dato.valor);
    paux1 = paux1->sig;
    paux2 = paux2->sig;
  }
}

void imprimirListaPuntuacion(nodo **lista){
  nodo* paux = (*lista);
  if(paux)
    printf("-CARACTER DE PUNTUACION\n");
  while(paux){
    printf("El cdp %s aparece %i vez/veces\n", paux->dato.id, paux->dato.valor);
    paux = paux->sig;
  }
}

void imprimirListaOperadores(nodo **lista){
  nodo* paux = (*lista);
  if(paux)
    printf("-OPERADORES\n");
  while(paux){
    printf("El operador %s aparece %i vez/veces\n", paux->dato.id, paux->dato.valor);
    paux = paux->sig;
  }
}

void imprimirListaComentarios(nodo **lista){
  nodo* paux = (*lista);
  if(paux)
    printf("-COMENTARIOS\n");
  while(paux){
    printf("%s\n", paux->dato.id);
    paux = paux->sig;
  }
}

void imprimirListaNoRec(nodo **lista){
  nodo* paux = (*lista);
  if(paux)
    printf("CARACTERES NO RECONOCIDOS\n");
  while(paux){
    printf("%s\n", paux->dato.id);
    paux = paux->sig;
  }
}

long long convertOctalToDecimal(int octalNumber){
    int decimalNumber = 0, i = 0;
    while(octalNumber != 0){
        decimalNumber += (octalNumber%10) * pow(8,i);
        ++i;
        octalNumber/=10;
    }
    i = 1;
    return decimalNumber;
}


long long hexadecimalToDecimal(int hexalNumber){
    int decimalNumber = 0, i = 0;
    while(hexalNumber != 0){
        decimalNumber += (hexalNumber%10) * pow(16,i);
        ++i;
        hexalNumber/=10;
    }
    i = 1;
    return decimalNumber;
}

long long realSeparator(float real){
    float base = real - (int)real;
    while (base - (int)base > 0){
        base *= 10;
    }
    return (int)base;
}

/*
void reporte(){
    imprimirListaId(&listaId);
    imprimirListaLCadena(&listaLCadena);
    imprimirListaTipo(&listaTipo);
    imprimirListaControl(&listaControl);
    imprimirListaOtra(&listaOtra);
    imprimirListaOctal(&listaOctal);
    imprimirListaHexa(&listaHexa);
    imprimirListaDecimal(&listaDecimal, acum);
    imprimirListaReal(&listaRealEntera, &listaRealMantisa);
    imprimirListaPuntuacion(&listaPuntuacion);
    imprimirListaOperadores(&listaOperador);
    imprimirListaComentarios(&listaComent);
    imprimirListaNoRec(&listaNoRec);
}*/
