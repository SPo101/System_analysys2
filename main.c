#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include "structs.h"

#define CNT_ARGS 2
#define CNT_FUNC 3

struct Data* Show_help();
struct Data* Show_users();
struct Data* Show_processes();
int Log_into(char*, struct Data* (*Func[]) (), int);
int Error_into(char*, struct Data* (*Func[]) (), int);

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

	struct Data* (*Functions[CNT_FUNC]) () = {NULL, NULL, NULL};
	char *Args[CNT_ARGS];
	for(int i=0; i<CNT_ARGS; i++)
		Args[i] = "0";
	
	while(1){
		int Option = getopt_long(argc, argv, Short_options, Long_options, &Option_index);
		if(Option == -1)
			break;
		
		switch(Option){
			case 'h':
				Functions[0] = Show_help;
				break;
			case 'u':
				Functions[1] = Show_users;
				break;
			case 'p':
				Functions[2] = Show_processes;
				break;
			case 'l':
				Args[0] = optarg;
				break;
			case 'e':
				Args[1] = optarg;
				break;
			case '?':
				break;
		}
	}
	

	if( Args[0] != "0" )
		Log_into(Args[0], Functions, CNT_FUNC);
	if( Args[1] != "0" )
		Error_into(Args[1], Functions, CNT_FUNC);
	else{
		struct Data *func;
		for(int i=0; i<CNT_FUNC; i++)
			if(Functions[i] != NULL){
				func = Functions[i]();
				for(int j=0; j<func->len; j++)
					printf("%s\n", func->data[j]);
			}
	}
	
	exit(EXIT_SUCCESS);
}


