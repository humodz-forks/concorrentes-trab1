all:	 JR.o concorrentes.o 
	@g++  JR.o  concorrentes.o -o concorrentes -lpthread -g

JR.o:
	@g++ -Wall -c JR.c -lpthread -g

concorrentes.o:
	@g++  -Wall -c concorrentes.c -g

clean:
	@rm *.o concorrentes
	@rm -r out/*/*/*
run:
	@./concorrentes
