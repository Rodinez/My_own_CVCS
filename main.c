#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "lib/ds.h"
#include "lib/dir.h"
#include "lib/conf.h"

int main(){
    node *root = create_tree("repo");
    char path[PATH_LEN] = "repo";
    DIR *dir = opendir(path);
    struct dirent *repo;
    
    root = read_dir(dir, repo, root, path);
    calculate_tree_hash(root);
    
    commit *first_commit = create_commit(root->hash, author, message);

    int levels[10] = {0};
    print_files(root, 0, levels);
    destroy_nodes(root);
    return 0;
}