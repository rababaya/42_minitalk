/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rababaya <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/13 13:47:09 by rababaya          #+#    #+#             */
/*   Updated: 2025/03/13 15:33:02 by rababaya         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void	sigusr1_handler(int sig)
{
	printf("hi\n");
}

int	main(void)
{
	struct sigaction	sigact;

	printf("%d\n", getpid());
	sigact.sa_handler = &sigusr1_handler;
	sigact.sa_flags = SA_RESTART;
	sigaction(SIGUSR1, &sigact, NULL);
	while (1)
	{
		usleep(1);
	}
}
