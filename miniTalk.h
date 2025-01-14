/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniTalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lalhindi <lalhindi@student.42amman.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/14 20:17:47 by lalhindi          #+#    #+#             */
/*   Updated: 2025/01/14 20:17:48 by lalhindi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_TALK_H
# define MINI_TALK_H

# define _DEFAULT_SOURCE
# include "./Libft/libft.h"
# include <signal.h>
# include <stdlib.h>
# include <unistd.h>

typedef struct s_mini
{
	char	character;
	int		counter;
	int		indicator;
	int		length;
	char	*buffer;
	int		oncetime;
	int		index;
}			t_mini;

t_mini		g_mini;

#endif