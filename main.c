#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "lib/ds.h"
#include "lib/dir.h"

int main(){
    node *root = create_tree("repo");
    char path[PATH_LEN] = "repo";
    DIR *dir = opendir(path);
    struct dirent *repo;
    
    root = read_dir(dir, repo, root, path);

    int levels[10] = {0};
    print_file_tree(root, -1, levels);
    return 0;
}