#ifndef SCANNER_H_INCLUDED
#define SCANNER_H_INCLUDED

typedef enum { INICIO, FIN, LEER, ESCRIBIR, ID, CONSTANTE, PARENIZQUIERDO,
		PARENDERECHO, PUNTOYCOMA, COMA, ASIGNACION, SUMA, RESTA,
		MULTIPLICACION, DIVISION, COMENTARIO, FDT,ERRORLEXICO,
		ERRORASIG, ERRORCTE
}token;

extern char * const yytext;
extern char *tok_names[];
token prox_token(void);
void match(token tok);

#endif
