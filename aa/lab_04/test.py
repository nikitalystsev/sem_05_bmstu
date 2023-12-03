import nltk
from nltk import ngrams
from collections import defaultdict
import re


def preprocess_text(text):
    # Удаление символов, кроме букв
    cleaned_text = re.sub(r'[^а-яёА-ЯЁ]', ' ', text)
    return cleaned_text.lower()


def generate_ngrams(word, n):
    # Генерация N-грамм для слова
    word_ngrams = ngrams(word, n)
    return [''.join(gram) for gram in word_ngrams]


def process_text(text, n):
    # Предварительная обработка текста
    cleaned_text = preprocess_text(text)

    # Разбиение текста на слова
    words = cleaned_text.split()

    # Словарь для хранения употреблений N-грамм
    ngram_counts = defaultdict(int)

    for word in words:
        word_ngrams = generate_ngrams(word, n)
        for ngram in word_ngrams:
            ngram_counts[ngram] += 1

    return ngram_counts


def main():
    n = 3  # Задайте значение N (3, 4, 5)
    input_text = """Ваш текст на русском языке для анализа должен быть здесь."""

    # Подсчет употреблений N-грамм
    ngram_counts = process_text(input_text, n)

    # Вывод результатов
    for ngram, count in ngram_counts.items():
        print(f'{ngram}: {count}')


if __name__ == "__main__":
    main()
