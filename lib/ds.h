#ifndef DATA_STRUCTURE
#define DATA_STRUCTURE

#include <inttypes.h>
#include <openssl/sha.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define PATH_LEN 1020 // max len for the dir/subdir/subsubdir.../ and maybe a file

// enum for the type od the node (file or directory)
typedef enum node_type{
    NODE_BLOB, // file
    NODE_TREE // directory
} node_type;

// principal struct to mantain blobs and trees
typedef struct node {
    char name[255];
    node_type type;
    unsigned char hash[SHA256_DIGEST_LENGTH];

    // use blob OR directory
    union {
        struct {
            __INT32_TYPE__ size;
        } blob;
        
        struct {
            struct node *first_children;
            struct node *last_children;
        } tree;
    };
    
    struct node *next;
    struct node *parent;
} node;

// struct for commits
typedef struct commit{
    unsigned char commit_hash[SHA256_DIGEST_LENGTH]; 
    unsigned char tree_hash[SHA256_DIGEST_LENGTH]; 
    unsigned char parent_commit[SHA256_DIGEST_LENGTH];
    char author[100];
    time_t timestamp;
    char message[510];
} commit;

// FUNCTIONS FOR BLOBS AND TREES

// create a tree node
node *create_tree(const char *name);

// create a blob node
node *create_blob(const char *name, int32_t size);

// link the nodes based on the types of both
void add_child(node *parent, node *child);

// add a blob as next of the actual blob
void next(node *current, node* next);

// print all nodes
void print_files(node *root);

// internal function for printing
void print_file_tree(node *root, short int depth, int levels[10]);

// calculate the SHA-256 for the blob
void calculate_blob_hash(node *new_blob, char new_path[PATH_LEN]);

// calculate the SHA-256 for the tree
void calculate_tree_hash(node *new_tree);

// free all nodes
void destroy_nodes(node *root);

// FUNCTIONS FOR COMMITS

// creat a commit
commit *create_commit(unsigned char tree_hash[SHA256_DIGEST_LENGTH], char author[100], char message[510]);

// calculate the SHA-256 for the commit
void calculate_commit_hash(commit *com);

// free a commit
void destroy_commit(commit *com);

#endif