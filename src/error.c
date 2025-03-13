#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "structs.h"

int Error_into(char *path, struct Data* (*Functions[]) (), int cnt){
	int fd = open(path, O_WRONLY|O_APPEND|O_CREAT);
	if(fd == -1){
		perror("Log error:Error with opening file");
		exit(EXIT_FAILURE);
	}

	struct Data *func;
	for(int i=0; i<cnt; i++)
		if(Functions[i] != NULL){
			func = Functions[i]();
			if(func->errs == NULL){
				printf("No errors yet!\n");
				free(func);
				continue;
			}
				
			for(int j=0; j<func->len; j++)
				dprintf(fd, "%s\n", func->errs[j]);
			free(func);
		}

	close(fd);
	return 0;
}
