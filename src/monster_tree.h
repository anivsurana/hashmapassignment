#ifndef MONSTER_TREE_H
#define MONSTER_TREE_H

#include "monster_utils.h"

typedef enum {
    PREORDER,
    INORDER,
    POSTORDER
} traverse_type;

typedef struct BTNode {
    int key;
    monster_s *monster;
    struct BTNode *left; 
    struct BTNode *right;
} BTNode;
BTNode *bst_search(BTNode *node, int key);
void bst_insert(BTNode **root, monster_s *monster, int key);
void bst_traverse(BTNode *node, traverse_type t);

#endif
