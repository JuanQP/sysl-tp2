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
void termino(struct reg_expr *preg);
void expresion(struct reg_expr *preg);
void primaria(struct reg_expr *preg);
void operadorAditivo(struct reg_op *preg);
void operadorMultiplicativo(struct reg_op *preg);
void identificador(struct reg_expr *preg);

#endif
