#include <stdlib.h>
#include <stdio.h>
#include "scanner.h"


/*Informa la existencia de un error sintáctico (se obtuvo un token que no se esperaba).*/
void errorSintactico(token tokenObtenido, char *valoresEsperados)
{
    printf("%2d-\e[1;31m[X]\e[0m: Se esperaban los token '%s' pero se obtuvo \e[1;31m%s\e[0m.\n", numeroLinea, valoresEsperados, nombresToken[tokenObtenido]);
}

/*Informo qué error léxico se encontró.*/
void errorLexico(token tok)
{
    printf("%2d-\e[1;31m[X]\e[0m: El lexema %s es un \e[1;31m%s\e[0m. Va a ser salteado.\n", numeroLinea, yytext, nombresToken[tok]);
}
