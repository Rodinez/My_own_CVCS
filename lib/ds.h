#ifndef DATA_STRUCTURE
#define DATA_STRUCTURE

#include <inttypes.h>

typedef enum node_type{
    NODE_BLOB,
    NODE_TREE
} node_type;

typedef struct node {
    char name[30];
    node_type type;

    union {
        struct {
            __INT32_TYPE__ size;
            void *data;
        } blob;
        
        struct {
            struct node *first_children;
            struct node *last_children;
        } tree;
    };
    
    struct node *next;
    struct node *parent;
} node;

node *create_tree(const char *name);
node *create_blob(const char *name, void *data, int32_t size);
void add_child(node *parent, node *child);
void next(node *current, node* next);
void print_files(node *root, int8_t depth, int levels[10]);
void print_file_tree(node *root, int8_t depth, int levels[10]);
void destroy(node *root);

#endif