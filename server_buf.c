/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_buf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:16:46 by lalhindi          #+#    #+#             */
/*   Updated: 2025/01/14 20:23:29 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniTalk.h"

t_mini	g_mini;

void	shift_bit(int sig_num)
{
	if (sig_num == SIGUSR2)
		g_mini.character = (g_mini.character << 1) | 1;
	else if (sig_num == SIGUSR1)
		g_mini.character = (g_mini.character << 1);
	g_mini.counter++;
}

void	ft_len_char(void)
{
	if (g_mini.character == '\0')
		g_mini.indicator = 1;
	else
	{
		g_mini.length = g_mini.length * 10 + (g_mini.character - '0');
	}
}

void	ft_message_in_buffer(siginfo_t *siginfo)
{
	if (g_mini.character == '\0')
	{
		g_mini.indicator = 0;
		g_mini.buffer[g_mini.length] = '\0';
		write(1, g_mini.buffer, g_mini.length);
		g_mini.index = 0;
		g_mini.oncetime = 0;
		free(g_mini.buffer);
		g_mini.buffer = NULL;
		write(1, "\n", 1);
		if (kill(siginfo->si_pid, SIGUSR1) < 0)
			exit(EXIT_FAILURE);
	}
	else if (!g_mini.oncetime)
	{
		g_mini.oncetime = 1;
		g_mini.buffer = ft_calloc((g_mini.length + 1), sizeof(char));
		if (!g_mini.buffer)
			exit(EXIT_FAILURE);
		g_mini.buffer[g_mini.index++] = g_mini.character;
	}
	else
		g_mini.buffer[g_mini.index++] = g_mini.character;
}

void	print_num(int sig_num, siginfo_t *siginfo, void *context)
{
	(void)context;
	shift_bit(sig_num);
	if (g_mini.counter == 8)
	{
		if (!g_mini.indicator)
			ft_len_char();
		else
			ft_message_in_buffer(siginfo);
		g_mini.character = 0;
		g_mini.counter = 0;
	}
}

int	main(void)
{
	struct sigaction	action;

	ft_printf("Server is running. PID: %d\n", getpid());
	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = &print_num;
	sigemptyset(&action.sa_mask);
	ft_bzero(&g_mini, sizeof(t_mini));
	if (sigaction(SIGUSR1, &action, NULL) < 0 || sigaction(SIGUSR2, &action,
			NULL) < 0)
	{
		ft_printf("Error setting up signal handlers");
		return (1);
	}
	while (1)
		pause();
	return (0);
}
