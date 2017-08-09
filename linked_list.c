#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>

void linked_list_add_last(list_node_t *root, list_node_t *newTree)
{
    list_node_t *last = linked_list_get_last(root);
    if(last != NULL) {
        last->next = newTree;
        newTree->prev = last;
    }
}
list_node_t *linked_list_get_last(list_node_t *root)
{
    list_node_t *last;
    if(root == NULL)
        return NULL;
    last = root;
    while(last->next != NULL) {
        last = last->next;
    }
    return last;
}
list_node_t *linked_list_get_first(list_node_t *root)
{
    if(root == NULL)
        return NULL;
    if(root->next == NULL)
        return NULL;
    return root->next;
}
void linked_list_remove_node(list_node_t *root, list_node_t *tree)
{
    list_node_t *found = root;
    while(linked_list_each(&found)) {
        if(found == tree && found != root) {
            if(found->next && found->prev) {
                found->prev->next = found->next;
                found->next->prev = found->prev;
            } else if(found->next) {
                found->next->prev = NULL;
            } else if(found->prev) {
                found->prev->next = NULL;
            }
            free(found);
            break;
        }
    }
}

void linked_list_clear(list_node_t *root)
{
    //FIXME: Need to test this function
    list_node_t *found;
    while((found = linked_list_get_first(root)) != NULL) {
        linked_list_remove_node(root, found);
    }
}

int linked_list_get_size(list_node_t *root)
{
    if(root == NULL)
        return 0;  //XXX: this should not happen
    int count = 0;
    while(root->next != NULL) {
        count++;
        root = root->next;
    }
    return count;
}

void linked_list_move_to_last(list_node_t *node)
{
    if(node == NULL || node->prev == NULL)
        return;
    list_node_t *last = node;
    while(last->next) {
        last = last->next;
    }

    if(last != node) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
        last->next = node;
        node->prev = last;
        node->next = NULL;
    }
}

int linked_list_each(list_node_t **root_ptr)
{
    if(root_ptr == NULL)
        return 0;
    list_node_t *root_node = *root_ptr;
    if(root_node && root_node->next) {
        *root_ptr = root_node->next;
        return 1;
    }
    return 0;
}
