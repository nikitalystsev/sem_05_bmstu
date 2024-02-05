#include "interface.h"

#include "tree_visual.h"

void vertex_to_dot(vertex_t *vertex, std::ofstream &file)
{
    if (vertex->left)
    {
        file << vertex->data << " [label=\"" << vertex->data << ", h = " << vertex->height << "\"]";
        file << vertex->left->data << " [label=\"" << vertex->left->data << ", h = " << vertex->left->height << "\"]";
        file << vertex->data << " -> " << vertex->left->data << " [color=blue];" << std::endl;
    }
    if (vertex->right)
    {
        file << vertex->data << " [label=\"" << vertex->data << ", h = " << vertex->height << "\"]";
        file << vertex->right->data << " [label=\"" << vertex->right->data << ", h = " << vertex->right->height << "\"]";
        file << vertex->data << " -> " << vertex->right->data << " [color=blue];" << std::endl;
    }
}

void tree_to_dot(vertex_t *root, std::ofstream &file)
{
    if (!root)
    {
        return;
    }

    vertex_to_dot(root, file);

    tree_to_dot(root->left, file);
    tree_to_dot(root->right, file);
}

int export_to_dot(const std::string &file_name, const std::string &tree_name, tree_t *tree)
{
    std::ofstream file(file_name);

    if (!file.is_open())
    {
        puts(RED "Ошибка открытия файла!\n" RESET);
        return ERR_OPEN_FILE;
    }

    file << "digraph " << tree_name << " {" << std::endl;

    tree_to_dot(tree->root, file);

    file << "}" << std::endl;

    file.close();

    std::string s = "dot -Tpng -O " + file_name;

    int rc = system(s.c_str());

    if (rc == 0)
        puts(GREEN "\nКартинка была успешно создана!" RESET);

    return rc;
}

void print_menu(void)
{
    printf(
        TURQ "\n----------------------------------------------------------|\n"
             "Программа для обработки ДДП и АВЛ-дерева.\n"
             "Элементом дерева является целое число.\n"

             "\nПравила:\n"
             "- добавить можно только уникальное число,\n"
             "  добавление дубликата будет проигнорировано;\n"

             "\nОперации для обработки дерева:\n"
             "1  - прочитать данные из файла;\n"
             "4  - визуализировать ДДП и АВЛ-дерево в виде png картинки;\n"
             "5  - поиск введенного с клавиатуры числа;\n"

             "\n0  - выйти из программы.\n"
             "\n----------------------------------------------------------|\n"
             "Выберите пункт меню:\n" RESET);
}

int read_menu_item(int &item)
{
    if (scanf("%d", &item) != 1)
    {
        puts(RED "\nНекорректный ввод пункта меню!" RESET);
        return ERR_MENU_ITEM;
    }

    if (item < 0 || item > 10)
    {
        puts(RED "\nНеверный номер пункта меню!" RESET);
        return ERR_MENU_ITEM;
    }

    return EXIT_SUCCESS;
}

static bool is_exist_file(const std::string &file_name)
{
    std::ifstream file(file_name);

    if (!file.is_open())
        return false;

    file.close();

    return true;
}

static int read_count_data(int &count_data)
{
    puts("\nВведите количество генерируемых данных "
         "(целое положительное число):");
    if (scanf("%d", &count_data) != 1)
    {
        puts(RED "\nНекорректный ввод количества генерируемых данных!" RESET);
        return ERR_COUNT_DATA;
    }

    if (count_data < 0)
    {
        puts(RED "\nНеверный ввод! "
                 "Количество генерируемых данных - число больше нуля!" RESET);
        return ERR_COUNT_DATA;
    }

    return EXIT_SUCCESS;
}

static void gen_data_file(const std::string &file_name, const int count_data)
{
    srand(time(NULL));

    std::ofstream file(file_name);

    if (!file.is_open())
    {
        std::cout << RED "\nОшибка открытия файла!" RESET << std::endl;
        return;
    }

    file << count_data << std::endl;

    for (int i = 0; i < count_data; i++)
    {
        int x = MIN_DATA + rand() % (MAX_DATA - MIN_DATA + 1);

        file << x << std::endl;
    }

    file.close();
}

static int read_numbers(const std::string &file_name, tree_t *_tree, bool is_balance)
{
    int rc = 0;

    std::ifstream file(file_name);

    if (!file.is_open())
    {
        puts(RED "\nОшибка открытия файла!\n" RESET);
        return ERR_OPEN_FILE;
    }

    int count, data;

    file >> count;

    for (int i = 0; i < count; i++)
    {
        file >> data;

        vertex_t *vertex = create_vertex(data, 0);

        if (!vertex)
        {
            file.close();
            return ERR_READ_DATA;
        }

        if (is_balance)
            _tree->root = add_vertex(_tree->root, vertex, true);
        else
            _tree->root = add_vertex(_tree->root, vertex, false);
    }

    file.close();

    return rc;
}

int read_data(int &count_data, tree_t *bst_tree, tree_t *awl_tree)
{
    free_tree(bst_tree);
    free_tree(awl_tree);

    std::string file_name;
    std::string data_file;

    int rc = 0;

    std::cout << TURQ "\nВведите имя файла: " RESET;
    std::cin >> file_name >> data_file;

    if (!is_exist_file(data_file))
    {
        if ((rc = read_count_data(count_data)) != 0)
            return rc;

        gen_data_file(data_file, count_data);
    }

    // std::string data_gv = data_file + GV;

    if ((rc = read_numbers(data_file, bst_tree, false)) != 0)
        return rc;

    if ((rc = read_numbers(data_file, awl_tree, true)) != 0)
        return rc;

    if (rc == 0)
        puts(GREEN "\nДанные были успешно прочитаны!" RESET);

    return rc;
}

int trees_to_dot(tree_t *bst_tree, tree_t *awl_tree)
{
    int rc = 0;

    if (is_empty_tree(bst_tree) || is_empty_tree(awl_tree))
    {
        puts(VIOLET "\nДерево пустое" RESET);
        return;
    }

    char data_file[MAX_STR_SIZE] = DATA_DIR;
    char balance_data_file[MAX_STR_SIZE] = DATA_DIR "balance_";

    char data_gv[MAX_STR_SIZE];

    if ((rc = read_file_name(data_gv)) != 0)
        return rc;

    strcat(data_file, data_gv);
    strcat(balance_data_file, data_gv);

    if ((rc = export_to_dot(data_file, "my_tree", tree)) != 0)
        return rc;

    if ((rc = export_to_dot(balance_data_file, "my_tree",
                            balance_tree)) != 0)
        return rc;

    return rc;
}

// void vertex_to_dot(vertex_t *vertex, FILE *file)
// {
//     if (vertex->left)
//     {
//         fprintf(file, "%d [label=\"%d, h = %d\"]", vertex->data,
//                 vertex->data, vertex->height);
//         fprintf(file, "%d [label=\"%d, h = %d\"]", vertex->left->data,
//                 vertex->left->data, vertex->left->height);
//         fprintf(file, "%d -> %d [color=blue];\n", vertex->data,
//                 vertex->left->data);
//     }
//     if (vertex->right)
//     {
//         fprintf(file, "%d [label=\"%d, h = %d\"]", vertex->data,
//                 vertex->data, vertex->height);
//         fprintf(file, "%d [label=\"%d, h = %d\"]", vertex->right->data,
//                 vertex->right->data, vertex->right->height);
//         fprintf(file, "%d -> %d [color=red];\n", vertex->data,
//                 vertex->right->data);
//     }
// }