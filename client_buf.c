#include "miniTalk.h"
#include <stdio.h>

void send_bit(int c, pid_t pidNum)
{
    int j;

    j = 7;
    while (j >= 0)
    {
        if ((c >> j) & 1)
        {
            if (kill(pidNum, SIGUSR2) < 0)
                exit(1);
        }
        else
        {
            if (kill(pidNum, SIGUSR1) < 0)
                exit(1);
        }
        usleep(500);
        j--;
    }
}

void send_char(char *str, pid_t pidNum)
{
    int i;

    i = 0;
    while (str[i])
    {
        send_bit(str[i++], pidNum);
    }
    send_bit('\0', pidNum);
}

void send_server(int signal)
{
    if (signal == SIGUSR1)
    {
        printf("Server got message \n");
        exit(0);
    }
    else
        printf("The server did not take the message\n");
}

int main(int argc, char **argv)
{
    pid_t pidNum;
    if (argc != 3)
    {
        printf("Usage: %s <PID> <message>\n", argv[0]);
        return (1);
    }
    pidNum = ft_atoi(argv[1]);
    if (pidNum <= 0)
    {
        printf("Invalid PID\n");
        return (1);
    }
    if ((signal(SIGUSR1, send_server)) != 0)
    {
        printf("Message not sent\n");
        return (1);
    }
    int length = ft_strlen(argv[2]);
    char *length_str = ft_itoa(length);
    send_char(length_str,pidNum);
    send_char(argv[2], pidNum);
    pause();
    return (0);
}