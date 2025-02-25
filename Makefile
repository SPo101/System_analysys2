FUNCTIONS = help.c error.c log.c users.c processes.c main.c

all: 
	@cc $(FUNCTIONS) -c
	@cc $(FUNCTIONS:.c=.o) -o executable
	
clean:
	@rm -f *.o executable
