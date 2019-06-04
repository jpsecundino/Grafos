#include "list.h"
#include <stdlib.h>
#include <string.h>

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
    return head ? head->val : (node_val){.pointer = NULL};
}

void list_destroy(node *head) {
    while (head) {
        node *next = head->next;
        free(head);
        head = next;
    }
}

void deque_push_front(node **head, node **tail, node_val val) {
    *head = list_insert(*head, val);
    if (*tail == NULL) {
        *tail = *head;
    }
}

void deque_push_back(node **head, node **tail, node_val val) {
    if (*head == NULL) {
        deque_push_front(head, tail, val);
    } else {
        *tail = (*tail)->next = list_insert(NULL, val);
    }
}

node_val deque_pop_front(node **head, node **tail) {
    node_val val = list_val(*head);
    node *aux = *head;
    if (*head == *tail) {
        *head = *tail = NULL;
    } else {
        *head = (*head)->next;
    }
    if (aux) {
        free(aux);
    }
    return val;
}
