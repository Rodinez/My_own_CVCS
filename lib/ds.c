#include "ds.h"

// FUNCTIONS FOR BLOBS AND TRESS 

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

// Worth to make the insertion alphabetically ordered to avoid equal trees but with files in distinct orders to be seen
// as different snapshots by the hash (dont know if it will happen but if it happens its cause of this insertion)

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
void print_file_tree(node *root, short int depth, int levels[10]) {
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
void print_files(node *root) {
    printf("%s/\n", root->name);
    short int depth = 0;
    int levels[10] = {0};
    print_file_tree(root->tree.first_children, depth, levels);
}

// calculate the SHA-256 for the blob
void calculate_blob_hash(node* new_blob, char new_path[PATH_LEN]) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    FILE *file = fopen(new_path, "rb");

    if (file == NULL) {
        printf("Cannot open file %s\n", new_path);
        exit(1);
    }

    unsigned char buffer[4096];
    size_t bytes;
    while ((bytes = fread(buffer, 1, sizeof(buffer), file)) > 0) {
        SHA256_Update(&ctx, buffer, bytes);
    }

    SHA256_Final(new_blob->hash, &ctx);
    fclose(file);
};

// calculate the SHA-256 for the tree
void calculate_tree_hash(node* new_tree) {
    SHA256_CTX ctx;
    SHA256_Init(&ctx);
    node *child = new_tree->tree.first_children;

    while (child != NULL) {
        SHA256_Update(&ctx, &child->type, sizeof(child->type));
        SHA256_Update(&ctx, child->name, strlen(child->name));
        SHA256_Update(&ctx, child->hash, SHA256_DIGEST_LENGTH);

        child = child->next;
    }

    SHA256_Final(new_tree->hash, &ctx);
}

// free all nodes
void destroy_nodes(node* root) {
    if (root->type == NODE_BLOB) {
        if (root->next != NULL)
            destroy_nodes(root->next);
        free(root);
    } else if (root->type == NODE_TREE) {
        if (root->tree.first_children != NULL)
            destroy_nodes(root->tree.first_children);
        if (root->next != NULL)
            destroy_nodes(root->next);
        free(root);
    }
}

// FUNCTIONS FOR COMMITS

// creat a commit
commit *create_commit(unsigned char tree_hash[SHA256_DIGEST_LENGTH], char author[100], char message[510]){
    commit *new_commit = (commit*)malloc(sizeof(commit));
    memcpy(new_commit->tree_hash, tree_hash, SHA256_DIGEST_LENGTH);
    // Identify the last commit here
    strcpy(new_commit->author, author);
    strcpy(new_commit->message, message);
    time(&new_commit->timestamp);
    return new_commit;
}

void calculate_commit_hash(commit *com){
    SHA256_CTX ctx;
    SHA256_Init(&ctx);

    SHA256_Update(&ctx, com->tree_hash, SHA256_DIGEST_LENGTH);
    // SHA256_Update(&ctx, com->parent_commit, SHA256_DIGEST_LENGTH);
    SHA256_Update(&ctx, com->author, strlen(com->author));
    SHA256_Update(&ctx, com->message, strlen(com->message));
    SHA256_Update(&ctx, &com->timestamp, sizeof(com->timestamp));

    SHA256_Final(com->commit_hash, &ctx);
}


// free a commit
void destroy_commit(commit *com){
    free(com);
}