//
// Created by marco on 5/6/25.
//

#ifndef BTREE_H
#define BTREE_H

typedef struct node* AVLIntervalTree;

AVLIntervalTree avl_insert(AVLIntervalTree root, int key);
AVLIntervalTree avl_delete(AVLIntervalTree root, int key);
void avl_preorder(AVLIntervalTree root);
void avl_inorder(AVLIntervalTree root);
void avl_free(AVLIntervalTree root);
#endif //BTREE_H
