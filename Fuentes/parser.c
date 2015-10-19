#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "scanner.h"
#include "error.h"
#include "semantic.h"
#include "symbol.h"

/*En este fuente están las implementaciones de todas las Producciones de Análisis Sintáctico.*/

/*<objetivo> -> <programa> FDT #terminar*/
void objetivo()
{
    /*Agrego las palabras reservadas al diccionario.*/
    inicializarDiccionario();

    programa();
    match(FDT);
    terminar();
}

/*<programa> -> #comenzar INICIO <listaSentencias> FIN*/
void programa()
{
    comenzar();
    match(INICIO);
    listaSentencias();
    match(FIN);
}

/* <listaSentencias> -> <sentencia> {<sentencia>} */
void listaSentencias () 
{
    sentencia();
    
    while (1)
    {
        switch (proximoToken()) 
        {
            case ID:
            case LEER:
            case ESCRIBIR:
                sentencia();
                break;
            default:
                return;
        }
    }
}

/*<sentencia> -> <identificador := <expresion> #asignar ; |
                read ( <listaIdentificadores> ) ; |
                write ( <listaExpresiones> ) ;*/
void sentencia() 
{
    struct reg_expr registroI;
    struct reg_expr registroD;
    token tokenProximo = proximoToken();
    switch (tokenProximo) 
    {
        case ID: /* <sentencia> -> ID := <expresion>; */
            identificador(&registroI);
            match(ASIGNACION);
            expresion(&registroD);
            asignar(&registroI, &registroD);
            match(PUNTOYCOMA);
            break;
        case LEER: /* <sentencia> -> LEER ( <listaIdentificadores> ); */
            match(LEER);
            match(PARENIZQUIERDO);
            listaIdentificadores();
            match(PARENDERECHO); 
            match(PUNTOYCOMA);
            break;
        case ESCRIBIR: /* <sentencia> -> ESCRIBIR (<listaExpresiones>); */
            match(ESCRIBIR); 
            match(PARENIZQUIERDO);
            listaExpresiones();
            match(PARENDERECHO); 
            match(PUNTOYCOMA);
            break;
        default:
            errorSintactico(tokenProximo, "ID, LEER o ESCRIBIR");
            break;
    }
}

/*<listaIdentificadores> -> <identificador> #leer_id {, <identificador> #leer_id}*/
void listaIdentificadores()
{
    struct reg_expr registro;
    identificador(&registro);
    leer_id(&registro);

    while(proximoToken() == COMA)
    {
        match(COMA);
        identificador(&registro);
        leer_id(&registro);
    }
}

/* <listaExpresiones> → <expresión> #escribir_exp {, <expresión>} */
void listaExpresiones () 
{
    struct reg_expr registro;
    expresion(&registro);
    escribir_exp(&registro);
    while (proximoToken() == COMA) 
    {
        match(COMA);
        expresion(&registro);
        escribir_exp(&registro);
    }
}

/* <primaria> → <identificador> | CONSTANTE #procesar_cte | ( <expresión> )*/
void primaria(struct reg_expr *preg) 
{
    struct reg_expr registroSalida;    
    token tokenProximo = proximoToken();
    switch (tokenProximo) 
    {
        case ID:
            identificador(preg);
            break;
        case CONSTANTE:
            match(CONSTANTE);
            registroSalida = procesar_cte();
            *preg = registroSalida;
            break;
        case PARENIZQUIERDO:
            match(PARENIZQUIERDO);
            expresion(preg);
            match(PARENDERECHO);
            break;
        default:
            errorSintactico(tokenProximo, "ID, CONSTANTE o PARENIZQUIERDO");
            break;
    }
}

/* <expresion> -> <termino> {<operadorAditivo> <termino> #gen_infijo} */
void expresion (struct reg_expr *preg)
{
    struct reg_expr operandoIzq, operandoDer;
    struct reg_op op;
    token t;

    termino(&operandoIzq);
    for (t = proximoToken(); t == SUMA || t == RESTA; t = proximoToken()) 
    {
        operadorAditivo(&op);
        termino(&operandoDer);
        operandoIzq = gen_infijo(&operandoIzq, &op, &operandoDer);
    }

    *preg = operandoIzq;
}

/*<termino> -> <primaria> { <operadorMultiplicativo> <primaria> #gen_infijo}*/
void termino(struct reg_expr *preg)
{
    struct reg_expr operandoIzq, operandoDer;
    struct reg_op op;
    token t;

    primaria(&operandoIzq);
    for(t = proximoToken(); t == MULTIPLICACION || t == DIVISION; t = proximoToken())
    {
        operadorMultiplicativo(&op);
        primaria(&operandoDer);
        operandoIzq = gen_infijo(&operandoIzq, &op, &operandoDer);
    }

    *preg = operandoIzq;
}

/*<operadorAditivo> -> SUMA #procesar_op | RESTA #procesar_op*/
void operadorAditivo(struct reg_op *preg)
{
    struct reg_op registroSalida;
    token tokenProximo = proximoToken();
    switch(tokenProximo)
    {
        case SUMA:
            match(SUMA);
            registroSalida = procesar_op();
            *preg = registroSalida;
            break;
        case RESTA:
            match(RESTA);
            registroSalida = procesar_op();
            *preg = registroSalida;
            break;
        default:
            errorSintactico(tokenProximo, "SUMA o RESTA");
            break;
    }
}

/*<operadorMultiplicativo> -> MULTIPLICACION #procesar_op | DIVISION #procesar_op*/
void operadorMultiplicativo(struct reg_op *preg)
{
    struct reg_op registroSalida;
    token tokenProximo = proximoToken();
    switch(tokenProximo)
    {
        case MULTIPLICACION:
            match(MULTIPLICACION);
            registroSalida = procesar_op();
            *preg = registroSalida;
            break;
        case DIVISION:
            match(DIVISION);
            registroSalida = procesar_op();
            *preg = registroSalida;
            break;
        default:
            errorSintactico(tokenProximo, "MULTIPLICACION o DIVISION");
            break; 
    }
}

/*<identificado> -> ID #procesar_ID*/
void identificador(struct reg_expr *registro)
{
    token tokenProximo = proximoToken();
    match(ID);
    struct reg_expr salida = procesar_id();
    *registro = salida;
}
