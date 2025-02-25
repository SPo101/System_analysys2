#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "structs.h"

/*
void Show_users();
	return text, errors;

void Show_processes();
	return text, errors;

void Show_help();
	return text;

void Log_into();
	check path
	call show_smth
	write output into file

void Error_into();
	check path
	call show_smth
	wrire errors into file
*/

char* Show_help();
struct Data* Show_users();
struct Data* Show_processes();

int main(int argc, char *argv[]){

	if(argc < 2){
		//Help();
		exit(EXIT_FAILURE);
	}

	static struct option Long_options[] = {
		{"users", 	no_argument, 		0, 'u'},
		{"processes", 	no_argument, 		0, 'p'},
		{"help", 	no_argument, 		0, 'h'}, 
		{"log", 	required_argument, 	0, 'l'},
		{"errors", 	required_argument, 	0, 'e'}
	};
	static char *Short_options = "uphl:e:";
	int Option_index = 0;
	int cnt_args = sizeof(Long_options)/sizeof(struct option);
	char *Args[cnt_args];
	for(int i=0; i<cnt_args; i++)
		Args[i] = "0";
	
	while(1){
		int Option = getopt_long(argc, argv, Short_options, Long_options, &Option_index);
		if(Option == -1)
			break;
		
		switch(Option){
			case 'u':
				Args[0] = "1";
				break;
			case 'p':
				Args[1] = "1";
				break;
			case 'h':
				Args[2] = "1";
				break;
			case 'l':
				Args[3] = optarg;
				break;
			case 'e':
				Args[4] = optarg;
				break;
			case '?':
				break;
		}
	}

	printf("%s\n\n", Show_help());
	struct Data *u = Show_users();
	for(int i=0; i<u->len; i++){
		printf("%20s", u->data[i]);
		if(i%2!=0)
			printf("\n");
	}
	
}


