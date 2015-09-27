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
    char *nombresToken[20] = {"PalabraReservada INICIO","PalabraReservada FIN","PalabraReservada LEER","PalabraReservada ESCRIBIR",
        "Identificador","Constante","ParentesisIzquierdo","ParentesisDerecho",
        "PuntoYComa", "Coma", "Asignacion", "Suma",
        "Resta", "Multiplicacion", "Division", "Comentario",
        "FinDeTexto", "ErrorLexico", "ErrorAsignacion", "ErrorDeConstante"};
    
    /*Inicializo el token actual con cualquier valor.*/
    token tokenActual = INICIO;
    
    /*Imprimo un encabezado.*/
    encabezado();
    printf("[Scanner]: Reconociendo lexemas...\n\n");
     
    /*Itero mientras no se haya reconocido el token de Fin de Texto.*/
    while(tokenActual != FDT)
    {
        /*Llamo a scanner para que lea el siguiente lexema y me devuelva
        el token correspondiente.*/
        tokenActual = scanner();
        /*Imprimo la informacion correspondiente al token leido.*/
        printf("Linea %d: '%s' - ", numeroLinea,  yytext);
        printf("Token: %s\n", nombresToken[tokenActual]);
    }

    printf("\n[Scanner]: Trabajo terminado.\n");

    return 0;
}

/*Imprime un bonito encabezado al principio del programa :v*/
void encabezado()
{
    puts("┌─────────────────────────────────────────────────────┐");
    puts("│Sintaxis y Semantica de Lenguajes - UTN K2055 Grupo 4│");
    puts("│     COMPILADOR DE LENGUAJE MICRO - Scanner          │");
    puts("└─────────────────────────────────────────────────────┘");
}
