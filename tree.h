#pragma once

//Дерево
struct avltree
{
    int key;
    struct avltree* left;
    struct avltree* right;
    int height;
};

int AVLTree_height(struct avltree* tree);

int max(int a, int b);

void avltree_free(struct avltree* tree);

struct avltree* newNode(int key);

struct avltree* avltree_lookup(struct avltree* tree, int key);

struct avltree* AVLTree_RRotate(struct avltree* y);

struct avltree* AVLTree_LRotate(struct avltree* x);

int AVLTree_balance(struct avltree* Node);

struct avltree* avltree_insert(struct avltree* avltree, int key);

struct avltree* minKeyAVL(struct avltree* avltree);

struct avltree* maxKeyAVL(struct avltree* avltree);

struct avltree* deleteNode(struct avltree* root, int key);

void preOrder(struct avltree* root);