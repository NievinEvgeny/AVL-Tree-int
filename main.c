#include "tree.h"
#include <stdio.h>

int main()
{
    struct avltree* root = NULL;
    for (int i = 1; i < 131080; i++)
    {
        root = avltree_insert(root, i);
    }
    AVLtree_print(root);
    printf("\n");
    deleteNode(root, 2);
    AVLtree_print(root);
    printf("\n");
    struct avltree* temp1 = avltree_lookup(root, 65536);
    printf("%d\n", AVLTree_height(temp1));
    struct avltree* temp2 = avltree_lookup(root, 131079);
    printf("%d\n", AVLTree_height(temp2));
    return 0;
}