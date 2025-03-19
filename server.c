/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 17:04:11 by rababaya          #+#    #+#             */
/*   Updated: 2025/03/19 17:29:50 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	sig_handler(int sig)
{
	static unsigned char	a = 0;
	static int				bit = 0;

	if (sig == SIGUSR1)
		a |= (128 >> bit);
	else
		a |= 0;
	bit++;
	if (bit == 8)
	{
		write(1, &a, 1);
		bit = 0;
		a = 0;
	}
}

int	main(void)
{
	struct sigaction	sig;

	printf("%d\n", getpid());
	sig.sa_handler = &sig_handler;
	sig.sa_flags = SA_RESTART;
	sigemptyset(&sig.sa_mask);
	sigaddset(&sig.sa_mask, SIGUSR1);
	sigaddset(&sig.sa_mask, SIGUSR2);
	sigaction(SIGUSR1, &sig, NULL);
	sigaction(SIGUSR2, &sig, NULL);
	while (1)
	{
		usleep(1);
	}
}
