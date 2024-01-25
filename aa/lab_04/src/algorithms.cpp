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
// пытаюсь распараллелить по строкам

std::mutex mutex;
std::map<std::wstring, int> ngramCounts;

static std::vector<std::wstring> getNgramsByWord(const std::wstring &word, int ngram)
{
    std::vector<std::wstring> ngrams;

    for (size_t i = 0; i <= word.length() - ngram; ++i)
        ngrams.push_back(word.substr(i, ngram));

    return ngrams;
}

static std::vector<std::wstring> getVectorText(std::wifstream &inputFile)
{
    std::vector<std::wstring> vecStrText;
    std::wstring currStr;

    while (std::getline(inputFile, currStr))
    {
        currStr.erase(std::remove_if(currStr.begin(), currStr.end(), ::iswpunct), currStr.end());
        std::transform(currStr.begin(), currStr.end(), currStr.begin(), ::towlower);

        vecStrText.push_back(currStr);
    }

    return vecStrText;
}

static void processStr(std::wstring &currStr, const int ngram)
{
    size_t startPos = 0;
    size_t endPos = 0;

    while (endPos != std::wstring::npos)
    {
        endPos = currStr.find(L' ', startPos);

        std::wstring word = currStr.substr(startPos, endPos - startPos);

        if (static_cast<int>(word.size()) < ngram)
        {
            startPos = endPos + 1;
            continue;
        }

        std::vector<std::wstring> ngrams = getNgramsByWord(word, ngram);

        for (const auto &ngram : ngrams)
        {
            std::lock_guard<std::mutex> lock(mutex);
            ngramCounts[ngram]++;
        }

        startPos = endPos + 1;
    }
}

int solution(const std::string &filename, const std::string &outputFilename, const int ngram, const int numThreads)
{
    std::wifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        std::wcerr << L"Ошибка открытия файла" << std::endl;
        return 1;
    }

    std::vector<std::wstring> vecStrText = getVectorText(inputFile);

    inputFile.close();

    std::vector<std::thread> threads;
    for (int i = 0; i < numThreads; ++i)
    {
        threads.emplace_back([&, i]()
                             {         
            for (int j = i; j < (int)vecStrText.size(); j += numThreads) {
                processStr(vecStrText[j], ngram);
            } });
    }
    // Ожидание завершения всех потоков
    for (auto &thread : threads)
        thread.join();

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

} // namespace parallelVersion

void getRandomText(const std::string &filename, const int numStr)
{
    std::wstring rusAlph = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

    std::wstring currStr(81, L' ');

    std::wofstream data(filename);

    for (int i = 0; i < numStr; ++i)
    {
        for (int j = 0; j < 80; ++j)
            currStr[j] = (rand() % 5) ? rusAlph[rand() % 32] : L' ';

        data << currStr << std::endl;
    }

    data.close();
}