#include "symbol.h"
#include "scanner.h"
#include "semantic.h"
#include <stdio.h>

void comenzar()
{
    generar("Start", "", "", "");
}

void terminar()
{
    generar("Stop", "", "", "");
}

void generar(char *operacion, char *a, char *b, char *c)
{
    fprintf(fuente, "%s %s,%s,%s\n", operacion, a, b, c);
}

/*Devuelve un registro de expresión.*/
struct reg_expr procesar_id()
{
    chequear(yytext);

    struct reg_expr registro;
    registro.clase = ID;

    copiarLexema(yytext, registro.nombre);
    /*registro.nombre = yytext;*/
    registro.valor = 0;

    return registro;
}
