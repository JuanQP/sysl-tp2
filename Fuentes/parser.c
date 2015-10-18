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
    token tokenProximo = proximoToken();
    switch (tokenProximo) 
    {
        case ID: /* <sentencia> -> ID := <expresion>; */
            identificador();
            match(ASIGNACION);
            expresion();
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
            errorSintactico(tokenProximo);
            break;
    }
}

void listaIdentificadores()
{
    identificador();
    while(proximoToken() == COMA)
    {
        match(COMA);
        identificador();
    }
}

/* <listaExpresiones> → <expresión> {COMA <expresión>} */
void listaExpresiones () 
{
    expresion(); /* la primera de la lista de expresiones */
    while (proximoToken() == COMA) 
    { /* El resto de las opcionales */
        match(COMA);
        expresion();
    }
}

/* <primaria> → ID | CONSTANTE | PARENIZQUIERDO <expresión> PARENDERECHO */
void primaria() 
{
    token tokenProximo = proximoToken();
    switch (tokenProximo) 
    {
        case ID:
            identificador();
            break;
        case CONSTANTE:
            match(CONSTANTE);
            break;
        case PARENIZQUIERDO:
            match(PARENIZQUIERDO);
            expresion();
            match(PARENDERECHO);
            break;
        default:
            errorSintactico(tokenProximo);
            break;
    }
}

/* <expresion> -> <primaria> {<operadorAditivo> <primaria>} */
void expresion ()
{
    token t;
    termino();
    for (t = proximoToken(); t == SUMA || t == RESTA; t = proximoToken()) 
    {
        operadorAditivo();
        termino();
        /*Acá debería ir la generación de código (y declaración de variables).
        operandoIzq = generar(operandoIzq, operacion, operandoDerecho);*/
    }
}

/*Aca van los operadores multiplicativos.*/
void termino()
{
    token t;
    primaria();
    for(t = proximoToken(); t == MULTIPLICACION || t == DIVISION; t = proximoToken())
    {
        operadorMultiplicativo();
        primaria();
        /*Acá debería ir la geenración de código (y declaración de variables).
        operandoIzq = generar(operandoIzq, operacion, operandoDerecho);*/
    }
}

void operadorAditivo()
{
    token tokenProximo = proximoToken();
    switch(tokenProximo)
    {
        case SUMA:
            match(SUMA);
            break;
        case RESTA:
            match(RESTA);
            break;
        default:
            errorSintactico(tokenProximo);
            break;
    }
}

void operadorMultiplicativo()
{
    token tokenProximo = proximoToken();
    switch(tokenProximo)
    {
        case MULTIPLICACION:
            match(MULTIPLICACION);
            break;
        case DIVISION:
            match(DIVISION);
            break;
        default:
            errorSintactico(tokenProximo);
            break; 
    }
}

/*<identificado> -> ID #procesar_ID*/
void identificador()
{
    token tokenProximo = proximoToken();
    match(ID);
    procesar_id();
}
