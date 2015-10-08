#include <stdlib.h>
#include <stdio.h>
#include "parser.h"
#include "scanner.h"
#include "error.h"

/*En este fuente están las implementaciones de todas las Producciones de Análisis Sintáctico.*/

/*<objetivo> -> <programa> FDT*/
void objetivo()
{
    programa();
    match(FDT);
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
            match(ID); 
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
    match(ID);
    while(proximoToken() == COMA)
    {
        match(COMA);
        match(ID);
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
            match(ID);
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

/*Informa la existencia de un error sintáctico (se obtuvo un token que no se esperaba).*/
void errorSintactico(token tokenObtenido)
{
    printf("%2d-\e[1;31m[X]\e[0m: No se esperaba el token \e[1;31m%s\e[0m.\n", numeroLinea, nombresToken[tokenObtenido]);
}
