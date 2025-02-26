FUNCTIONS = help.c error.c log.c users.c processes.c main.c

all: check_dir
	@cc $(FUNCTIONS) -c 
	@cc $(FUNCTIONS:.c=.o) -o executable
	@mv *.o ./.obj
	@mv executable ./.build
	
check_dir:
	@./create_dirs.sh
clean:
	@rm -fr .obj .build *.o
