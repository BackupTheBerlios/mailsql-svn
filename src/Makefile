main: main.o socketfactory.o
	gcc -o main main.o socketfactory.o

main.o: main.c
	gcc -c main.c -Wall

socketfactory.o: socketfactory.c socketfactory.h
	gcc -c socketfactory.c -Wall

prof: main.c socketfactory.c
	gcc -c main.c socketfactory.c -pg -g
	gcc -o main socketfactory.o main.o

parser-prof: xmlparser.c
	gcc -c xmlparser.c `xml2-config --cflags` -pg -g -Wall
	gcc -o xmlparser xmlparser.o `xml2-config --libs` -pg


xmlparser.o: xmlparser.c xmlparser.h
	gcc -c xmlparser.c `xml2-config --cflag`

xmlparser:xmlparser.c xmlparser.h
	gcc -c xmlparser.c `xml2-config --cflags` -DDEBUG=1
	gcc -o xmlparser xmlparser.o `xml2-config --libs` 

clean: 
	rm *.o
