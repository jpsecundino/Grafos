#pragma once

typedef union {
    double d;
    long long ll;
    void *pointer;
} node_val;

typedef struct _node node;

node *list_insert(node *head, node_val val);
node *list_delete(node *head, node_val val);
node *list_next(node *head);
node_val list_val(node *head);
void list_destroy(node *head);
