#include <stdlib.h>
#include <stdio.h>
#include "scanner.h"
/*Sintaxis y Semantica de los Lenguajes: TP2
Curso: Viernes-Noche*/

/*Definicion de prototipos.*/
void encabezado();

int main()
{
    /*Guardo los nombres de los tokens.*/
    char *nombresToken[20] = {"Inicio","Fin","Leer","Escribir",
        "Identificador","Constante","ParenIzquierdo","ParenDerecho",
        "PuntoYComa", "Coma", "Asignacion", "Suma",
        "Resta", "Multiplicacion", "Division", "Comentario",
        "FinDeTexto", "ErrorLexico", "ErrorAsignacion", "ErrorConstante"};
    
    /*Guardo el token actual (numero).*/
    token tokenActual = INICIO;
    encabezado();
    printf("[Scanner]: Reconociendo lexemas...\n\n");
       
    /*Llamo al Scanner para que recorra el archivo de texto.*/
    while(tokenActual != FDT)
    {
        /*Llamo a scanner para que lea el siguiente lexema y me devuelva
        el token correspondiente.*/
        tokenActual = scanner();
        /*Imprimo la informacion correspondiente al token leido.*/
        printf("Lexema: %s\n", yytext);
        printf("Token : %s\n", nombresToken[tokenActual]);
    }

    printf("\n[Scanner]: Trabajo terminado.\n");
}

/*Imprime un bonito encabezado al principio del programa :v*/
void encabezado()
{
    puts("*******************************************************");
    puts("*Sintaxis y Semantica de Lenguajes - UTN K2055 Grupo 3*");
    puts("*     COMPILADOR DE LENGUAJE MICRO - Scanner          *");
    puts("*******************************************************");
}
