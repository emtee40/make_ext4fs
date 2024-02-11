#include "selinux_internal.h"
#include <stdlib.h>
void freecon(char * con)
{
	free(con);
}

hidden_def(freecon)
