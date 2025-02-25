#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <sys/dir.h>
#include <dirent.h>
#include "structs.h"

#ifndef PATH_MAX
#define PATH_MAX 4096
#endif

struct Data* Show_processes(){
	struct dirent **listproc;//list of pid's
	ssize_t filecnt = scandir("/proc", &listproc, NULL, alphasort);
	if(filecnt < 0){
		exit(-1);
	}

	char procid[PATH_MAX];//process id
	char nameproc[PATH_MAX];//process name

	struct Data  *Processes= malloc(sizeof(struct Data));
	Processes->data = (char**) malloc(filecnt * sizeof(char*));
	Processes->len = filecnt;

	for(int i=0; i<filecnt; i++){
		sprintf(procid, "/proc/%s/status", listproc[i]->d_name);

		int fd = open(procid, O_RDONLY);
		if(fd==-1){
			Processes->data[i] = (char *) malloc(10);
			memset(Processes->data[i], 0, 10);
			continue;
		}
		
		read(fd, nameproc, PATH_MAX);
		int pplace = 1 + strcspn(nameproc, "\t");//beginning of proc name
		int place = strcspn(nameproc, "\n");// end of proc name

		Processes->data[i] = (char *) malloc(place-pplace+10);
		memset(Processes->data[i], 0, place-pplace+10);
		memcpy(Processes->data[i], nameproc+pplace, place-pplace);

		close(fd);
	}
	free(listproc);
	return Processes;
}
