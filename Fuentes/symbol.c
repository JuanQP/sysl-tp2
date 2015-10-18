#include "scanner.h"
#include "symbol.h"

void copiarLexema(char*, char*);

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
    
    copiarLexema(lexema, nuevoSimbolo.lexema);
    /*nuevoSimbolo.lexema = lexema;*/
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
        printf("%2d-\e[1;34m[D]\e[0m: Se va a definir la variable \e[1;32m%s\e[0m.\n", numeroLinea, lexema);
        generar("Declare", lexema, "Integer", "");
    }
}

/*Ingresa en el diccionario las palabras reservadas.*/
void inicializarDiccionario()
{
    struct ts_entry inicio;
    copiarLexema("inicio", inicio.lexema);
    inicio.tok = INICIO;

    struct ts_entry fin;
    copiarLexema("fin", fin.lexema);
    fin.tok = FIN;

    struct ts_entry leer;
    copiarLexema("leer", leer.lexema);
    leer.tok = LEER;

    struct ts_entry escribir;
    copiarLexema("escribir", escribir.lexema);
    escribir.tok = ESCRIBIR;

    tabla_simb[0] = inicio;
    tabla_simb[1] = fin;
    tabla_simb[2] = leer;
    tabla_simb[3] = escribir;

    ultimoElemento = 4;
}

void copiarLexema(char *fuente, char *destino)
{
    int indice = 0;
    while (fuente[indice] != '\0')
    {
        destino[indice] = fuente[indice];
        indice++;
    }
    destino[indice] = '\0';
}
