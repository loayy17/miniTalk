/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_buf.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:16:32 by lalhindi          #+#    #+#             */
/*   Updated: 2025/01/14 20:29:29 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "miniTalk.h"
#include <stdio.h>

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
		usleep(500);
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

void	send_server(int signal)
{
	if (signal == SIGUSR1)
	{
		ft_printf("Server got message \n");
		exit(0);
	}
	else
		ft_printf("The server did not take the message\n");
}

int	main(int argc, char **argv)
{
	pid_t pid_num;
	int length;

	if (argc != 3)
	{
		ft_printf("Usage: %s <PID> <message>\n", argv[0]);
		return (1);
	}
	pid_num = ft_atoi(argv[1]);
	if (pid_num <= 0)
	{
		ft_printf("Invalid PID\n");
		return (1);
	}
	if ((signal(SIGUSR1, send_server)) != 0)
	{
		ft_ft_printf("Message not sent\n");
		return (1);
	}
	length = ft_strlen(argv[2]);
	send_char(ft_itoa(length), pid_num);
	send_char(argv[2], pid_num);
	pause();
	return (0);
}