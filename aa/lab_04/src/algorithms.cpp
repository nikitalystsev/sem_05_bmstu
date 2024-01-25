#include "algorithms.h"

namespace serialVersion
{

static std::vector<std::wstring> getNgramsByWord(const std::wstring &word, int ngram)
{
    std::vector<std::wstring> ngrams;

    for (size_t i = 0; i <= word.length() - ngram; ++i)
        ngrams.push_back(word.substr(i, ngram));

    return ngrams;
}

static std::map<std::wstring, int> generateNgrams(std::wifstream &inputFile, int ngram)
{
    // Создаем словарь для хранения употреблений N-грамм
    std::map<std::wstring, int> ngramCounts;

    std::wstring word;
    // Обрабатываем каждое слово в файле
    while (inputFile >> word)
    {
        // Удаляем знаки препинания и приводим слово к нижнему регистру
        word.erase(std::remove_if(word.begin(), word.end(), ::iswpunct), word.end());
        std::transform(word.begin(), word.end(), word.begin(), ::towlower);

        if (static_cast<int>(word.size()) < ngram)
            continue;

        // Генерируем N-граммы для текущего слова
        std::vector<std::wstring> ngrams = getNgramsByWord(word, ngram);

        // Обновляем счетчики употреблений в словаре
        for (const auto &ngram : ngrams)
            ngramCounts[ngram]++;
    }

    return ngramCounts;
}

int solution(const std::string &filename, const std::string &outputFilename, const int ngram)
{
    std::wifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        std::wcerr << L"Ошибка открытия файла" << std::endl;
        return 1;
    }

    std::map<std::wstring, int> ngramCounts = generateNgrams(inputFile, ngram);

    inputFile.close();

    std::wofstream outputFile(outputFilename);

    if (!outputFile.is_open())
    {
        std::wcerr << L"Ошибка открытия файла" << std::endl;
        return 2;
    }

    for (const auto &entry : ngramCounts)
        outputFile << entry.first << ": " << entry.second << std::endl;

    outputFile.close();

    return 0;
}
} // namespace serialVersion

namespace parallelVersion
{

}