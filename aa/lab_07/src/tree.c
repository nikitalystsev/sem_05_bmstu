#include "tree.h"

vertex_t *create_vertex(int data, int height)
{
    vertex_t *vertex = malloc(sizeof(vertex_t));

    if (vertex)
    {
        vertex->data = data;
        vertex->height = height;
        vertex->left = NULL;
        vertex->right = NULL;
    }

    return vertex;
}

vertex_t *add_vertex(vertex_t *root, vertex_t *vertex, bool is_balance)
{
    if (!root)
    {
        return vertex;
    }

    if (vertex->data < root->data)
    {
        root->left = add_vertex(root->left, vertex, is_balance);
    }
    else if (vertex->data > root->data)
    {
        root->right = add_vertex(root->right, vertex, is_balance);
    }

    return is_balance ? balance(root) : root;
}

vertex_t *search(vertex_t *root, int data, int *count_compare)
{
    (*count_compare)++;

    if (!root)
    {
        return NULL;
    }

    if (data < root->data)
    {
        return search(root->left, data, count_compare);
    }
    if (data > root->data)
    {
        return search(root->right, data, count_compare);
    }

    return root;
}

/*
Функция для нахождения родителя элемента.
Случай, когда элементом является корень, не обрабатывается
*/
vertex_t *find_parent(vertex_t *root, vertex_t *vertex)
{
    if (!root)
    {
        return NULL;
    }

    if (vertex->data < root->data)
    {
        if (root->left->data == vertex->data)
        {
            return root;
        }

        return find_parent(root->left, vertex);
    }
    if (vertex->data > root->data)
    {
        if (root->right->data == vertex->data)
        {
            return root;
        }

        return find_parent(root->right, vertex);
    }

    return root;
}

static vertex_t *find_min_right(vertex_t *vertex)
{
    vertex_t *tmp_vertex = vertex;

    while (tmp_vertex->left)
    {
        tmp_vertex = tmp_vertex->left;
    }

    return tmp_vertex;
}

// static vertex_t *find_max_left(vertex_t *vertex)
// {
//     vertex_t *tmp_vertex = vertex;

//     while (tmp_vertex->right)
//     {
//         tmp_vertex = tmp_vertex->right;
//     }

//     return tmp_vertex;
// }

int delete_vertex(vertex_t **root, int data, bool is_balance)
{
    vertex_t *parent = NULL;

    int count_compare = 0;
    vertex_t *find = search(*root, data, &count_compare);
    if (!find)
    {
        return NOT_FOUND;
    }

    // если удаляемый не корень, то находим родителя
    if (find != *root)
    {
        parent = find_parent(*root, find);
    }

    // у удаляемого элемента есть оба потомка
    if (find->left && find->right)
    {
        // находим самый левый (минимальный) элемент в правом поддереве
        vertex_t *min_right = find_min_right(find->right);

        // или находим самый правый (максимальный) элемент в левом поддереве
        // vertex_t *min_right = find_max_left(find->left);

        int data = min_right->data;

        // удаляем всех преемников найденного (min_right) элемента
        // и его самого тоже
        delete_vertex(root, min_right->data, is_balance);

        find->data = data;
    }
    // у удаляемого элемента 0 или 1 потомок
    else
    {
        // переводится heir как преемник
        vertex_t *heir = (find->left) ? find->left : find->right;

        if (!parent)
        {
            if (!heir)
                free(*root);
            *root = heir;
        }
        else
        {
            if (parent->left == find)
            {
                free(find);
                parent->left = heir, find = NULL;
            }
            else if (parent->right == find)
            {
                free(find);
                parent->right = heir, find = NULL;
            }
        }
    }

    if (is_balance)
    {
        *root = balance(*root);
    }

    return EXIT_SUCCESS;
}

bool is_empty_tree(tree_t *tree)
{
    if (!tree->root)
    {
        return true;
    }

    return false;
}

void free_vertex(vertex_t *root)
{
    if (root)
    {
        free_vertex(root->right);
        free_vertex(root->left);
    }

    free(root);
}

void free_tree(tree_t *tree)
{
    free_vertex(tree->root);
    tree->root = NULL;
}

int get_tree_depth(vertex_t *root)
{
    if (!root)
    {
        return 0;
    }

    int ldepth = get_tree_depth(root->left);
    int rdepth = get_tree_depth(root->right);

    if (ldepth > rdepth)
    {
        return ldepth + 1;
    }

    return rdepth + 1;
}

int get_count_vertex_in_level(vertex_t *root, int n, int c)
{
    if (n == c)
    {
        return 1;
    }

    int count = 0;

    if (root->left)
    {
        count += get_count_vertex_in_level(root->left, n, c + 1);
    }
    if (root->right)
    {
        count += get_count_vertex_in_level(root->right, n, c + 1);
    }

    return count;
}

static int height(vertex_t *vertex)
{
    return vertex ? vertex->height : 0;
}

// получает разницу высот правого и левого поддеревьев
static int balance_factor(vertex_t *vertex)
{
    return height(vertex->right) - height(vertex->left);
}

static void new_height(vertex_t *vertex)
{
    int height_l = height(vertex->left);
    int height_r = height(vertex->right);

    vertex->height = ((height_l > height_r) ? height_l : height_r) + 1;
}

static vertex_t *rotate_left(vertex_t *root)
{
    vertex_t *new_root = root->right;

    root->right = new_root->left;

    new_root->left = root;

    new_height(new_root);
    new_height(root);

    return new_root;
}

static vertex_t *rotate_right(vertex_t *root)
{
    vertex_t *new_root = root->left;

    root->left = new_root->right;

    new_root->right = root;

    new_height(new_root);
    new_height(root);

    return new_root;
}

vertex_t *balance_vertex(vertex_t *root) // балансировка узла
{
    new_height(root);

    if (balance_factor(root) == 2)
    {
        if (balance_factor(root->right) < 0)
            root->right = rotate_right(root->right);

        return rotate_left(root);
    }

    if (balance_factor(root) == -2)
    {
        if (balance_factor(root->left) > 0)
            root->left = rotate_left(root->left);

        return rotate_right(root);
    }

    return root; // балансировка не нужна
}

vertex_t *balance(vertex_t *root)
{
    if (root)
    {
        if (root->right)
            root->right = balance(root->right);
        if (root->left)
            root->left = balance(root->left);

        root = balance_vertex(root);
    }

    return root;
}

int get_count_vertex(vertex_t *root)
{
    if (!root)
        return 0;

    int l = get_count_vertex(root->left);
    int r = get_count_vertex(root->right);

    return 1 + l + r;
}

void print_tree(vertex_t *root, int p)
{
    if (!root)
    {
        return;
    }

    print_tree(root->right, p + 3);

    printf("\n");
    for (int i = 0; i < p; i++)
    {
        printf(" ");
    }

    printf("%3d\n", root->data);
    print_tree(root->left, p + 3);
}
