/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fileonar <fileonar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:02:25 by fileonar          #+#    #+#             */
/*   Updated: 2024/11/27 17:22:05 by fileonar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_msg_char(char c, int server_pid)
{
	int	bits;

	bits = 7;
	while (bits >= 0)
	{
		if ((c >> bits) & 1)
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		usleep(500);
		bits--;
	}
}

static void	send_msg(char *msg, int server_pid)
{
	while (*msg)
	{
		send_msg_char(*msg, server_pid);
		msg++;
	}
	usleep(200);
	send_msg_char('\0', server_pid);
}

int	main(int argc, char **argv)
{
	int		server_pid;
	char	*msg;

	if (argc != 3)
		return (ft_printf("Usage: ./client [PID] [MSG]\n"), EXIT_FAILURE);
	server_pid = ft_atoi(argv[1]);
	msg = argv[2];
	send_msg(msg, server_pid);
	return (0);
}
