#ifndef BINARY_TREE_H
#define BINARY_TREE_H

/**
 * Binary tree implementation
 */

/**
 * binary tree node declare
 */
typedef struct node {
    struct node *left;
    struct node *right;
}node;


typedef struct btree {
    struct node *root;
}btree;

/**
 * Initialize the binary tree head
 */
#define BTREE_INIT(name) { NULL }

/**
 * Initialize the binary tree structure
 */

#define BTREE(name) \
    btree name = BTREE_INIT(name)

/**
 * binary tree insert
 *
 * \param new the node to be added
 * \param head the binary tree root
 */
void btree_add(node *new, btree *head);


/**
 * binary tree delete
 *
 * \param new the node to be added
 * \param head the binary tree head
 */
void btree_del(node *new, btree *head);

#endif //BINARY_TREE_H
