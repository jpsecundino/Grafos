#pragma once

// Estrutura do nó
typedef union {
    double d;
    long long ll;
    void *pointer;
} node_val;

typedef struct _node node;

/*  Insere um novo elemento na lista
    Parâmetros:
        - node *head    : primeiro elemento da lista
        - node_val val  : elemento a ser adicionado
    Retorno:
        ponteiro para o novo primeiro elemento da lista
*/
node *list_insert(node *head, node_val val);

/*  Deleta um elemento na lista
    Parâmetros:
        - node *head    : primeiro elemento da lista
        - node_val val  : elemento a ser removido
    Retorno:
        ponteiro para o novo primeiro elemento da lista
*/
node *list_delete(node *head, node_val val);

/*  Retorna o próximo elemento da lista
    Parâmetros:
        - node *head    : primeiro elemento da lista
    Retorno:
        Caso não haja um próximo elemento na lista, retorna NULL;
        Caso haja, retorna o elemento seguinte a 'head'
*/
node *list_next(node *head);

/*  Retorna o valor do primeiro elemento da lista
    Parâmetros:
        - node *head    : primeiro elemento da lista
    Retorno:
        Caso não haja elementos da lista, retorna NULL;
        Caso haja, retorna o valor desejado
*/
node_val list_val(node *head);

/*  Destroi a lista
    Parâmetros:
        - node *head    : primeiro elemento da lista
*/
void list_destroy(node *head);

void deque_push_front(node **head, node **tail, node_val val);

void deque_push_back(node **head, node **tail, node_val val);

node_val deque_pop_front(node **head, node **tail);
