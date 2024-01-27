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

static void processStr(std::wstring &currStr, const int ngram, std::map<std::wstring, int> &ngramCounts)
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
            ngramCounts[ngram]++;
        }

        startPos = endPos + 1;
    }
}

int solution(const std::string &filename, const std::string &outputFilename, const int ngram)
{
    std::wifstream inputFile(filename);

    if (!inputFile.is_open())
    {
        std::wcerr << L"Ошибка открытия файла" << std::endl;
        return 1;
    }

    std::vector<std::wstring> vecStrText = getVectorText(inputFile);

    inputFile.close();

    std::map<std::wstring, int> ngramCounts;

    for (int i = 0; i < (int)vecStrText.size(); ++i)
        processStr(vecStrText[i], ngram, ngramCounts);

    // std::wofstream outputFile(outputFilename);

    // if (!outputFile.is_open())
    // {
    //     std::wcerr << L"Ошибка открытия файла" << std::endl;
    //     return 2;
    // }

    // for (const auto &entry : ngramCounts)
    //     outputFile << entry.first << ": " << entry.second << std::endl;

    // outputFile.close();

    return 0;
}
} // namespace serialVersion

namespace parallelVersion
{
// пытаюсь распараллелить по строкам

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

void parallelProcessStr(int i, std::vector<std::wstring> &vecStrText, int ngram, int numThreads, std::map<std::wstring, int> &localNgramCounts)
{
    for (int j = i; j < (int)vecStrText.size(); j += numThreads)
    {
        size_t startPos = 0;
        size_t endPos = 0;

        while (endPos != std::wstring::npos)
        {
            endPos = vecStrText[j].find(L' ', startPos);

            std::wstring word = vecStrText[j].substr(startPos, endPos - startPos);

            if (static_cast<int>(word.size()) < ngram)
            {
                startPos = endPos + 1;
                continue;
            }

            std::vector<std::wstring> ngrams = getNgramsByWord(word, ngram);

            for (const auto &ngram : ngrams)
                localNgramCounts[ngram]++;

            startPos = endPos + 1;
        }
    }
}

int solution(const std::string &filename, const std::string &outputFilename, const int ngram, const int numThreads)
{
    std::wifstream inputFile(filename);
    // std::wofstream outputFile(outputFilename);

    if (!inputFile.is_open())
    {
        std::wcerr << L"Ошибка открытия файла" << std::endl;
        return 1;
    }

    // if (!outputFile.is_open())
    // {
    //     std::wcerr << L"Ошибка открытия файла" << std::endl;
    //     return 2;
    // }

    std::vector<std::wstring> vecStrText = getVectorText(inputFile);
    std::map<std::wstring, int> ngramCounts;
    std::vector<std::thread> threads(numThreads);
    std::vector<std::map<std::wstring, int>> localNgramCounts(numThreads);

    for (int i = 0; i < numThreads; ++i)
        threads[i] = std::thread(parallelProcessStr, i, std::ref(vecStrText), ngram, numThreads, std::ref(localNgramCounts[i]));

    for (auto &thread : threads)
        thread.join();

    for (const auto &localCount : localNgramCounts)
        for (const auto &entry : localCount)
            ngramCounts[entry.first] += entry.second;

    // for (const auto &entry : ngramCounts)
    //     outputFile << entry.first << ": " << entry.second << std::endl;

    inputFile.close();
    // outputFile.close();

    return 0;
}

} // namespace parallelVersion

void getRandomText(const std::string &filename, const int numStr)
{
    std::wstring rusAlph = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

    std::wstring currStr(80, L' ');

    std::wofstream data(filename);

    if (!data.is_open())
    {
        std::wcout << L"Ошибка открытия файла" << std::endl;
        return;
    }

    for (int i = 0; i < numStr; ++i)
    {
        for (int j = 0; j < 80; ++j)
            currStr[j] = (rand() % 5) ? rusAlph[rand() % 32] : L' ';

        data << currStr << std::endl;
    }

    data.close();
}