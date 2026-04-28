#include <assert.h>
#include <stdio.h>
#include "lib/ds.h"
#include "lib/conf.h"

void test_create_tree() {
    node *tree = create_tree("root");

    assert(tree != NULL);
    assert(tree->type == NODE_TREE);
    assert(strcmp(tree->name, "root") == 0);

    printf("test_create_tree passed\n");
}

void test_create_blob() {
    node *blob = create_blob("file.txt", 100);

    assert(blob != NULL);
    assert(blob->type == NODE_BLOB);
    assert(strcmp(blob->name, "file.txt") == 0);
    assert(blob->blob.size == 100);

    printf("test_create_blob passed\n");
}

void test_add_child() {
    node *root = create_tree("root");
    node *blob = create_blob("file.txt", 100);

    add_child(root, blob);

    assert(root->tree.first_children == blob);
    assert(root->tree.last_children == blob);
    assert(blob->parent == root);

    printf("test_add_child passed\n");
}

void test_add_two_children() {
    node *root = create_tree("root");
    node *blob = create_blob("file.txt", 100);
    node *blob2 = create_blob("file2.txt", 150);

    add_child(root, blob);
    add_child(root, blob2);

    assert(root->tree.first_children == blob);
    assert(root->tree.last_children == blob2);
    assert(blob->parent == root);
    assert(blob2->parent == root);
    assert(blob->next == blob2);

    printf("test_add_two_children passed\n");
}
void test_add_children_and_subdir() {
    node *root = create_tree("root");
    node *lib = create_tree("lib");
    node *blob = create_blob("file.txt", 100);
    node *blob2 = create_blob("file2.txt", 150);
    node *blob3 = create_blob("file3.txt", 150);

    add_child(root, blob);
    add_child(root, blob2);
    add_child(root, lib);
    add_child(lib, blob3);

    assert(root->tree.first_children == blob);
    assert(root->tree.last_children == lib);
    assert(blob->parent == root);
    assert(blob2->parent == root);
    assert(blob->next == blob2);
    assert(blob2->next == lib);
    assert(lib->tree.first_children = blob3);
    assert(lib->tree.last_children = blob3);
    assert(blob3->parent == lib);

    printf("test_add_children_and_subdir passed\n");
}

void test_commit() {
    node *root = create_tree("root");
    node *blob = create_blob("file.txt", 100);
    add_child(root, blob);
    char path[PATH_LEN] = "repo/file1.txt";
    calculate_blob_hash(blob, path);
    calculate_tree_hash(root);
    commit *com = create_commit(root->hash, author, message);
    
    assert(memcmp(root->hash, com->tree_hash, SHA256_DIGEST_LENGTH) == 0);
    assert(strcmp(com->author, author) == 0);
    assert(strcmp(com->message, message) == 0);

    printf("test_commit passed\n");
}

int main() {
    test_create_tree();
    test_create_blob();
    test_add_child();
    test_add_two_children();
    test_add_children_and_subdir();
    test_commit();

    printf("All tests passed\n");
    return 0;
}