#include <stdlib.h>
#include "structs.h"

struct Data* Show_help(){
	struct Data *Text = malloc(sizeof(struct Data));
	Text->len = 6;
	Text->data = malloc(Text->len);

	Text->data[0] = 	"Usage:";
	Text->data[1] = 	"--users     [-u] --- print all users";
	Text->data[2] =		"--processes [-p] --- print all processes";
	Text->data[3] =		"--help      [-h] --- print help info";
	Text->data[4] =		"--log       [-l] --- log output into file";
	Text->data[5] =		"--errors    [-e] --- log errors into file";

	return Text;
}

