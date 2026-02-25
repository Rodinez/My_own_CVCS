#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ds.h"

node *create_tree(const char *name) {
    node *new_tree = (node*)malloc(sizeof(node));
    strcpy(new_tree->name, name);
    new_tree->type = NODE_TREE;
    new_tree->tree.first_children = NULL;
    new_tree->tree.last_children = NULL;
    new_tree->last = NULL;
    return new_tree;
}

node *create_blob(const char *name, void *data, int32_t size) {
    node *new_blob = (node*)malloc(sizeof(node));
    strcpy(new_blob->name, name);
    new_blob->type = NODE_BLOB;
    new_blob->blob.data = data;
    new_blob->blob.size = size;
    new_blob->next = NULL;
    new_blob->last = NULL;
    return new_blob;
}


// mesclar add_child e next em um só
void add_child(node *parent, node *child) {
    parent->tree.first_children = child;
    parent->tree.last_children = child;
    child->blob.parent = parent;
}

void next(node *current, node* next) {
    current->next = next;
    next->last = current;
}

void print_file_tree(node *root, int8_t depth, int levels[10]) {
    if (root == NULL)
        return;

    for (int8_t i = 0; i < depth; i++){
        printf(!levels[i] ? "|" : " ");
        printf("  ");
    }

    if (root->type == NODE_BLOB) {
        printf(root->next == NULL ? "└ %s\n" : "├ %s\n", root->name);
        if (root->next == NULL) 
            levels[depth] = 1;
        print_file_tree(root->next, depth, levels);
    } else if (root->type == NODE_TREE) {
        if (depth != -1 ) {
            printf(root->next == NULL ? "└ %s/\n" : "├ %s/\n", root->name);
            if (root->next == NULL)
                levels[depth] = 1;
        } else {
            printf("%s/\n", root->name);
        }
        print_file_tree(root->tree.first_children, depth+1, levels);
        print_file_tree(root->next, depth, levels);
    }
}

void destroy(node* root) {
    if (root->type == NODE_BLOB) {
        if (root->next != NULL)
            destroy(root->next);
        free(root);
    } else if (root->type == NODE_TREE) {
        if (root->tree.first_children != NULL)
            destroy(root->tree.first_children);
        if (root->next != NULL)
            destroy(root->next);
        free(root);
    }
}
