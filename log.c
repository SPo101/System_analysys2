#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include "structs.h"

int Log_into(char *path, struct Data* (*Functions[]) (), int cnt){
	int fd = open(path, O_WRONLY|O_APPEND|O_CREAT, 0600);
	if(fd == -1){
		perror("Log: Error with opening file");
		exit(EXIT_FAILURE);
	}

	struct Data *func;
	for(int i=0; i<cnt; i++)
		if(Functions[i] != NULL){
			func = Functions[i]();
			if(func->data == NULL){
				printf("No data yet!\n");
				free(func);
				continue;
			}

			for(int j=0; j<func->len; j++){
				if(i!=1)
					dprintf(fd, "%s\n", func->data[j]);
				else{//for users and their dirs
					dprintf(fd, "%30s", func->data[j]);
					if(j%2!=0)
						dprintf(fd, "\n");
				}
			}
			free(func);
		}

	close(fd);
	return 0;
}
