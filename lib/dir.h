#ifndef DIR_OPERATIONS
#define DIR_OPERATIONS

#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "ds.h"

#define PATH_LEN 100

node* read_dir(DIR *dir, struct dirent *repo, node *root, char path[PATH_LEN]);

#endif