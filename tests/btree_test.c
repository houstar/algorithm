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


/**
 * This Q_SIZE declares the Queue Size
 *
 * TODO Use realloc to achieve dynamic Queue
 * */
#define Q_SIZE (CHAR_BIT * sizeof(size_t))
/**
 * level reversal the binary tree
 *
 * This level reversal uses array as queue
 * */
int **btree_level(node *head, int **column_size, int *return_size)
{
    if (!head) {
        *column_size = NULL;
        *return_size = 0;
        return NULL;
    }

    /* realloc to get the node address */
    int **nodes = (int **)malloc(sizeof(int*));
    *return_size = 0;
    *column_size = NULL;

    node *q[Q_SIZE];
    size_t front = 0, rear = 0;

    q[rear] = head;
    rear = (rear + 1) % Q_SIZE;
    while(front != rear) {
        /* realloc memory for column_size and node */
        *column_size = (int *)realloc(*column_size, sizeof(int) * (*return_size + 1));
        nodes = (int **)realloc(nodes, sizeof(int*) * (*return_size + 1));
        int level_width = (rear - front + Q_SIZE) % Q_SIZE;

        (*column_size)[*return_size] = level_width;
        nodes[*return_size] = (int *)calloc(level_width, sizeof(int));

        for(int i = 0; i < level_width; i++) {
            node *temp = q[front];
            front = (front + 1) % Q_SIZE;
            nodes[*return_size][i] = container_of(temp, struct int_list, node)->val;
            if(temp->left) {
                q[rear] = temp->left;
                rear = (rear + 1) % Q_SIZE;
            }
            if(temp->right) {
                q[rear] = temp->right;
                rear = (rear + 1) % Q_SIZE;
            }
        }

        (*return_size)++;
    }

    return nodes;
}


static void setup(void)
{
    /**
     *
     *                 10
     *           18         19
     *      30     31           36
     *
     *
     **/
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

    int **array = NULL;
    int *col = NULL;
    int size = 0;

    array = btree_level(b.root, &col, &size);

    printf("level: column_size %d level %d\n", *col, size);
    for(int i = 0; i < size; i++) {
        int w = 1 << (size - i + 1);
        for(int j = 0, len = col[i]; j < len; j++) {
            printf("%*d%*c ", w, array[i][j], w, ' ');
        }
        printf("\n");
    }
}
END_TEST

Suite *make_binary_tree_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("binary_tree");
    /* Core test case */
    tc_core = tcase_create("Core");
    tcase_add_checked_fixture(tc_core, setup, teardown);
    tcase_add_test(tc_core, btree_add_test);
    suite_add_tcase(s, tc_core);

    return s;
}
