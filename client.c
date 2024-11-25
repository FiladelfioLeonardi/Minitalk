/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fileonar <fileonar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 21:02:25 by fileonar          #+#    #+#             */
/*   Updated: 2024/11/25 01:41:31 by fileonar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

static void	send_msg_char(char c, int pid)
{
	int	bits;

	bits = 8;
	while (bits > 0)
	{
		if ((c >> bits) & 1)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(200);
		bits--;
	}
}

static void send_msg(char *msg, int pid)
{
	while(*msg)
	{
		send_msg_char(*msg, pid);
		msg++;
	}
	usleep(200);
	send_msg_char(pid, '\0');
}

int main(int argc, char **argv)
{
	int		pid;
	char	*msg;
	
	if (argc != 3)
		return (ft_printf("Usage: ./client [PID] [MSG]\n"), EXIT_FAILURE);
	pid = ft_atoi(argv[1]);
	msg = argv[2];
	send_msg(msg, pid);
	return (0);
}