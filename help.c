#include <stdlib.h>

char *Show_help(){
	char* Text = 	"Usage:\n"
		 	"--users     [-u] --- print all users\n"
			"--processes [-p] --- print all processes\n"
			"--help      [-h] --- print help info\n"
			"--log       [-l] --- log output into file\n"
			"--errors    [-e] --- log errors into file\n";
	return Text;
}

