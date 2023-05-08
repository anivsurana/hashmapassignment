#include "monster_tree.h"
#include "bt_utils.h"
#include <stdio.h>
#include <stdlib.h>
void bst_insert(BTNode **root, monster_s *monster, int key) {
    if (*root == NULL) {
        *root = calloc(1, sizeof(BTNode));
        (*root)->monster = monster;
        (*root)->key = key;

        return;
    }

    BTNode **temp = root;
    while (*temp != NULL) {
        if (key >= (*temp)->key) {
            temp = &(*temp)->right;
        } else {
            temp = &(*temp)->left;
        }
    }

    *temp = calloc(1, sizeof(BTNode));
    (*temp)->monster = monster;
    (*temp)->key = key;
}

BTNode *bst_search(BTNode *node, int key) {
    if (node == NULL || node->key == key) {
        return node;
    } else if (key > node->key) {
        return bst_search(node->right, key);
    } else {
        return bst_search(node->left, key);
    }
}

void bst_traverse(BTNode *node, traverse_type t) {
    if (node == NULL) {
        return;
    }

    if (t == PREORDER) {
        bst_traverse(node->left, t);
        printf("%d ", node->key);
        print_monster(node->monster);
        bst_traverse(node->right, t);
    }

    if (t == INORDER) {
        printf("%d ", node->key);
        bst_traverse(node->left, t);
        print_monster(node->monster);
        bst_traverse(node->right, t);
    }

    if (t == POSTORDER) {
        bst_traverse(node->left, t);
        bst_traverse(node->right, t);
        printf("%d ", node->key);
        print_monster(node->monster);
    }
}
