CC := /usr/bin/gcc
BDIR = ./.build/
SDIR = ./src/
ODIR = ./.obj/
FILES = help error log users processes main
EXE_NAME = executable

all: create_dir $(FILES)
	@$(CC) -o $(BDIR)$(EXE_NAME) $(ODIR)*
	
$(FILES):
	@$(CC) $(SDIR)$(@:%=%.c) -c -o $(ODIR)$(@:%=%.o)

create_dir:
	@./create_dirs.sh
clean:
	@rm -fr .obj .build
