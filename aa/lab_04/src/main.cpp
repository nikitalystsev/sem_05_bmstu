#include <algorithm>
#include <fstream>
#include <iostream>
#include <locale> // Для корректной работы с кириллицей
#include <map>
#include <mutex>
#include <thread>
#include <unordered_map>
#include <vector>

std::mutex mutex;

std::wstring preprocessText(const std::wstring &text)
{
    std::wstring processedText = text;
    // Удаляем знаки препинания и приводим текст к нижнему регистру
    processedText.erase(std::remove_if(processedText.begin(), processedText.end(), ::iswpunct), processedText.end());
    std::transform(processedText.begin(), processedText.end(), processedText.begin(), ::towlower);
    return processedText;
}

std::vector<std::wstring> extractNgrams(const std::wstring &word, int n)
{
    std::vector<std::wstring> ngrams;
    for (size_t i = 0; i <= word.length() - n; ++i)
    {
        ngrams.push_back(word.substr(i, n));
    }
    return ngrams;
}

void processTextChunk(const std::wstring &text, int n, size_t start, size_t end, std::unordered_map<std::wstring, int> &ngramFreq)
{
    std::wcout << L"[+] вызов processTextChunk\n"
               << std::endl;

    std::wstring processedText = preprocessText(text.substr(start, end - start));
    std::wcout << L"[=] processedText: [" << processedText << L"]" << std::endl;

    // size_t pos = 0;
    // while ((pos = processedText.find(L' ', pos)) != std::wstring::npos)
    // {
    //     processedText.erase(pos, 1);
    // }

    // std::wcout << L"[=] processedText: [" << processedText << L"]" << std::endl;

    size_t startPos = 0;
    size_t endPos = 0;
    // std::wcout << L"[=] endPos = " << endPos << std::endl;
    while (endPos != std::wstring::npos)
    {
        // std::wcout << L"бля" << std::endl;
        // std::wcout << L"[=] endPos = " << endPos << std::endl;
        endPos = processedText.find(L' ', startPos);

        std::wstring word = processedText.substr(startPos, endPos - startPos);

        if (static_cast<int>(word.size()) < n)
        {
            // std::wcout << L"маловато, ебаный насвай" << std::endl;
            startPos = endPos + 1;
            // endPos = processedText.find(L' ', startPos);
            continue;
        }

        // std::wcout << L"[=] word: " << word << std::endl;

        std::vector<std::wstring> ngrams = extractNgrams(word, n);
        for (const auto &ngram : ngrams)
        {
            std::lock_guard<std::mutex> lock(mutex);
            ngramFreq[ngram]++;
        }

        startPos = endPos + 1;
        // endPos = processedText.find(L' ', startPos);
    }
}

void processText(const std::wstring &text, int n, std::unordered_map<std::wstring, int> &ngramFreq, int numThreads)
{
    std::vector<std::thread> threads;
    size_t chunkSize = text.size() / numThreads;

    for (int i = 0; i < numThreads; ++i)
    {
        size_t start = i * chunkSize;
        size_t end = (i == numThreads - 1) ? text.size() : (i + 1) * chunkSize;
        threads.emplace_back(processTextChunk, std::ref(text), n, start, end, std::ref(ngramFreq));
    }

    for (auto &thread : threads)
    {
        thread.join();
    }
}

void writeToFile(const std::unordered_map<std::wstring, int> &ngramFreq, const std::string &outputFile)
{
    // Записываем результаты в файл
    std::wofstream file(outputFile);
    if (file.is_open())
    {
        std::wcout << L"Количество n-грам: " << ngramFreq.size() << std::endl;

        for (const auto &entry : ngramFreq)
        {
            file << entry.first << L": " << entry.second << std::endl;
        }
        file.close();
    }
    else
    {
        std::wcout << L"Unable to open output file: " << std::endl;
    }
}

int main()
{
    // Устанавливаем локаль для корректной работы с кириллицей
    std::locale::global(std::locale(""));

    std::wifstream inputFile("src/text.txt"); // Замените "input.txt" на имя вашего файла с текстом
    std::wstring text((std::istreambuf_iterator<wchar_t>(inputFile)), std::istreambuf_iterator<wchar_t>());

    int n = 5;          // Замените на необходимое значение N
    int numThreads = 2; // Замените на необходимое количество потоков

    std::unordered_map<std::wstring, int> ngramFreq;
    processText(text, n, ngramFreq, numThreads);

    writeToFile(ngramFreq, "output_text2.txt"); // Замените "output.txt" на имя файла для записи результатов

    return 0;
}
