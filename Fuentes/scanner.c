#include <stdio.h>
#include "scanner.h"
#include <ctype.h>
#include <string.h>

/*Variables*/
static char buffer[100];
char *const yytext = buffer;
int numeroLinea = 1;

/*Defino la Tabla de Transicion como static para que solo sea visible en este fuente.
Para entender el funcionamiento de la tabla de transicion, es necesario leer la documentacion.*/
static int tablaTransicion[24][16] =
    {
    { 1, 3, 5, 6, 7, 8, 9,10,11,14,13, 0,14,16,17, 0},/*0: Inicio.*/
    { 1, 1, 2, 2, 2, 2, 2, 2, 2, 2, 2, 2,14, 2, 2, 2},/*1: Reconociendo identificador.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99},/*2: Identificador reconocido.*/
    {22, 3, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,22, 4, 4, 4},/*3: Reconociendo constante.*/
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
    {22,22,23,23,23,23,23,23,23,23,23,23,22,23,23,23},/*22: Reconociendo error de Constante.*/
    {99,99,99,99,99,99,99,99,99,99,99,99,99,99,99,99} /*23: Error de Constante reconocido.*/
    };

/*Prototipos de funcion*/
int requiereCentinela(int);
int columna(char);
int esAceptor(int);
token tokenCorrespondiente(int);
int sonIguales(char*, char*);
token verificarPalabraReservada();

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
    /*Indice para iterar en el buffer.*/
    int i = 0;
    int estado = 0;
    int proximoEstado = 0;

    /*La letra actualmente siendo scaneada.*/
    char letra = '\0';
    
    /*Obtengo la primer letra.*/
    letra = getchar();
    
    /*Mientras no estè en estado aceptor.*/
    while(!esAceptor(estado))
    {
        /*Verifico cual va a ser el proximo estado.*/
        proximoEstado = tablaTransicion[estado][columna(letra)];
        
        /*Si estoy en estado inicial, empiezo a contar las "nueva linea".
        Los espacios los ignoro.*/
        if(estado == 0 && (letra == '\n' || letra == ' '))
        {
            if(letra == '\n')
            {
                numeroLinea++;
            }
        }
        /*Si no estoy en el estado inicial, agrego al lexema actual la letra scaneada.*/
        else
        {
            buffer[i] = letra;
            i++;
        }

        estado = proximoEstado;

        /*Si estoy en un lexema que requiere centinela, al reconocerlo me voy inmediatamente
        del while, ya que significa que la letra actual tiene que ser devuelta..*/
        if(esAceptor(estado) && requiereCentinela(estado))
        {
            break;
        }
        
        letra = getchar();
    }
    /*Si el lexema requeria centinela, significa que el ultimo caracter leido no forma parte
    del lexema. Asi que decremento el indice para pisar esa ultima letra leida con un '\0'*/
    if(requiereCentinela(estado))
    {
        i--;
    }

    /*Devuelvo la ultima letra leida..*/
    ungetc(letra, stdin);
    /*En la ultima posicion pongo el fin de linea.*/
    buffer[i] = '\0';

    return tokenCorrespondiente(estado);
}

/*Algunos lexemas requieren centinela. Estos lexemas en particular salen del While llevandose
una letra "de mas" (el centinela). En estos casos necesito devolver ese ultimo caracter,
por eso necesito saber que estados requieren centinela.*/
int requiereCentinela(int estado)
{
    switch(estado)
    {
        case 2:     /*Identificador.*/
        case 4:     /*Constante.*/
        case 15:    /*Error lexico.*/
        case 20:    /*Comentario.*/
        case 23:    /*Error de constante.*/
            return 1;
            break;
        default:
            break;
    }

    /*Si no es ninguno de los casos mencionados entonces,
    entonces no es un lexema que requiera centinela.*/
    return 0;
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
        case 23:
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

/*Informa si la palabra pasada almacenada en el buffer es una palabra reservada.*/
token verificarPalabraReservada()
{
    
    if(sonIguales(buffer, "inicio"))    return INICIO;
    if(sonIguales(buffer, "fin"))       return FIN;
    if(sonIguales(buffer, "leer"))       return LEER;
    if(sonIguales(buffer, "escribir"))   return ESCRIBIR;

    /*Si llego hasta aca es porque no es palabra reservada.*/
    return ID;
}

/*Una vez obtenido el estado final (se finalizo de reconocer la palabra), 
se devuelve el token correspondiente a dicho estado final.*/
token tokenCorrespondiente(int estado)
{
    /*Es un identificador. Tenemos que ver si es palabra reservada.*/	
    if(estado == 2)
    {
        return verificarPalabraReservada();
    }
    
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
    
    if(estado == 23)    return ERRORCTE;
}

/*Verifica si dos lexemas son iguales.*/
int sonIguales(char *primerLexema, char *segundoLexema)
{
    return (strcmp(primerLexema, segundoLexema) == 0);
}
