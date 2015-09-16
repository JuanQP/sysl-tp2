#include <stdio.h>
#include "scanner.h"
#include <ctype.h>

static char buffer[100];
char *const yytext = buffer;
int columna(char);
int esAceptor(int);
token tokenCorrespondiente(int);

token prox_token()
{
    /*Codigo de prox_token.
    PARA LA SEGUNDA ENTREGA.*/
}

void match(token tok)
{
    /*Codigo que permita hacer match.
    PARA LA SEGUNDA ENTREGA.*/
}

token scanner()
{
    int i = 0;
    int estado = 0;
    int proximoEstado = 0;
    char letra = '\0';
    
    /*Defino la tabla de transición (Leer documentación).*/
    int tablaTransicion[15][13] = 
    {
    { 1, 3, 5, 6, 7, 8, 9,10,11,14,13, 0,14},
    { 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2},
    {99,99,99,99,99,99,99,99,99,99,99,99,99},
    { 4, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4},
    {99,99,99,99,99,99,99,99,99,99,99,99,99},
    {99,99,99,99,99,99,99,99,99,99,99,99,99},
    {99,99,99,99,99,99,99,99,99,99,99,99,99},
    {99,99,99,99,99,99,99,99,99,99,99,99,99},
    {99,99,99,99,99,99,99,99,99,99,99,99,99},
    {99,99,99,99,99,99,99,99,99,99,99,99,99},
    {99,99,99,99,99,99,99,99,99,99,99,99,99},
    {14,14,14,14,14,14,14,14,14,12,14,14,14},
    {99,99,99,99,99,99,99,99,99,99,99,99,99},
    {99,99,99,99,99,99,99,99,99,99,99,99,99},
    {99,99,99,99,99,99,99,99,99,99,99,99,99}
    };   
    
    letra = getchar();

    /*Mientras no se haya reconocido FDT.*/
    while(estado != 13)
    {
        proximoEstado = tablaTransicion[estado][columna(letra)];
        if (esAceptor(proximoEstado))
        {
            estado = proximoEstado;
            ungetc(letra, stdin);
            break;
        }
        estado = proximoEstado;
        
        /*Los espacios se ignoran.*/
        if(letra != ' ' && letra != '\n')
        {
            buffer[i] = letra;
            i++;
        }
        letra = getchar();
    }
    
    buffer[i]='\0';
    return tokenCorrespondiente(estado);
}

/*Informa si el estado pasado por parametro es estado aceptor.*/
int esAceptor(int estado)
{
   switch(estado)
    {
        case 2:
        case 4:
        case 5:
        case 6:
        case 7:
        case 8:
        case 9:
        case 10:
        case 12:
        case 13:
            return 1;
            break;
        default:
            break;
    }
    
    /*Llegado a esta instancia devuelve falso.*/
    return 0;
}

/*Devuelve el indice de la columna que le corresponde al caracter.*/
int columna(char letra)
{
    if(isalpha(letra))
    {
        return 0;
    }
    if(letra == ' ')
    {
        return 11;
    }
    if(letra == EOF)
    {
        return 10;
    }
}

/*Informa si la palabra pasada por parametro es una palabra reservada.*/
int esPalabraReservada(char *letra)
{
    
}

token tokenCorrespondiente(int estado)
{
    if(estado == 2)
    {
        return ID;
    }

    if(estado == 13)
    {
        return FDT;
    }
}
