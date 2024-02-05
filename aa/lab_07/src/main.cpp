
#include "interface.h"
#include "tree.h"

int main()
{
    int rc = 0;

    tree_t bst_tree, awl_tree;
    bst_tree.root = NULL, awl_tree.root = NULL;

    int count_data;

    while (true)
    {
        print_menu();

        int menu_item;

        if ((rc = read_menu_item(menu_item)) != 0)
            goto free;

        switch (menu_item)
        {
        case 0:
            free_tree(&bst_tree);
            free_tree(&awl_tree);
            exit(0);
            break;
        case 1:
            if ((rc = rea d_data(count_data, &bst_tree, &awl_tree)) != 0)
                goto free;
            break;
        case 4:
            if ((rc = trees_to_dot(&bst_tree, &awl_tree)) != 0)
                goto free;
            break;
        default:
            break;
        }
    }

free:

    return rc;
}
