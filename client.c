/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:43 by rababaya          #+#    #+#             */
/*   Updated: 2025/03/20 15:22:20 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

int	g_status = 0;

void	status_handler(int sig)
{
	g_status = 1;
}

void	send_bit(char sending, pid_t server_pid)
{
	unsigned char	a;
	int				i;

	i = -1;
	a = 128;
	while (++i < 8)
	{
		g_status = 0;
		if (sending & (a >> i))
			kill(server_pid, SIGUSR1);
		else
			kill(server_pid, SIGUSR2);
		while (g_status == 0)
			usleep(100);
	}
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	unsigned char		*massage;
	struct sigaction	status_changer;

	if (argc == 3)
	{
		status_changer.sa_handler = &status_handler;
		status_changer.sa_flags = SA_RESTART;
		sigaction(SIGUSR1, &status_changer, NULL);
		server_pid = atoi(argv[1]);
		massage = (unsigned char *)argv[2];
		while (*massage)
		{
			send_bit(*massage, server_pid);
			massage++;
		}
		send_bit('\0', server_pid);
	}
}
