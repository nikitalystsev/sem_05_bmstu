#ifndef __INTERFACE_H__
#define __INTERFACE_H__

#include "defines.h"
#include "tree.h"

void print_menu(void);

int read_menu_item(int &item);

int read_data(int &count_data, tree_t *bst_tree, tree_t *awl_tree);

int trees_to_dot(tree_t *bst_tree, tree_t *awl_tree);

#endif