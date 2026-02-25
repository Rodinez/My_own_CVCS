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
    node *dir1 = create_tree("src");
    node *dir2 = create_tree("lib");
    node *dir3 = create_tree("data");

    node *file1 = create_blob("file1", NULL, 12);
    node *file2 = create_blob("file2", NULL, 22);
    node *file3 = create_blob("file3", NULL, 32);
    node *file4 = create_blob("file4", NULL, 12);
    node *file5 = create_blob("file5", NULL, 22);
    node *file6 = create_blob("file6", NULL, 32);
    node *file7 = create_blob("file7", NULL, 12);
    node *file8 = create_blob("file8", NULL, 22);
    node *file9 = create_blob("file9", NULL, 32);
    
    // level 0
    add_child(root, file1);
    add_child(root, dir1);
    add_child(root, file7);
    add_child(root, dir2);
    
    // level 1
    add_child(dir1, file2);
    add_child(dir1, file3);
    add_child(dir1, dir3);
    add_child(dir1, file6);
    
    add_child(dir2, file8);
    add_child(dir2, file9);
    
    //level 2
    add_child(dir3, file4);
    add_child(dir3, file5);
    
    int levels[10] = {0};
    print_files(root, 0, levels);
    return 0;
}