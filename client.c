/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:16:40 by lalhindi          #+#    #+#             */
/*   Updated: 2025/01/14 20:30:06 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniTalk.h"

void	send_bit(int c, pid_t pid_num)
{
	int	j;

	j = 7;
	while (j >= 0)
	{
		if ((c >> j) & 1)
		{
			if (kill(pid_num, SIGUSR2) < 0)
				exit(1);
		}
		else
		{
			if (kill(pid_num, SIGUSR1) < 0)
				exit(1);
		}
		usleep(1000);
		j--;
	}
}
void	send_char(char *str, pid_t pid_num)
{
	int	i;

	i = 0;
	while (str[i])
	{
		send_bit(str[i++], pid_num);
	}
	send_bit('\0', pid_num);
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
	pid_t pid_num;
	struct sigaction client;
	if (argc != 3)
	{
		ft_printf("Usage: %s <PID> <message>\n", argv[0]);
		return (1);
	}
	pid_num = atoi(argv[1]);
	client.sa_flags = SA_SIGINFO;
	client.sa_sigaction = &send_server;
	if (pid_num <= 0)
	{
		ft_printf("Invalid PID\n");
		return (1);
	}
	if ((sigaction(SIGUSR1, &client, NULL)) < 0)
	{
		ft_printf("Message not Send");
		return (1);
	}
	send_char(argv[2], pid_num);
	while (1)
		pause();
	return (0);
}