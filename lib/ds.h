#ifndef DATA_STRUCTURE
#define DATA_STRUCTURE

#include <inttypes.h>
#include <openssl/sha.h>

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

// create a tree node
node *create_tree(const char *name);
// create a blob node
node *create_blob(const char *name, int32_t size);
// link the nodes based on the types of both
void add_child(node *parent, node *child);
// add a blob as next of the actual blob
void next(node *current, node* next);
// print all nodes
void print_files(node *root, int8_t depth, int levels[10]);
// internal function for printing
void print_file_tree(node *root, int8_t depth, int levels[10]);
// free all nodes
void destroy(node *root);

#endif