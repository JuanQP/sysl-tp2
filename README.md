## Trabajo Práctico Número 2

Hay que armar un compilador (modificado) del lenguaje Micro siguiendo las instrucciones mencionadas en los [apuntes][3].

**Fecha de Primer Entrega: 18/09/2015**

## Teoría necesaria

### Primer entrega: Scanner

La primer entrega del TP requiere tener un Scanner listo. Es decir, que tiene que poder leer los caracteres
de un código de fuente del lenguaje Micro, y a medida que va leyendo tiene que poder *entender* las palabras que lee y clasificarlas. Es decir
que debería poder ser capaz de (por ejemplo) al leer `:=` lo guarde en una tabla de lexemas (palabras reconocidas) y que la clasifique como
*ASIGNACION*.

El [capítulo 3][1] es necesario para entender qué es una BNF (qué es un lexema, qué es una gramática léxica de un lenguaje, etc...).

El [capítulo 8][2] (hasta la hoja 17 inclusive) es necesario para entender el comportamiento de un compilador y ver el pseudocódigo que explica el funcionamiento de un compilador del lenguaje Micro. Esas 17 hojas explican el funcionamiento de la primer etapa de un compilador: el **Scanner**. 

**Gramática Léxica**

|Nombre|Descripción|
|:----:|-----------|
|token | **uno de** identificador constante palabraReservada operadorAditivo asignacion caracterPuntuacion|
|identificador| letra {letra o digito}|
|letra o digito| uno de letra digito|
|letra| una de a-z A-Z|
|digito| uno de 0-9|
|palabraReservada| **uno de** inicio fin leer escribir|
|operadorAditivo| **uno de** + -|
|operadorMultiplicativo| **uno de** *asterisco* /|
|asignacion| := |
|caracterPuntuacion| **uno de** ( ) , ;|

### Como ejecutar el programa

En Linux

Hay que bajar el proyecto, luego entrar en la carpeta Fuentes. Primero hay que hacer el makefile que se va a encargar de compilar los
fuentes que son necesarios y generar el ejecutable. Desde la terminal hacer lo siguiente:

```bash
[juan Fuentes]$ make
[juan Fuentes]$ ./Compilador < input
```

La primer línea compila `main.c` y `scanner.c`.
La segunda línea ejecuta la aplicación con `./Compilador` y luego le pasa lo que tiene el archivo "input" dentro.

Se puede modificar el archivo "input" o crear otro archivo para escribirle otro código y probar el compilador.

[1]: https://www.dropbox.com/sh/nr1zia5bz1tgdu0/AAAbIArF7-gDmO9FcUCuqv3Da/Apuntes%20y%20Ejercicios/03-SintaxisBNF.pdf?dl=0
[2]: https://www.dropbox.com/sh/nr1zia5bz1tgdu0/AADuFldyjY-BjwPTU7A9VU9pa/Apuntes%20y%20Ejercicios/08-ProcesoCompilaci%C3%B3n.pdf?dl=0
[3]: http://ur1.ca/h9w5u