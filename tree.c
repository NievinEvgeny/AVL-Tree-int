#include "tree.h"
#include <stdio.h>
#include <stdlib.h>

//Нахождение высоты
int AVLTree_height(struct avltree* tree)
{
    if (tree == NULL)
    {
        return -1;
    }
    return tree->height;
}

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

//Печать дерева
void AVLtree_print(struct avltree* root)
{
    if (root != NULL)
    {
        printf("%d ", root->key);
        AVLtree_print(root->left);
        AVLtree_print(root->right);
    }
}

//Освобождение памяти
void avltree_free(struct avltree* tree)
{
    if (tree == NULL)
    {
        return;
    }
    avltree_free(tree->left);
    avltree_free(tree->right);
    free(tree);
}

//Вспомогательная функция, выделяющая новый узел с Null потомками
struct avltree* newNode(int key)
{
    struct avltree* avltree = (struct avltree*)malloc(sizeof(struct avltree));
    avltree->key = key;
    avltree->left = NULL;
    avltree->right = NULL;
    avltree->height = 0;
    return (avltree);
}

struct avltree* avltree_lookup(struct avltree* tree, int key)
{
    while (tree != NULL)
    {
        if (key == tree->key)
        {
            return tree;
        }
        else if (key < tree->key)
        {
            tree = tree->left;
        }
        else
        {
            tree = tree->right;
        }
    }
    return tree;
}

//Правый поворот в корне с "y"
struct avltree* AVLTree_RRotate(struct avltree* y)
{
    struct avltree* x = y->left;
    struct avltree* T2 = x->right;

    x->right = y;
    y->left = T2;

    y->height = max(AVLTree_height(y->left), AVLTree_height(y->right)) + 1;
    x->height = max(AVLTree_height(x->left), AVLTree_height(x->right)) + 1;

    return x;
}

//Левый поворот в корне с "y"
struct avltree* AVLTree_LRotate(struct avltree* x)
{
    struct avltree* y = x->right;
    struct avltree* T2 = y->left;

    y->left = x;
    x->right = T2;

    x->height = max(AVLTree_height(x->left), AVLTree_height(x->right)) + 1;
    y->height = max(AVLTree_height(y->left), AVLTree_height(y->right)) + 1;

    return y;
}

// Min ключ
struct avltree* minKeyAVL(struct avltree* avltree)
{
    struct avltree* current = avltree;
    while (current->left != NULL)
    {
        current = current->left;
    }
    return current;
}

// Max ключ
struct avltree* maxKeyAVL(struct avltree* avltree)
{
    struct avltree* current = avltree;
    while (current->right != NULL)
    {
        current = current->right;
    }
    return current;
}

//Коэффициент сбалансированности узла Node
int AVLTree_balance(struct avltree* Node)
{
    if (Node == NULL)
    {
        return 0;
    }
    return AVLTree_height(Node->left) - AVLTree_height(Node->right);
}

struct avltree* avltree_insert(struct avltree* avltree, int key)
{
    if (avltree == NULL)
    {
        return (newNode(key));
    }
    if (key < avltree->key)
    {
        avltree->left = avltree_insert(avltree->left, key);
    }
    else if (key > avltree->key)
    {
        avltree->right = avltree_insert(avltree->right, key);
    }
    else //Одинаковые ключи
    {
        return avltree;
    }
    //Обновляем высоту предка
    avltree->height = 1 + max(AVLTree_height(avltree->left), AVLTree_height(avltree->right));

    //Получаем его баланс, чтобы узнать, стал ли он несбалансированным
    int balance = AVLTree_balance(avltree);

    //Если да, то есть 4 случая

    // Left Left Case
    if (balance > 1 && key < avltree->left->key)
    {
        return AVLTree_RRotate(avltree);
    }

    // Right Right Case
    if (balance < -1 && key > avltree->right->key)
    {
        return AVLTree_LRotate(avltree);
    }

    // Left Right Case
    if (balance > 1 && key > avltree->left->key)
    {
        avltree->left = AVLTree_LRotate(avltree->left);
        return AVLTree_RRotate(avltree);
    }

    // Right Left Case
    if (balance < -1 && key < avltree->right->key)
    {
        avltree->right = AVLTree_RRotate(avltree->right);
        return AVLTree_LRotate(avltree);
    }
    return avltree;
}

//Удаление узла по ключу, вернёт корень изменённого поддерева
struct avltree* deleteNode(struct avltree* root, int key)
{
    //Обычное удаление
    if (root == NULL)
    {
        return root;
    }

    //Идём по дереву, ищем ключ
    if (key < root->key)
    {
        root->left = deleteNode(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = deleteNode(root->right, key);
    }

    //Если корень (текущего поддерева) и есть искомый узел
    else
    {
        //Один или ноль потомков
        if ((root->left == NULL) || (root->right == NULL))
        {
            struct avltree* temp = root->left ? root->left : root->right;

            //Нет потомков
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            //Один потомок
            else
            {
                *root = *temp;
            }
            free(temp);
        }
        else
        {
            //Берём узел с наименьшим ключом в правом поддереве
            struct avltree* temp = minKeyAVL(root->right);

            //Вставляем его в корень
            root->key = temp->key;

            //Удаляем его в правом поддереве
            root->right = deleteNode(root->right, temp->key);
        }
    }
    // Если в дереве был только один узел
    if (root == NULL)
    {
        return root;
    }

    //Обновляем высоту текущего узла
    root->height = 1 + max(AVLTree_height(root->left), AVLTree_height(root->right));

    //Получаем его баланс, чтобы узнать, стал ли он несбалансированным
    int balance = AVLTree_balance(root);

    //Если да, то есть 4 случая

    // Left Left Case
    if (balance > 1 && AVLTree_balance(root->left) >= 0)
    {
        return AVLTree_RRotate(root);
    }

    // Left Right Case
    if (balance > 1 && AVLTree_balance(root->left) < 0)
    {
        root->left = AVLTree_LRotate(root->left);
        return AVLTree_RRotate(root);
    }

    // Right Right Case
    if (balance < -1 && AVLTree_balance(root->right) <= 0)
    {
        return AVLTree_LRotate(root);
    }

    // Right Left Case
    if (balance < -1 && AVLTree_balance(root->right) > 0)
    {
        root->right = AVLTree_RRotate(root->right);
        return AVLTree_LRotate(root);
    }

    return root;
}
