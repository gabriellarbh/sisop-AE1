teste: ./src/bfila.c libfila2.a ./include/fila2.h
	gcc -o teste ./src/bfila.c -I./include -L./lib -lfila2 -Wall

libfila2.a: fila2.o 
	ar crs ./lib/libfila2.a fila2.o

fila2.o: ./src/fila2.c ./include/fila2.h
	gcc -c -I./include ./src/fila2.c -Wall
 clean : 
	rm *.o 
	rm lib/*.a 
	rm teste
