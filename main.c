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
    struct stat stats;
    char *objects_dir = ".objects";

   if (stat(objects_dir, &stats) != 0) {
        if (mkdir(objects_dir, 0755) != 0){
            fprintf(stderr, "Failed to create .objects\n");
            perror("mkdir");
            exit(EXIT_FAILURE);
        }
    } else if (!S_ISDIR(stats.st_mode)) {
        fprintf(stderr, "Path to .objects already taken\n");
        exit(EXIT_FAILURE);
    } 

    node *root = create_tree("repo");
    char path[PATH_LEN] = "repo";
    DIR *dir = opendir(path);
    struct dirent *repo;
    
    root = read_dir(dir, repo, root, path);
    calculate_tree_hash(root);
    
    commit *first_commit = create_commit(NULL, root->hash, author, message);

    print_files(root);
    destroy_nodes(root);
    return 0;
}