#include "scanner.h"
#include "symbol.h"

/*Defino el largo del diccionario.*/
struct ts_entry tabla_simb[100];
int ultimoElemento = 0;
int i = 0;

int buscar(char *lexema, struct ts_entry *tablaSimbolos, token *tk)
{
    for(i = 0; i < ultimoElemento; i++)
    {
        if(sonIguales(lexema, tabla_simb[i].lexema))
        {
            *tk = tabla_simb[i].tok;
            return 1;
        }
    }
    return 0;
}

void colocar(char *lexema, struct ts_entry *tablaSimbolos)
{
    struct ts_entry nuevoSimbolo;
    nuevoSimbolo.lexema = lexema;
    nuevoSimbolo.tok = ID;
    
    tablaSimbolos[ultimoElemento] = nuevoSimbolo;
    ultimoElemento++;
}

void chequear(char *lexema)
{
    token tk = ID;
    if(!buscar(lexema, tabla_simb, &tk))
    {
        colocar(lexema, tabla_simb);
        /*Generar código de declaración*/
    }
}

/*Ingresa en el diccionario las palabras reservadas.*/
void inicializarDiccionario()
{
    struct ts_entry inicio;
    inicio.lexema = "inicio";
    inicio.tok = INICIO;

    struct ts_entry fin;
    fin.lexema = "fin";
    fin.tok = FIN;

    struct ts_entry leer;
    leer.lexema = "leer";
    leer.tok = LEER;

    struct ts_entry escribir;
    escribir.lexema = "escribir";
    escribir.tok = ESCRIBIR;

    tabla_simb[0] = inicio;
    tabla_simb[1] = fin;
    tabla_simb[2] = leer;
    tabla_simb[3] = escribir;

    ultimoElemento = 4;
}
