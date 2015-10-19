#include "symbol.h"
#include "scanner.h"
#include "semantic.h"
#include <stdio.h>
#include <stdlib.h>

int numeroVariableTemporal = 0;
void nombreVariableTemporal(char*);
void nombreOperacion(struct reg_op*, char*);

void comenzar()
{
    generar("Start", "", "", "");
}

void terminar()
{
    generar("Stop", "", "", "");
}

/*Genera código de pseudo-assembler y lo escribe en el fuente.*/
void generar(char *operacion, char *a, char *b, char *c)
{   
    fprintf(fuente, "%s %s, %s, %s\n", operacion, a, b, c);
}

void asignar(struct reg_expr *vizq, struct reg_expr *vder)
{
    generar("Store", vder->nombre, vizq->nombre, "");
}

/*Chequea la existencia del lexema actual, y luego crea el registro de expresión correspondiente..*/
struct reg_expr procesar_id()
{
    chequear(yytext);

    struct reg_expr registro;
    registro.clase = ID;
    copiarLexema(yytext, registro.nombre);
    registro.valor = 0;
    return registro;
}

/*Crea el registro de expresión correspondiente para la constante recién leída.*/
struct reg_expr procesar_cte()
{
    struct reg_expr registro;
    registro.clase = CONSTANTE;
    copiarLexema(yytext, registro.nombre);
    registro.valor = 0;
    return registro;
}

/*Crea el registro de operación correspondiente a la operación aritmética correspondiente.*/
struct reg_op procesar_op()
{
    struct reg_op registro;
    switch(tokenActual)
    {
        case SUMA:
            registro.cod_oper = SUMA;
            break;
        case RESTA:
            registro.cod_oper = RESTA;
            break;
        case MULTIPLICACION:
            registro.cod_oper = MULTIPLICACION;
            break;
        case DIVISION:
            registro.cod_oper = DIVISION;
            break;
    }
    
    return registro;
}

void leer_id(struct reg_expr *pin)
{
    generar("Read", extraer(pin), "Integer", "");
}

void escribir_exp(struct reg_expr *pout)
{
    generar("Write", extraer(pout), "Integer", "");
}

/*Genera el código de pseudo-assembler de una expresión.*/
struct reg_expr gen_infijo(struct reg_expr *pei, struct reg_op *op, struct reg_expr *ped)
{
    struct reg_expr salida;

    /*Genero el nombre de la variable temporal donde voy a almacenar el resultado.*/
    char variable[12];
    nombreVariableTemporal(variable);

    /*Obtengo el nombre de la operación.*/
    char operacion[4];
    nombreOperacion(op, operacion);

    /*Si alguno de los registros de expresión es un identificador, entonces lo chequeo.*/
    if(pei->clase == ID) chequear(pei->nombre);
    if(ped->clase == ID) chequear(ped->nombre);
    chequear(variable);
    
    /*Genero el código de pseudo-assembler.*/
    generar(operacion, pei->nombre, ped->nombre, variable);
    
    /*Armo el registro correspondiente a la operación recién realizada.*/
    copiarLexema(variable, salida.nombre);
    salida.clase = ID;
    salida.valor = 0;

    /*Incremento el numero de variable temporal utilizada.*/
    numeroVariableTemporal++;

    return salida;
}

/*Genera el nombre de la variable temporal correspondiente (incrementa un valor numérico al final).*/
void nombreVariableTemporal(char *var)
{
    sprintf(var, "VarTemp%d", numeroVariableTemporal);
}

/*Genera el nombre de la operación correspondiente a un código de operación de un registro de operación.*/
void nombreOperacion(struct reg_op *registro, char *nom)
{
    switch(registro->cod_oper)
    {
        case SUMA:
            sprintf(nom, "ADD");
            break;
        case RESTA:
            sprintf(nom, "SUBS");
            break;
        case MULTIPLICACION:
            sprintf(nom, "MULT");
            break;
        default:
            sprintf(nom, "DIV");
            break;
    }
}

/*Obtiene el lexema de un registro de expresión.*/
char *extraer(struct reg_expr *preg)
{
    char *salida = preg->nombre;
    return preg->nombre;
}
