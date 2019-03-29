#include <stdlib.h>

#include "list.h"

struct _node {
    node_val val;
    node *next;
};

node *list_insert(node *head, node_val val) {
    node *n = malloc(sizeof(node));
    n->next = head;
    n->val = val;
    return n;
}

node *list_next(node *head) {
    return head ? head->next : head;
}

node_val list_val(node *head) {
    return head ? head->val : (node_val) NULL;
}