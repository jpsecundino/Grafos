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
        novo elemento adicionado à lista
*/
node *list_insert(node *head, node_val val);


/*  Deleta um elemento na lista
    Parâmetros:
        - node *head    : primeiro elemento da lista
        - node_val val  : elemento a ser removido
    Retorno:
        novo elemento removido da lista
*/
node *list_delete(node *head, node_val val);


/*  Retorna o próximo elemento da lista
    Parâmetros:
        - node *head    : primeiro elemento da lista
    Retorno:
        Caso não haja elementos da lista, retorna NULL;
        Caso haja, retorna o elemento seguinte ao primeiro
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
