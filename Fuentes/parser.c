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
    inicializarDiccionario();
    comenzar();
    programa();
    match(FDT);
    terminar();
}

/*<programa> -> INICIO <listaSentencias> FIN*/
void programa()
{
    match(INICIO);
    listaSentencias();
    match(FIN);
}

/* <listaSentencias> -> <sentencia> {<sentencia>} */
void listaSentencias () 
{
    sentencia();
    
    while (1)
    { /* un ciclo indefinido */
        switch (proximoToken()) 
        {
            case ID:
            case LEER:
            case ESCRIBIR: /* detectó token correcto */
                sentencia(); /* procesa la secuencia opcional */
                break;
            default:
                return;
        } /* fin switch */
    }
}

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

/*Genera el código de cada uno de los identificadores pasado en LEER.*/
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

/* <listaExpresiones> → <expresión> {COMA <expresión>} */
void listaExpresiones () 
{
    struct reg_expr registro;
    expresion(&registro); /* la primera de la lista de expresiones */
    escribir_exp(&registro);
    while (proximoToken() == COMA) 
    { /* El resto de las opcionales */
        match(COMA);
        expresion(&registro);
        escribir_exp(&registro);
        /*#excribir_exp*/
    }
}

/* <primaria> → ID | CONSTANTE | PARENIZQUIERDO <expresión> PARENDERECHO */
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

/* <expresion> -> <primaria> {<operadorAditivo> <primaria>} */
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
        /*Acá debería ir la generación de código (y declaración de variables).*/
        operandoIzq = gen_infijo(&operandoIzq, &op, &operandoDer);
    }

    *preg = operandoIzq;
}

/*Aca van los operadores multiplicativos.*/
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
        /*Acá debería ir la geenración de código (y declaración de variables).*/
        operandoIzq = gen_infijo(&operandoIzq, &op, &operandoDer);
    }

    *preg = operandoIzq;
}

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
