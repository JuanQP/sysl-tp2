#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

#include <stdio.h>

typedef enum { INICIO, FIN, LEER, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO,
    PARENDERECHO, PUNTOYCOMA, COMA, ASIGNACION, SUMA, RESTA,
	MULTIPLICACION, DIVISION, COMENTARIO, FDT,ERRORLEXICO,
	ERRORASIG, ERRORCTE
}token;

/*Guarda el lexema actual.*/
extern char * const yytext;

/*Guarda los nombres de los tokens en string.*/
extern char *nombresToken[];

/*Informa el número de línea del archivo siendo scaneado.*/
extern int numeroLinea;

/*Token actual*/
extern token tokenActual;

/*Me devuelve el próximo token a ser scanneado.*/
token proximoToken(void);

/*Verifica que el token devuelto por el scanner coincida con el token que se esperaba.*/
void match(token tok);

/*Defino el fuente donde voy a escribir el pseudo-assambler.*/
extern FILE *fuente;

int sonIguales(char*, char*);

#endif
