#include <algorithm>
#include <fstream>
#include <iostream>
#include <map>
#include <vector>

std::vector<std::wstring> generateNgrams(const std::wstring &word, int n)
{
    std::vector<std::wstring> ngrams;
    for (size_t i = 0; i <= word.length() - n; ++i)
    {
        ngrams.push_back(word.substr(i, n));
    }
    return ngrams;
}

int main()
{
    // Установка локали для корректной работы с символами Юникода
    std::locale::global(std::locale(""));

    // Открываем файл с текстом на русском языке
    std::wifstream inputFile("/home/nikita/bmstu/sem_05/aa/lab_04/src/test.txt");

    if (!inputFile.is_open())
    {
        std::wcerr << L"Unable to open the file" << std::endl;
        return 1;
    }

    // Создаем словарь для хранения употреблений N-грамм
    std::map<std::wstring, int> ngramCounts;

    // N, который вы хотите использовать (3, 4, 5 и так далее)
    int n = 3;

    // Обрабатываем каждое слово в файле
    std::wstring word;
    while (inputFile >> word)
    {
        if (static_cast<int>(word.size()) < n)
            continue;

        // Приводим слово к нижнему регистру, если необходимо
        std::transform(word.begin(), word.end(), word.begin(), ::tolower);

        // Генерируем N-граммы для текущего слова
        std::vector<std::wstring> ngrams = generateNgrams(word, n);

        // Обновляем счетчики употреблений в словаре
        for (const auto &ngram : ngrams)
        {
            ngramCounts[ngram]++;
        }
    }

    // Закрываем файл
    inputFile.close();

    // Создаем и открываем файл для записи словаря
    std::wofstream outputFile("ngram_counts.txt");

    // Записываем употребления N-грамм в файл
    for (const auto &entry : ngramCounts)
    {
        outputFile << entry.first << ": " << entry.second << std::endl;
    }

    // Закрываем файл
    outputFile.close();

    return 0;
}
