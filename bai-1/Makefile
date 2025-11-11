all: static shared
	@echo "Full build."
static: bstrutils.c main.c strutils.h
	gcc -c bstrutils.c -o bstrutils.o
	ar rcs libstrutils.a bstrutils.o 
	gcc main.c -L. -lstrutils -o main_static
shared: bstrutils.c main.c strutils.h
	gcc -c -fPIC bstrutils.c -o bstrutils.o
	gcc -shared bstrutils.o -o libstrutils.so
	gcc main.c -L. -lstrutils -o main_shared 
clean: 
	rm bstrutils.o libstrutils.so libstrutils.a main_static main_shared