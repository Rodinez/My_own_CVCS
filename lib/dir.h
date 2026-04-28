#ifndef DIR_OPERATIONS
#define DIR_OPERATIONS

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "ds.h"

// read inicial dir to create all nodes
node* read_dir(DIR *dir, struct dirent *repo, node *root, char path[PATH_LEN]);

#endif