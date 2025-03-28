/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 13:20:43 by rababaya          #+#    #+#             */
/*   Updated: 2025/03/21 18:23:58 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_status = 0;

void	status_handler(int sig)
{
	(void)sig;
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
		{
			if (kill(server_pid, SIGUSR1))
				error_handler("Kill error:");
		}
		else
		{
			if (kill(server_pid, SIGUSR2))
				error_handler("Kill error:");
		}
		while (g_status == 0)
			usleep(100);
	}
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	unsigned char		*message;
	struct sigaction	status_changer;

	if (argc == 3)
	{
		status_changer.sa_handler = &status_handler;
		status_changer.sa_flags = SA_RESTART;
		if (sigaction(SIGUSR1, &status_changer, NULL) == -1)
			error_handler("Sigaction error:");
		server_pid = ft_atoi(argv[1]);
		message = (unsigned char *)argv[2];
		while (*message)
		{
			send_bit(*message, server_pid);
			message++;
		}
		send_bit('\0', server_pid);
	}
	else
		ft_putstr_fd("Wrong argument number", 2);
}
