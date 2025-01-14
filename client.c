#include "miniTalk.h"

void	send_bit(int c, pid_t pidNum)
{
	int	j;

	j = 7;
	while (j >= 0)
	{
		if ((c >> j) & 1)
        {
			if(kill(pidNum, SIGUSR2) < 0)
                exit(1);
        }
		else
        {
			if(kill(pidNum, SIGUSR1) < 0)
                exit(1);
        }
		usleep(1000);
		j--;
	}
}
void	send_char(char *str, pid_t pidNum)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_bit(str[i++], pidNum);
	}
	send_bit('\0', pidNum);
}

void	send_server(int signal, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (signal == SIGUSR1)
	{
		ft_printf("Server with this PID (%d) got message \n", siginfo->si_pid);
		exit(0);
	}
	else
		ft_printf("The server not take message ");
}

int	main(int argc, char **argv)
{
	pid_t pidNum;
	struct sigaction client;
	if (argc != 3)
	{
		ft_printf("Usage: %s <PID> <message>\n", argv[0]);
		return (1);
	}
	pidNum = atoi(argv[1]);
	client.sa_flags = SA_SIGINFO;
	client.sa_sigaction = &send_server;
	if (pidNum <= 0)
    {
        ft_printf("Invalid PID\n");
		return (1);
    }
	if ((sigaction(SIGUSR1, &client, NULL)) < 0)
	{
		ft_printf("Message not Send");
		return (1);
	}
	send_char(argv[2], pidNum);
	while (1)
		pause();
	return (0);
}