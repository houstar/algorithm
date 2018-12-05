#include <tree/binary_tree.h>
#include <utils/container_of.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

#include "unittest.h"

struct int_list {
    int val;
    node node;
};

BTREE(b);

struct int_list *root;
struct int_list *newNode(int key)
{
    struct int_list *n = (struct int_list *)malloc(sizeof(struct int_list));
    n->val = key;
    n->node.left = NULL;
    n->node.right = NULL;

    return n;
}

#define Q_SIZE (CHAR_BIT * sizeof(size_t))
/**
 * level reversal the binary tree
 *
 * This level reversal uses array as queue
 * */
void btree_level(node *head)
{
    if (!head) return;

    node *q[Q_SIZE];
    size_t front = 0, tail = 0, old_tail = 0;

    q[tail] = head;
    tail = (tail + 1) % Q_SIZE;
    while(front != tail) {
        old_tail = tail;
        for(int i = front ; i != old_tail; i = (i + 1) % Q_SIZE) {
            printf("%d  ", container_of(q[i], struct int_list, node)->val);
        }
        printf("\n");

        for( ; front != old_tail; front = (front + 1) % Q_SIZE) {
            node *temp = q[front];
            if(temp->left) {
                q[tail] = temp->left;
                tail = (tail + 1) % Q_SIZE;
            }
            if(temp->right) {
                q[tail] = temp->right;
                tail = (tail + 1) % Q_SIZE;
            }
        }
    }
}


static void setup(void)
{
    root = newNode(10);

    struct int_list *left = newNode(18);
    root->node.left = &left->node;

    struct int_list *right = newNode(19);
    root->node.right = &right->node;

    struct int_list *lleft= newNode(30);
    left->node.left = &lleft->node;

    struct int_list *lright = newNode(31);
    left->node.right= &lright->node;


    struct int_list *rright= newNode(36);
    right->node.right= &rright->node;
}

static void teardown(void)
{
}

START_TEST(btree_add_test)
{
    b.root = &root->node;

    struct int_list *n1 = newNode(34);
    btree_add(&n1->node, &b);

    btree_level(b.root);
}
END_TEST

Suite *make_binary_tree_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("binary_tree");
    /* Core test case */
    tc_core = tcase_create("Binary Tree");
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, btree_add_test);
    suite_add_tcase(s, tc_core);

    return s;
}
