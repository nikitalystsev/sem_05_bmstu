
#include "apue.h"
#include <errno.h>
#include <fcntl.h>
#include <pthread.h>
#include <sys/resource.h>
#include <syslog.h>

#define _GNU_SOURCE
#include <sys/types.h>
#include <unistd.h>

#define LOCKFILE "/var/run/daemon.pid"
#define CONFFILE "/etc/daemon.conf"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

sigset_t mask;

void daemonize(const char *cmd)
{
    int i, fd0, fd1, fd2;
    pid_t pid;
    struct rlimit rl;
    struct sigaction sa;

    /*
     * Сброс маски создания файлов в значение 0
     */
    umask(0);

    /*
     * Получить максимально возможный номер дескриптора файла.
     */
    if (getrlimit(RLIMIT_NOFILE, &rl) < 0)
    {
        fprintf(stderr, "%s: невозможно получить максимальный номер дескриптора", cmd);
        exit(1);
    }

    if ((pid = fork()) < 0)
        fprintf(stderr, "%s: ошибка вызова функции fork", cmd);
    else if (pid != 0)
        exit(0);

    /*
     * Создаем новый сеанс
     */
    if (setsid() == -1)
    {
        perror("Ошибка setsid");
        exit(EXIT_FAILURE);
    }

    /*
     * Обеспечить невозможность обретения управляющего терминала в будущем.
     */
    sa.sa_handler = SIG_IGN;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
    {
        fprintf(stderr, "Невозможно игнорировать сигнал SIGHUP");
        exit(1);
    }

    /*
     * Назначить корневой каталог текущим рабочим каталогом,
     * чтобы впоследствии можно было отмонтировать файловую систему.
     */
    if (chdir("/") < 0)
    {
        fprintf(stderr, "Невозможно сделать текущим рабочим каталогом /");
        exit(1);
    }

    /*
     * Закрыть все открытые файловые дескрипторы.
     */
    if (rl.rlim_max == RLIM_INFINITY)
        rl.rlim_max = 1024;
    for (i = 0; i < rl.rlim_max; i++)
        close(i);

    /*
     * Присоединить файловые дескрипторы 0, 1 и 2 к /dev/null.
     */
    fd0 = open("/dev/null", O_RDWR);
    fd1 = dup(0);
    fd2 = dup(0);

    /*
     * Инициализировать файл журнала.
     */
    openlog(cmd, LOG_CONS, LOG_DAEMON);
    if (fd0 != 0 || fd1 != 1 || fd2 != 2)
    {
        syslog(LOG_ERR, "ошибочные файловые дескрипторы %d %d %d",
               fd0, fd1, fd2);
        exit(1);
    }
}

int lockfile(int fd)
{
    struct flock fl;

    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;

    return fcntl(fd, F_SETLK, &fl);
}

int already_running(void)
{
    int fd;
    char buf[16];

    fd = open(LOCKFILE, O_RDWR | O_CREAT, LOCKMODE);

    if (fd < 0)
    {
        syslog(LOG_ERR, "can't open %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }

    if (lockfile(fd) < 0)
    {
        if (errno == EACCES || errno == EAGAIN)
        {
            close(fd);
            return (1);
        }

        syslog(LOG_ERR, "can't lock %s: %s", LOCKFILE, strerror(errno));
        exit(1);
    }

    ftruncate(fd, 0);
    sprintf(buf, "%ld", (long)getpid());
    write(fd, buf, strlen(buf) + 1);

    return (0);
}

void reread(void)
{
    FILE *fd;

    char buffer[256];

    if ((fd = fopen(CONFFILE, "r")) == NULL)
    {
        syslog(LOG_INFO, "Ошибка fopen " CONFFILE "");
        exit(EXIT_FAILURE);
    }

    fgets(buffer, 256, fd);

    fclose(fd);
}

void *thr_fn(void *arg)
{
    int err, signo;
    for (;;)
    {
        syslog(LOG_INFO, "Thread (id = %d) send '%s'", gettid(), (char *)arg);
        err = sigwait(&mask, &signo);
        if (err != 0)
        {
            syslog(LOG_ERR, "ошибка вызова функции sigwait");
            pthread_exit(1);
        }
        switch (signo)
        {
        case SIGHUP:
            syslog(LOG_INFO, "read CONFIGFILE");
            reread();
            break;
        case SIGTERM:
            syslog(LOG_INFO, "got SIGTERM;");
            exit(0);
        case SIGINT:
            syslog(LOG_INFO, "got SIGINT");
            pthread_exit(0);
        default:
            syslog(LOG_INFO, "получен сигнал %d\n", signo);
        }
    }
}

int main(int argc, char *argv[])
{
    int err;
    pthread_t tid;
    char *cmd;
    struct sigaction sa;
    pthread_t tid_msg[2];
    int status_addr, status;

    if ((cmd = strrchr(argv[0], '/')) == NULL)
        cmd = argv[0];
    else
        cmd++;

    /*
     * Перейти в режим демона.
     */
    daemonize(cmd);

    /*
     * Убедиться, что ранее не была запущена другая копия демона.
     */
    if (already_running())
    {
        syslog(LOG_ERR, "Демон уже запущен");
        exit(EXIT_FAILURE);
    }

    /*
     * Восстановить действие по умолчанию для сигнала SIGHUP
     * и заблокировать все сигналы.
     */
    sa.sa_handler = SIG_DFL;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;
    if (sigaction(SIGHUP, &sa, NULL) < 0)
    {
        syslog(LOG_INFO, "Невозможно восстаносить действие SIG_DFL для SIGHUP");
        exit(EXIT_FAILURE);
    }

    sigfillset(&mask);
    if ((err = pthread_sigmask(SIG_BLOCK, &mask, NULL)) != 0)
    {
        syslog(LOG_INFO, "Ошибка выполнения операции SIG_BLOCK");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < 2; ++i)
    {
        char *msg = (i == 0) ? "aaa" : "bbb";
        err = pthread_create(&tid_msg[i], NULL, thr_fn, msg);
        if (err == -1)
        {
            syslog(LOG_INFO, "Невозможно создать поток");
            exit(EXIT_FAILURE);
        }
    }

    for (int i = 0; i < 2; i++)
    {
        status = pthread_join(tid_msg[i], (void **)&status_addr);
        if (status != 0)
        {
            syslog("main error: can't join thread, status = %d\n", status);
            exit(EXIT_FAILURE);
        }
    }

    /*
     * Proceed with the rest of the daemon.
     */
    while (1)
    {
        time_t cur_time = time(NULL);
        syslog(LOG_NOTICE, "Time: %s", ctime(&cur_time));
        sleep(1);
    }

    return 0;
}