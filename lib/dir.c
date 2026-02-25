#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include "ds.h"
#include "dir.h"

node* read_dir(DIR *dir, struct dirent *repo, node *root, char path[PATH_LEN]) {
    while ((repo = readdir(dir)) != NULL) {
        if (strcmp(repo->d_name, ".") == 0 || strcmp(repo->d_name, "..") == 0)
        continue;
        if (repo->d_type == DT_DIR) {
            node *new_tree = create_tree(repo->d_name);
            if (root->tree.children == NULL) {
                add_child(root, new_tree);
            } else {
                
            }
            char new_path[PATH_LEN];
            strcat(new_path, path);
            strcat(new_path, "/");
            strcat(new_path, repo->d_name);
            DIR *subdir = opendir(new_path);
            struct dirent *new_dir;
            printf("%s\n", path);
            printf("%s\n", new_path);
            read_dir(subdir, new_dir, new_tree, new_path);

        } else {
            // mudar os dados e o tamanho depois
            node *new_blob = create_blob(repo->d_name, NULL, 0);
            if (root->tree.children == NULL) {
                add_child(root, new_blob);
            } else {
                
            }
        }
    }
    return root;
}