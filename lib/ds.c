#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "ds.h"

// create a tree node
node *create_tree(const char *name) {
    node *new_tree = (node*)malloc(sizeof(node));
    strcpy(new_tree->name, name);
    new_tree->type = NODE_TREE;
    new_tree->parent = NULL;
    new_tree->tree.first_children = NULL;
    new_tree->tree.last_children = NULL;
    return new_tree;
}

// create a blob node
node *create_blob(const char *name, int32_t size) {
    node *new_blob = (node*)malloc(sizeof(node));
    strcpy(new_blob->name, name);
    new_blob->type = NODE_BLOB;
    new_blob->blob.size = size;
    new_blob->parent = NULL;
    new_blob->next = NULL;
    return new_blob;
}

// link the nodes based on the types of both
''' 
Worth to make the insertion alphabetically ordered to avoid equal trees but with files in distinct orders to be seen
as different snapshots by the hash (dont know if it will happen but if it happens its cause of this insertion)
'''
void add_child(node *parent, node *child) { 
    // if the parent is a tree...
    if (parent->type == NODE_TREE) {
        if (!parent->tree.first_children) {
            parent->tree.first_children = child; // add its first child
        } else {
            parent->tree.last_children->next = child; // add the child as the last child
        }
        parent->tree.last_children = child;
        child->parent = parent;
    } else {
        next(parent, child);
    }
}

// add a blob as next of the actual blob
void next(node *current, node* next) {
    current->next = next;
    next->parent = current->parent;
}

// internal function for printing
void print_file_tree(node *root, int8_t depth, int levels[10]) {
    if (root == NULL)
        return;

    // print '|' if the level/layer isn't over
    for (int8_t i = 0; i < depth; i++){
        printf(!levels[i] ? "│" : " ");
        printf("  ");
    }

    if (root->type == NODE_BLOB) {
        printf(root->next == NULL ? "└─ %s\n" : "├─ %s\n", root->name);
        print_file_tree(root->next, depth, levels);
        if (root->parent->next == NULL) // this level/layer is over
            levels[depth] = 1;
    } else if (root->type == NODE_TREE) {
        printf(root->next == NULL ? "└─ %s/\n" : "├─ %s/\n", root->name);
        print_file_tree(root->tree.first_children, depth+1, levels); // root subdir
        if (root->parent->next == NULL) // this level/layer is over
            levels[depth] = 1;
        print_file_tree(root->next, depth, levels);
    }
}

// print all nodes
void print_files(node *root, int8_t depth, int levels[10]) {
    printf("%s/\n", root->name);
    print_file_tree(root->tree.first_children, depth, levels);
}

// free all nodes
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
