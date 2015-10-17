#include <stdlib.h>
#include <stdio.h>
#include "scanner.h"
/*Sintaxis y Semantica de los Lenguajes: TP2
Curso: Viernes-Noche*/

/*Definicion de prototipos.*/
void encabezado();

FILE* fuente;

int main()
{
    /*Imprimo el encabezado.*/
    encabezado();
    printf("[Scanner]: Reconociendo lexemas...\n\n");
    
    /*Abro el archivo donde voy a escribir el fuente.*/
    fuente = fopen("fuente.assembler", "w");
    
    /*Llamo al analizador sintáctico.*/
    objetivo();

    printf("\n[Scanner]: Trabajo terminado.\n");
    fclose(fuente);
    return 0;
}

/*Imprime un bonito encabezado al principio del programa :v*/
void encabezado()
{
    printf("┌─────────────────────────────────────────────────────┐\n");
    printf("│       Universidad Tecnologica Nacional - FRBA       │\n");
    printf("│Sintaxis y Semantica de Lenguajes - UTN K2055 Grupo 4│\n");
    printf("│        COMPILADOR DE LENGUAJE MICRO - Parser        │\n");
    printf("└─────────────────────────────────────────────────────┘\n");
}
