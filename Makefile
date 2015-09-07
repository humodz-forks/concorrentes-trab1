all:	 JR.o concorrentes.o 
	@g++  JR.o  concorrentes.o -o concorrentes -lpthread

JR.o:
	@g++ -Wall -c JR.c -lpthread

concorrentes.o:
	@g++  -Wall -c concorrentes.c

clean:
	@rm *.o concorrentes
	@rm -r out/*/*/*
run:
	@./concorrentes
