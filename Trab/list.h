#pragma once

// Estrutura do no
typedef union {
    double d;
    long long ll;
    void *pointer;
} node_val;

typedef struct _node node;

/**
 * @brief  Insere um novo elemetno na lista
 * @param  *head: primeiro elemento da lista   
 * @param  val: elemento a ser adicionado
 * @retval ponteiro para o novo primeiro elemento da lista
 */
node *list_insert(node *head, node_val val);

/**
 * @brief  Deleta um elemento da lista
 * @param  *head: primeiro elemento da lista
 * @param  val: elemento a ser removido
 * @retval ponteiro para o novo primeiro elemento da lista
 */
node *list_delete(node *head, node_val val);

/**
 * @brief  Retorna o proximo elemento da lista
 * @param  *head: elemento atual da lista
 * @retval:
 *      Caso nao haja um proximo elemento na lista, retorna NULL;
        Caso haja, retorna o elemento seguinte a 'head'
 */
node *list_next(node *head);

/**
  * @brief   Retorna o valor do elemento da lista enviado como argumento
  * @note o valor pode ser um ponteiro, double ou lon long int
  * @param  *head:  valor do no
  * @retval retorna o valor do primeiro elemento
*/
node_val list_val(node *head);

/**
 * @brief  destroi a lista
 * @param  *head: primeiro elemento da lista
 * @retval none
 */
void list_destroy(node *head);

/**
 * @brief  adiciona um elemento no inicio da lista
 * @param  **head: ponteiro para o container do no inicial da lista
 * @param  **tail: ponteiro para o container do no final da lista
 * @param  val: valor do no a ser adicionado
 * @retval none
 */
void deque_push_front(node **head, node **tail, node_val val);

/**
 * @brief  adiciona um elemento no fim da lista
 * @param  **head: ponteiro para o container do no inicial da lista
 * @param  **tail: ponteiro para o container do no final da lista
 * @param  val: valor do no a ser adicionado
 * @retval none
 */
void deque_push_back(node **head, node **tail, node_val val);

/**
 * @brief  elimina elemento da frente da lista
 * @param  **head: ponteiro para o container do no inicial da lista
 * @param  **tail: ponteiro para o container do no final da lista
 * @retval 
 */
node_val deque_pop_front(node **head, node **tail);
