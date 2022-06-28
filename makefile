compiler = gcc
parameters = -g -Wall -std=c99
program = gps

$(program): main.o libbike.o
	$(compiler) main.o libbike.o -o $(program) 

main.o : main.c 
	$(compiler) $(parameters) -c main.c

libbike.o : libbike.c
	$(compiler) $(parameters) -c libbike.c

clean :
	rm *.o $(program)