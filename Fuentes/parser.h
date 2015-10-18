#ifndef PARSER_H_INCLUDED
#define PARSER_H_INCLUDED

#include "semantic.h"
#include "scanner.h"

void objetivo(void);
void programa(void);
void listaSentencias(void);
void sentencia(void);
void listaIdentificadores(void);
void listaExpresiones(void);

/*Los defino así momentáneamente para probar el analizador sintáctico.
void termino(void);
void expresion(void);
void primaria(void);
void operadorAditivo(void);
void operadorMultiplicativo(void);
void identificador(struct reg_expr *preg);*/

/*Los dejo comentados porque estos parametros son para el analizador semántico.*/
void termino(struct reg_expr *preg);
void expresion(struct reg_expr *preg);
void primaria(struct reg_expr *preg);
void operadorAditivo(struct reg_op *preg);
void operadorMultiplicativo(struct reg_op *preg);
void identificador(struct reg_expr *preg);

#endif
