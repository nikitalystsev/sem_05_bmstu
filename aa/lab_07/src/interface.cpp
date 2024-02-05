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