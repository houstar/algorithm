#include <stddef.h>
#include <stdlib.h>
#include <limits.h>

#include <tree/binary_tree.h>

#define STACK_SIZE (CHAR_BIT * sizeof(size_t))

typedef struct {
    node *node;
} stack_node;

void btree_add(node *new, btree *head)
{
    stack_node stack[STACK_SIZE];
    stack_node *top = stack;

    top->node = head->root, top++;
    while ( top != stack) {
        --top;
        node *temp = top->node;
        if (!temp) {
            head->root = new;
            break;
        }

        if (!temp->left) {
            temp->left = new;
            break;
        } else {
            top->node = temp->left, top++;
        }
        if (!temp->right) {
            temp->right= new;
            break;
        } else {
            top->node = temp->right, top++;
        }
    }
}

void btree_del(node *new, btree *head)
{

}
