#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include "structs.h"

struct Data* Show_users(){
	int fd = open("/etc/passwd", O_RDONLY);

	int offset = lseek(fd, 0, SEEK_END);
	lseek(fd, 0, SEEK_SET);
	
	char *string = malloc(offset);
	read(fd, string, offset);
	int cnt_next = 0;
	for(int i=0; i<offset; i++)
		if(string[i] == '\n')
			cnt_next+=1;

	size_t pplace = strcspn(string, "\n");//previous place
	size_t place = strcspn(string, ":");
	if(place > pplace){ //if have garbage like header in the top
		for(int i=place; i>0; i--)
			if(*(string+i) == '\n'){
				pplace = place = i+1;
				break;
			}
	}
	else
		pplace = place = 0;
	if(place)
		for(int i=place; i>0; i--)
			if(*(string+i) == '\n')
				cnt_next--;
	
	struct Data *Users = malloc(sizeof(struct Data));
	Users->data = malloc(cnt_next*2);
	Users->len = cnt_next*2;

	
	size_t cnt_d = 0;
	size_t i = 0;
	size_t ok = 1;
	while(place <= offset){
		place++;
		if( *(string+place) == ':')
			cnt_d++;
		if( *(string+place) == '\n'){
			cnt_d=0;
			pplace = place+1;
			ok = 1;
		}
		if(cnt_d == 4){
			pplace = place+2;
			ok = 1;
		}
			
		if( (cnt_d == 1 || cnt_d == 6) && ok ){ //if its name or home dir
			Users->data[i] = malloc(place-pplace+10);
			memset(Users->data[i], 0, place-pplace+10);
			memcpy(Users->data[i], string+pplace, place-pplace);
			pplace = place+1;
			i++;
			ok = 0;
		}
	}

	free(string);
	close(fd);
	return Users;
}
