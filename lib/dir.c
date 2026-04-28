#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <openssl/sha.h>
#include "ds.h"
#include "dir.h"

// read inicial dir to create all nodes
node* read_dir(DIR *dir, struct dirent *repo, node *root, char path[PATH_LEN]) {
    while ((repo = readdir(dir)) != NULL) {
        if (strcmp(repo->d_name, ".") == 0 || strcmp(repo->d_name, "..") == 0) // ignore . and .. dirs
            continue;
        if (repo->d_type == DT_DIR) { // if dir...
            node *new_tree = create_tree(repo->d_name);
            add_child(root, new_tree);
            char new_path[PATH_LEN];
            new_path[0] = '\0';
            strcat(new_path, path);
            strcat(new_path, "/");
            strcat(new_path, repo->d_name); // path to the subdir
            DIR *subdir = opendir(new_path);
            struct dirent *new_dir;
            read_dir(subdir, new_dir, new_tree, new_path);
            calculate_tree_hash(new_tree);
            // -> print hash
            //for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
            //    printf("%02x", new_tree->hash[i]);
            //printf("\n");
        } else { // if file...
            char new_path[PATH_LEN];
            new_path[0] = '\0';
            strcat(new_path, path);
            strcat(new_path, "/");
            strcat(new_path, repo->d_name); // path for the file 
            struct stat info;
            stat(new_path, &info);
            node *new_blob = create_blob(repo->d_name, info.st_size);
            add_child(root, new_blob);
            calculate_blob_hash(new_blob, new_path);
            // -> print hash
            //for (int i = 0; i < SHA256_DIGEST_LENGTH; i++)
            //    printf("%02x", new_blob->hash[i]);
            //printf("\n");
        }
    }
    return root;
}