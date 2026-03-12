#ifndef DIR_OPERATIONS
#define DIR_OPERATIONS

#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include "ds.h"

#define PATH_LEN 1020

node* read_dir(DIR *dir, struct dirent *repo, node *root, char path[PATH_LEN]);
void calculate_blob_hash(node *new_blob, char new_path[PATH_LEN]);
void calculate_tree_hash(node *new_tree);

#endif