/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:16:56 by lalhindi          #+#    #+#             */
/*   Updated: 2025/01/14 20:25:34 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniTalk.h"

void	print_num(int sig_num, siginfo_t *siginfo, void *context)
{
	(void)context;
	if (sig_num == SIGUSR2)
		g_mini.character = (g_mini.character << 1) | 1;
	else if (sig_num == SIGUSR1)
		g_mini.character = (g_mini.character << 1);
	g_mini.counter++;
	if (g_mini.counter == 8)
	{
		if (g_mini.character == 0)
		{
			write(1, "\n", 1);
			if (kill(siginfo->si_pid, SIGUSR1) < 0)
				exit(1);
		}
		else
			write(1, &g_mini.character, 1);
		g_mini.counter = 0;
		g_mini.character = 0;
	}
}

int	main(int argc, char **argv)
{
	struct sigaction	action;

	if (argc != 1 || argv[1])
		return (1);
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = &print_num;
	sigemptyset(&action.sa_mask);
	g_mini.character = 0;
	g_mini.counter = 0;
	ft_printf("Waiting for signals. PID: %d\n", getpid());
	if (sigaction(SIGUSR1, &action, NULL) < 0)
	{
		ft_printf("ERORR when receive SIGNAL");
		return (1);
	}
	if (sigaction(SIGUSR2, &action, NULL) < 0)
	{
		ft_printf("ERORR Receive SIGNAL");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
