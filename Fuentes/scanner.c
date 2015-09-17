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
    /*Mientras no estè en estado aceptor.*/
    while(!esAceptor(estado))
    {
	/*Consulto cual es el proximo estado.*/
        proximoEstado = tablaTransicion[estado][columna(letra)];
        
	/*El proximo estado es aceptor.*/
	if (esAceptor(proximoEstado))
        {
	    /*Si estaba en el estado 0, significa que va a reconocer un lexema de 1 caracter.
	    Por lo tanto, el caracter recien leido es el lexema.*/
	    if(estado == 0)
	    {
		buffer[i] = letra;
                i++;
	    }
	    /*Si no estaba en el estado 0, significa que estaba reconociendo un lexema
	    que está compuesto por más de 1 caracter.
            Puede ocurrir que tenga que devolver el centinela o que tenga que quedarse
            con el caracter si es uno compuesto como := */
	    else
	    {
                /*Si la letra recien leida es = significa que es estado aceptor de := */
	        if(letra == '=')
                {
                    buffer[i] = letra;
                    i++;
		}
                /*Caso contrario, es cualquier otro de los lexemas que necesitan un centinela,
                y como acabo de leer un centinela, tengo que devolverlo.*/
		else
		{
                    ungetc(letra, stdin);
		}
	    }
        }

        /*El estado no es aceptor.*/
        else
	{
	    /*Si no es un espacio o nueva línea, lo pongo en el string.*/
	    if(letra != ' ' && letra != '\n')
	    {
	        buffer[i] = letra;
		i++;
	    }
            
            /*Leo el proximo caracter.*/
            letra = getchar();
	}

        /*Asigno el estado en el que se encuentra. Si es aceptor, deja de iterar.*/
	estado = proximoEstado;
    }

    /*Pongo el fin de línea en el lexema.*/
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
    if(isalpha(letra))  return 0;

    if(isdigit(letra))  return 1;    
    
    if(letra == '+')    return 2;

    if(letra == '-')    return 3;
    
    if(letra == '(')    return 4;

    if(letra == ')')    return 5;
    
    if(letra == ',')    return 6;
    
    if(letra == ';')    return 7;

    if(letra == ':')    return 8;
    
    if(letra == '=')    return 9;
    
    if(letra == EOF)    return 10;

    if(letra == ' ' || letra == '\n')    return 11;

    /*Si llego hasta aca es porque es "cualquier otra cosa".*/
    return 12;
}

/*Informa si la palabra pasada por parametro es una palabra reservada.*/
int esPalabraReservada(char *letra)
{
    /*Falta código.*/
}

/*Una vez obtenido el estado final (se finalizo de reconocer la palabra), 
se devuelve el token correspondiente a dicho estado final.*/
token tokenCorrespondiente(int estado)
{
	
    if(estado == 2)     return ID;
    
    if(estado == 4)	return CONSTANTE;
    
    if(estado == 5)	return SUMA;

    if(estado == 6)	return RESTA;

    if(estado == 7)	return PARENIZQUIERDO;

    if(estado == 8)	return PARENDERECHO;

    if(estado == 9)	return COMA;

    if(estado == 10)	return PUNTOYCOMA;

    if(estado == 12)	return ASIGNACION;
	
    if(estado == 13)	return FDT;
}
