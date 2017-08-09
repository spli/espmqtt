#ifndef _LINKED_LIST_H_
#define _LINKED_LIST_H_

typedef struct list_node_t {
    struct list_node_t *next;
    struct list_node_t *prev;
} list_node_t;

/*
 * @brief: append a node to the end of the list
 *
 */
void linked_list_add_last(list_node_t *root, list_node_t *newTree);

/*
 * @brief: get the last node in the list
 * @note: might get the root
 *
 */
list_node_t *linked_list_get_last(list_node_t *root);

/*
 * @brief: get the first node in the list
 * @note: exclude root
 *
 */
list_node_t *linked_list_get_first(list_node_t *root);

/*
 * @brief: remove a node from the list
 * @note: exclude root (should not remove root)
 *
 */
void linked_list_remove_node(list_node_t *root, list_node_t *tree);

void linked_list_clear(list_node_t *root);

/*
 * @brief: get the number of nodes in the list (used for debug purposes)
 * @note: exclude root
 */
int linked_list_get_size(list_node_t *root);

/*
 * @brief: move a node in the list to the end of list
 * @note: do not move root
 */
void linked_list_move_to_last(list_node_t *node);

int linked_list_each(list_node_t **root);
#endif
