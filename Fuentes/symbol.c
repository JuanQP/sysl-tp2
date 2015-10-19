#include "scanner.h"
#include "symbol.h"

void copiarLexema(char*, char*);

/*Defino el largo del diccionario.*/
struct ts_entry tabla_simb[100];
int ultimoElemento = 0;
int i = 0;

/*Busca un lexema en el diccionario, en caso de existir, corrige el token (sirve para las palabras reservadas).*/
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

/*Coloca un lexema en el diccionario y lo define como Identificador.*/
void colocar(char *lexema, struct ts_entry *tablaSimbolos)
{
    /*Creamos el nuevo registro para el nuevo símbolo.*/
    struct ts_entry nuevoSimbolo; 
    copiarLexema(lexema, nuevoSimbolo.lexema);
    nuevoSimbolo.tok = ID;
    
    /*Lo colocamos en la última posición.*/
    tablaSimbolos[ultimoElemento] = nuevoSimbolo;
    ultimoElemento++;
}

/*Verifica si existe un lexema, si no existe, lo agrega al diccionario.*/
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
    
    /*Dejo seteado que el último elemento ingresado fue el 4.*/
    ultimoElemento = 4;
}

/*Copia un lexema y lo guarda en otra variable.*/
void copiarLexema(char *fuente, char *destino)
{
    int indice = 0;
    while (fuente[indice] != '\0')
    {
        destino[indice] = fuente[indice];
        indice++;
    }
    /*Coloco como último símbolo el fin de string.*/
    destino[indice] = '\0';
}
