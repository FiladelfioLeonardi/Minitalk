/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fileonar <fileonar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:53:20 by fileonar          #+#    #+#             */
/*   Updated: 2024/12/02 16:28:25 by fileonar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_msg(char **msg_str)
{
	write(1, *msg_str, ft_strlen(*msg_str));
	ft_free_n_null((void **)msg_str);
	return ;
}

static void	recieve_msg(int signal)
{
	static int		bits = 0;
	static int		index = 0;
	static char		*msg_str = NULL;
	unsigned char	c;
	char			*tmp;

	bits <<= 1;
	if (signal == SIGUSR1)
		bits |= 1;
	index++;
	if (index == 8)
	{
		c = bits;
		bits = 0;
		index = 0;
		if (c == '\0')
			return (print_msg(&msg_str), (void) 0);
		if (msg_str)
			tmp = ft_strjoin(msg_str, (const char *)&c);
		else
			tmp = ft_strdup((const char *)&c);
		free(msg_str);
		msg_str = tmp;
	}
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, recieve_msg);
	signal(SIGUSR2, recieve_msg);
	while (1)
		pause();
	return (0);
}
