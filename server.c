/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:04:11 by rababaya          #+#    #+#             */
/*   Updated: 2025/03/20 15:21:30 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	sig_handler(int sig, siginfo_t *info, void *ucontext)
{
	static unsigned char	a = 0;
	static int				bit = 0;
	struct sigaction		block_mask;

	sigemptyset(&block_mask.sa_mask);
	sigaddset(&block_mask.sa_mask, SIGUSR1);
	sigaddset(&block_mask.sa_mask, SIGUSR2);
	sigprocmask(SIG_BLOCK, &block_mask.sa_mask, NULL);
	if (sig == SIGUSR1)
		a |= (128 >> bit);
	bit++;
	if (bit == 8)
	{
		write(1, &a, 1);
		bit = 0;
		a = 0;
	}
	kill(info->si_pid, SIGUSR1);
	sigprocmask(SIG_UNBLOCK, &block_mask.sa_mask, NULL);
}

int	main(void)
{
	struct sigaction	sig;

	printf("%d\n", getpid());
	sig.sa_sigaction = &sig_handler;
	sig.sa_flags = SA_RESTART;
	sig.sa_flags = SA_SIGINFO;
	sigemptyset(&sig.sa_mask);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
		pause();
}
