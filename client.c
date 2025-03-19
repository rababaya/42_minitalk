/* ************************************************************************** */
/*																			  */
/*														  :::	   ::::::::   */
/*	 client.c											:+:		 :+:	:+:   */
/*													  +:+ +:+		  +:+	  */
/*	 By: rababaya <marvin@42.fr>					+#+  +:+	   +#+		  */
/*												  +#+#+#+#+#+	+#+			  */
/*	 Created: 2025/03/13 15:01:15 by rababaya		   #+#	  #+#			  */
/*	 Updated: 2025/03/18 14:57:28 by rababaya		  ###	########.fr		  */
/*																			  */
/* ************************************************************************** */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <signal.h>

void send_bit(char sending, pid_t server_pid)
{
	unsigned char	a;
	int		i;

	i = -1;
	a = 128;
	while (++i < 8)
	{
		printf("step:%d\n", i);
		if (sending & (a >> i))
		{
			printf("1\n");
			kill(server_pid, SIGUSR1);
		}
		else
		{
			printf("0\n");
			kill(server_pid, SIGUSR2);
		}
	}
}

int	main(int argc, char **argv)
{
	pid_t			server_pid;
	unsigned char	*massage;
	if (argc == 3)
	{
		server_pid = atoi(argv[1]);
		massage = argv[2];

		while (*massage)
		{
			send_bit(*massage, server_pid);
			massage++;
		}
		send_bit('\0', server_pid);
	}
}
