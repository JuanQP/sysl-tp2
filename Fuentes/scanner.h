#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

typedef enum { INICIO, FIN, LEER, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO,
    PARENDERECHO, PUNTOYCOMA, COMA, ASIGNACION, SUMA, RESTA,
	MULTIPLICACION, DIVISION, COMENTARIO, FDT,ERRORLEXICO,
	ERRORASIG, ERRORCTE
}token;

/*Guarda el lexema actual.*/
extern char * const yytext;

/*Guarda los nombres de los tokens en string.*/
extern char *tok_names[];

/*Informa el número de línea del archivo siendo scaneado.*/
extern int numeroLinea;
token prox_token(void);
void match(token tok);

/*Para poder utilizar el scanner sin necesidad de usar MATCH,
definimos publicamente el scanner aca, asi lo podemos
llamar desde main.c*/
token scanner(void);

#endif
