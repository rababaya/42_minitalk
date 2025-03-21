/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:30:39 by rababaya          #+#    #+#             */
/*   Updated: 2025/03/21 18:26:58 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	a = 0;
	static int				bit = 0;

	(void)ucontext;
	if (sig == SIGUSR1)
		a |= (128 >> bit);
	bit++;
	if (bit == 8)
	{
		write(1, &a, 1);
		if (a == '\0')
		{
			if (kill(info->si_pid, SIGUSR2))
				error_handler("Kill error:");
		}
		bit = 0;
		a = 0;
	}
	if (kill(info->si_pid, SIGUSR1))
		error_handler("Kill error:");
}

int	main(void)
{
	struct sigaction	sig;

	ft_putnbr_fd(getpid(), 1);
	ft_putstr_fd("\n", 1);
	sig.sa_sigaction = &sig_handler;
	sig.sa_flags = SA_RESTART | SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGUSR1);
	sigaddset(&sig.sa_mask, SIGUSR2);
	if (sigaction(SIGUSR1, &sig, NULL))
		error_handler("Kill error:");
	if (sigaction(SIGUSR2, &sig, NULL))
		error_handler("Kill error:");
	while (1)
		pause();
}
