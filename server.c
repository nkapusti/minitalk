/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akapusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:49:52 by akapusti          #+#    #+#             */
/*   Updated: 2023/04/07 13:36:07 by akapusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler(int signum, siginfo_t *info, void *context)
{
	static int	bytes;
	static int	client_pid;
	static char	c;

	(void)context;
	client_pid = info->si_pid;
	if (signum == SIGUSR1)
	{
		c |= (0x01 << bytes);
		bytes++;
	}
	else if (signum == SIGUSR2)
		bytes++;
	if (bytes == 8)
	{
		if (c == 0)
			kill(client_pid, SIGUSR2);
		else
			write(1, &c, 1);
		c = 0;
		bytes = 0;
	}
	kill(client_pid, SIGUSR1);
}

int	main(void)
{
	struct sigaction	sa;
	int					pid;

	pid = getpid();
	ft_printf("Server PID: %d\n", pid);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	sigemptyset(&sa.sa_mask);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0);
}
