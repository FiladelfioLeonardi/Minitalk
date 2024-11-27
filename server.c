/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fileonar <fileonar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/23 18:53:20 by fileonar          #+#    #+#             */
/*   Updated: 2024/11/27 17:22:18 by fileonar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	print_msg(char **msg_str)
{
	ft_printf("%s", *msg_str);
	ft_free_n_null((void **)&*msg_str);
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
			print_msg(&msg_str);
		if (msg_str)
			tmp = ft_strjoin(msg_str, (const char *)&c);
		else
			tmp = ft_strdup((const char *)&c);
		free(msg_str);
		msg_str = tmp;
	}
}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 1)
		return (ft_printf("Usage: ./server\n"), EXIT_FAILURE);
	ft_printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, recieve_msg);
	signal(SIGUSR2, recieve_msg);
	while (1)
		pause();
	return (0);
}
