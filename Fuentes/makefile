#Espera que este listo el ejecutable del compilador.
all: Compilador

#Permite hacer una prueba con el archivo prueba.
test: Compilador
	./Compilador < input

#Compila los objetos main y scanner para crear el ejecutable Compilador
Compilador: main.o scanner.o parser.o
	gcc -o Compilador main.o scanner.o parser.o

#Genera el objeto main a partir del fuente main.c
main.o: main.c
	gcc -ansi -c main.c

#Genera el objeto scanner a partir del fuente scanner.c y su header scanner.h
scanner.o: scanner.c scanner.h
	gcc -ansi -c scanner.c

#Genera el objeto parser
parser.o: parser.c parser.h
	gcc -ansi -c parser.c

#Borra los archivos object generados por la compilacion.
clean:
	rm -f *.o
