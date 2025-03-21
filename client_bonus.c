/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:22:20 by rababaya          #+#    #+#             */
/*   Updated: 2025/03/21 18:11:05 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	g_status = 0;

void	status_handler(int sig)
{
	(void)sig;
	g_status = 1;
}

void	success_execution(int sig)
{
	(void)sig;
	ft_putstr_fd("Successfully sended message!\n", 1);
	exit(1);
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

void	signal_setuper(struct sigaction *sa, void (*handler)(int), int signal)
{
	sa->sa_handler = handler;
	sa->sa_flags = SA_RESTART;
	if (sigaction(signal, sa, NULL) == -1)
		error_handler("Sigaction error:");
}

int	main(int argc, char **argv)
{
	pid_t				server_pid;
	unsigned char		*message;
	struct sigaction	status_changer;
	struct sigaction	success_checker;

	if (argc == 3)
	{
		signal_setuper(&status_changer, &status_handler, SIGUSR1);
		signal_setuper(&success_checker, &success_execution, SIGUSR2);
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
	while (1)
		pause();
}
