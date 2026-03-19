all : program run

program : 
	gcc operations.c main.c logger.c -o program

run: 
	./program

clean: 
	rm -f program
