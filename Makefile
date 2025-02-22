FUNCTIONS = help.c error.c log.c users.c processes.c main.c
SHARED_FUNC = $(FUNCTIONS:.c=.so)
FLAGS = -shared -o

all: 
	@cc $(FUNCTIONS) -c
	@cc $(FUNCTIONS:.c=.o) -o executable
	
clean:
	@rm -f *.o *.so
