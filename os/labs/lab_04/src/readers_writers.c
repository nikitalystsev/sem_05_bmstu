#include <windows.h>
#include <stdbool.h>
#include <stdio.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>
#include <unistd.h>
// определяем количество читателей и писателей
#define COUNT_READERS 5
#define COUNT_WRITERS 3

// HANDLE -- тип дескриптора объекта
HANDLE canRead;  // переменная - событие, пропускающая читателей
HANDLE canWrite; // переменная - событие, пропускающая писателей
HANDLE mutex;    // Переменная mutex -- гарантия монопольного доступа к ресурсу

// собственно, ресурс
int value = 0;

LONG waitingWritersCount = 0; // количество ждущих писателей
LONG waitingReadersCount = 0; // количество ждущих читателей
LONG activeReadersCount = 0;  // количество активных читателей
bool activeWriter = false;    // есть ли активный писатель

// определили массивы дескрипторов созданных потоков
// для читателей и писателей
HANDLE readerThreads[COUNT_READERS];
HANDLE writerThreads[COUNT_WRITERS];

// сигналы работают благодаря <unistd.h>
int flag = 1;

void signal_handler(int signal)
{
    printf("Catch signal: %d PID: %d; _PID: %d Thread: %d\n", signal, getpid(), GetCurrentProcessId(), GetCurrentThreadId());
    flag = 0;
}

void startRead()
{
    // инкремент ждущих читателей
    InterlockedIncrement(&waitingReadersCount);

    if (activeWriter || WaitForSingleObject(canWrite, 0) == WAIT_OBJECT_0)
    {
        WaitForSingleObject(canRead, INFINITE);
    }

    // захват мьютекса (делает операцию неделимой)
    WaitForSingleObject(mutex, INFINITE);
    // декремент ждущих читателей
    InterlockedDecrement(&waitingReadersCount);
    // декремент активных читателей
    InterlockedIncrement(&activeReadersCount);
    // Чтобы следующий читатель в очереди читателей смог начать чтение
    SetEvent(canRead);
    // освобождение ранее захваченного мьютекса
    ReleaseMutex(mutex);
}

void stopRead()
{
    // декремент активных читателей
    InterlockedDecrement(&activeReadersCount);

    if (!activeReadersCount)
    {
        SetEvent(canWrite);
    }
}

void startWrite()
{
    // инкремент ждущих писателей
    InterlockedIncrement(&waitingWritersCount);

    if (activeReadersCount > 0 || activeWriter)
    {
        WaitForSingleObject(canWrite, INFINITE);
    }

    // декремент ждущих писателей
    InterlockedDecrement(&waitingWritersCount);

    activeWriter = true;
    // сбрасываем, другим писать нельзя
    ResetEvent(canWrite);
}

void stopWrite()
{
    activeWriter = false;

    if (waitingReadersCount)
    {
        SetEvent(canRead);
    }
    else
    {
        SetEvent(canWrite);
    }
}

DWORD WINAPI reader()
{
    while (flag)
    {
        int sleepTime = rand() % 100;
        Sleep(sleepTime);

        startRead();
        printf("Reader (id = %lu) read:  %d\n", GetCurrentThreadId(), value);
        stopRead();
    }

    exit(EXIT_SUCCESS);
}

DWORD WINAPI writer()
{
    while (flag)
    {
        int sleepTime = rand() % 100;
        Sleep(sleepTime);

        startWrite();
        ++value;
        printf("Writer (id = %lu) write: %d\n", GetCurrentThreadId(), value);
        stopWrite();
    }

    exit(EXIT_SUCCESS);
}

int main(void)
{
    if (signal(SIGINT, signal_handler) == SIG_ERR)
    {
        perror("Ошибка signal\n");
        exit(EXIT_FAILURE);
    }

    printf("Process Id = %lu\n", GetCurrentProcessId());
    printf("getpid: Process Id = %lu\n", getpid());

    srand(time(NULL));
    // для реализации монитора достаточно  таких средств взаимоисключения
    // как события: с автосбросом и со сбросом вручную
    // Мьютекс включается в приложение искусственно

    /*создаем событие canRead c обычными правами доступа,
      дескриптором защиты "по умолчанию", не наследуемое дочерними
      процессами.
      событие canRead c автосбросом, изначально в несигнальном состоянии,
      безымянное, поскольку глобальный объект и  используется
      для синхронизации внутри одного процесса
    */
    canRead = CreateEvent(NULL, FALSE, FALSE, NULL);

    if (canRead == 0)
    {
        perror("Ошибка CreateEvent (canRead)");
        exit(EXIT_FAILURE);
    }

    /*аналогично событию canRead создаем событие canWrite
      событие canWrite со сбросом вручную, изначально в несигнальном состоянии,
      безымянное, поскольку глобальный объект и  используется
      для синхронизации внутри одного процесса
    */
    canWrite = CreateEvent(NULL, TRUE, FALSE, NULL);

    if (canWrite == 0)
    {
        perror("Ошибка CreateEvent (canWrite)");
        exit(EXIT_FAILURE);
    }

    /*создаем мьютекс - средство взаимоисключения
      - первый параметр тайна
      - мьютекс свободный, т. к. FALSE. Было бы TRUE, был бы захвачен текущим потоком
      - мьютекс безымянный
     */
    mutex = CreateMutex(NULL, FALSE, NULL);

    if (mutex == NULL)
    {
        perror("Ошибка CreateMutex");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < COUNT_READERS; i++)
    {
        /*создаем очередной поток для читателя:
          - атрибуты защиты "по умолчанию"
          - размер стека по умолчанию
          - адрес функции, с которой следует  начать выполнение потока: -
          - переменная, которая передается в поток: -
          - исполнение потока начинается немедленно
          - переменная, содержащая идентификатор потока: NULL
         */
        readerThreads[i] = CreateThread(NULL, 0, &reader, NULL, 0, NULL);

        if (readerThreads[i] == NULL)
        {
            perror("Ошибка CreateThread (reader)");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < COUNT_WRITERS; i++)
    {
        /*создаем очередной поток для писателя:
          - атрибуты защиты "по умолчанию"
          - размер стека по умолчанию
          - адрес функции, с которой следует  начать выполнение потока: -
          - переменная, которая передается в поток: -
          - исполнение потока начинается немедленно
          - переменная, содержащая идентификатор потока: NULL
         */
        writerThreads[i] = CreateThread(NULL, 0, &writer, NULL, 0, NULL);

        if (writerThreads[i] == NULL)
        {
            perror("Ошибка CreateThread (writer)");
            exit(EXIT_FAILURE);
        }
    }

    // COUNT_READERS - кол-во инетерсующих нас объектов ядра.
    // readerThreads - указатель на массив описателей объектов ядра.
    // TRUE - функция не даст потоку возобновить свою работу, пока не освободятся все объекты.
    // INFINITE - указывает, сколько времени поток готов ждать освобождения объекта.
    WaitForMultipleObjects(COUNT_WRITERS, writerThreads, TRUE, INFINITE);
    WaitForMultipleObjects(COUNT_READERS, readerThreads, TRUE, INFINITE);

    // в конце все надо освободить
    for (int i = 0; i < COUNT_READERS; i++)
    {
        CloseHandle(readerThreads[i]);
    }

    for (int i = 0; i < COUNT_WRITERS; i++)
    {
        CloseHandle(writerThreads[i]);
    }

    CloseHandle(canRead);
    CloseHandle(canWrite);
    CloseHandle(mutex);

    return 0;
}