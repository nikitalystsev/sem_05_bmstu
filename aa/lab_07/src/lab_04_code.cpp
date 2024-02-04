#include "lab_04_code.h"

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

int readFile(std::string &filename, std::vector<std::wstring> &vecStrText)
{
    std::wifstream inputFile(filename);
    if (!inputFile.is_open())
    {
        std::wcerr << L"Ошибка открытия файла" << std::endl;
        return 1;
    }

    vecStrText = getVectorText(inputFile);

    inputFile.close();

    return 0;
}

int solution(std::vector<std::wstring> &vecStrText, const std::string &outputFilename, const int ngram, const int numThreads)
{
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

void getRandomText(const std::string &filename, const int numStr, const int strLength)
{
    std::wstring rusAlph = L"абвгдеёжзийклмнопрстуфхцчшщъыьэюя";

    std::wstring currStr(strLength, L' ');

    std::wofstream data(filename);

    if (!data.is_open())
    {
        std::wcout << L"Ошибка открытия файла" << std::endl;
        return;
    }

    for (int i = 0; i < numStr; ++i)
    {
        for (int j = 0; j < strLength; ++j)
            currStr[j] = (rand() % 5) ? rusAlph[rand() % 32] : L' ';

        data << currStr << std::endl;
    }

    data.close();
}