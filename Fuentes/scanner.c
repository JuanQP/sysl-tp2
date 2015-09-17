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
    int tablaTransicion[22][16] = 
    {
    { 1, 3, 5, 6, 7, 8, 9,10,11,14,13, 0,14,16,17, 0},/*0: Inicio.*/
    { 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,14, 2, 2, 2},/*1: Reconociendo identificador.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*2: Identificador reconocido.*/
    {14, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,14, 4, 4, 4},/*3: Reconociendo constante.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*4: Constante reconocida.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*5: Operador suma.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*6: Operador resta.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*7: Paréntesis izquierdo.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*8: Paréntesis derecho.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*9: Coma.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*10: Punto y coma.*/
    {21,21,21,21,21,21,21,21,21,12,21,21,21,21,21,21},/*11: Reconociendo operador asignación.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*12: Operador asignación reconocido.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*13: Fin de texto.*/
    {14,14,14,14,14,14,14,14,14,14,15,15,14,14,14,15},/*14: Está reconociendo un error léxico. Sale por FDT, espacio o nueva linea.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*15: Error léxico reconocido.*/ 
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*16: Operador multiplicativo.*/
    {18,18,18,18,18,18,18,18,18,18,18,18,14,18,19,18},/*17: Barra puede ser comentario o division.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*18: Operador division reconocido.*/
    {19,19,19,19,19,19,19,19,19,19,19,19,19,19,19,20},/*19: Reconociendo comentario (tiene //).*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*20: Comentario reconocido.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*21: Error de asignación.*/
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
                /*Si la letra recien leida es = o / significa que puede ser un lexema
                compuesto. Por lo tanto, voy a agregar dicho caracter y no lo voy
                a devolver.*/
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
            else
            {
                /*Si estoy reconociendo un comentario, acepto espacios.*/
                if(estado == 19 && letra == ' ')
                {
                    buffer[i] = letra;
                    i++;
                }
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
        case 15:
        case 16:
        case 18:
        case 20:
        case 21:
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

    if(letra == ' ')    return 11;
    
    if(letra == '*')    return 13;
    
    if(letra == '/')    return 14;

    if(letra == '\n')   return 15;
    
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

    if(estado == 15)    return ERRORLEXICO;

    if(estado == 16)    return MULTIPLICACION;

    if(estado == 18)    return DIVISION;

    if(estado == 20)    return COMENTARIO;
    
    if(estado == 21)    return ERRORASIG;

}
