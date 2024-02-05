#include "interface.h"

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

int read_data(int &count_data, tree_t *tree, tree_t *balance_tree)
{
    free_tree(tree);
    free_tree(balance_tree);

    std::string file_name;
    std::string data_file;

    char file_name[MAX_STR_SIZE];
    char data_file[MAX_STR_SIZE] = DATA_DIR;
    char data_gv[MAX_STR_SIZE];

    int rc = 0;

    std::cout << TURQ "\nВведите имя файла: " RESET;
    std::cin >> file_name >> data_file;

    if (!is_exist_file(data_file))
    {
        if ((rc = read_count_data(count_data)) != 0)
            return rc;

        gen_data_file(data_file, *count_data);
    }

    strcpy(data_gv, data_file);
    strcat(data_gv, GV);

    if ((rc = read_numbers(data_file, tree, false)) != 0)
        return rc;

    if ((rc = read_numbers(data_file, balance_tree, true)) != 0)
        return rc;

    if (rc == 0)
        puts(GREEN "\nДанные были успешно прочитаны!" RESET);

    return rc;
}