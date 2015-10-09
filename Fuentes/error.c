#include <stdlib.h>
#include <stdio.h>
#include "scanner.h"


/*Informa la existencia de un error sintáctico (se obtuvo un token que no se esperaba).*/
void errorSintactico(token tokenObtenido)
{
    printf("%2d-\e[1;31m[X]\e[0m: No se esperaba el token \e[1;31m%s\e[0m.\n", numeroLinea, nombresToken[tokenObtenido]);
}

/*Informo qué error léxico se encontró.*/
void errorLexico(token tok)
{
    printf("%2d-\e[1;31m[X]\e[0m: El token \e[1;31m%s\e[0m va a ser salteado.\n", numeroLinea, nombresToken[tok]);
}
