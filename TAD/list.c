#include <stdlib.h>
#include <string.h>

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

node *list_delete(node *head, node_val val) {
    if (head) {
        if (!memcmp(&head->val, &val, sizeof(node_val))) {
            node *next = head->next;
            free(head);
            return next;
        }
        head->next = list_delete(head->next, val);
    }
    return head;
}

node *list_next(node *head) {
    return head ? head->next : head;
}

node_val list_val(node *head) {
    return head ? head->val : (node_val) NULL;
}

void list_destroy(node *head) {
    while (head) {
        node *next = head->next;
        free(head);
        head = next;
    }
}