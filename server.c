/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akapusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:49:52 by akapusti          #+#    #+#             */
/*   Updated: 2023/04/05 15:52:12 by akapusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*#include "minitalk.h"

static void	print_char(int sig)
{
	static char	c = 0x00;
	static int	i = 0;

	if (sig == SIGUSR1)
		c |= (0x01 << i);
	i++;
	if (i == 8)
	{
		if (c == '\0')
			ft_printf("\n");
		else
			ft_printf("%c", c);
		i = 0;
		c = 0x00;
	}
}

int	main(void)
{
	ft_printf("Server PID: %d\n", getpid());
	signal(SIGUSR1, print_char);
	signal(SIGUSR2, print_char);
	while (1)
		pause();
	return (0);
}*/

#include "minitalk.h"
#include <stdio.h>
#include <stdlib.h>

void	ft_putnbr_fd(int n, int fd)
{
	char	num;

	if (n == -2147483648)
	{
		write(fd, "-", 1);
		write(fd, "2", 1);
		n = 147483648;
	}
	if (n < 0)
	{
		write(fd, "-", 1);
		n *= -1;
	}
	if (n >= 10)
	{
		ft_putnbr_fd(n / 10, fd);
		ft_putnbr_fd(n % 10, fd);
	}
	else
	{
		num = n + '0';
		write(fd, &num, 1);
	}
}

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

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	int					pid1;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler;
	(void)argv;
	(void)argc;
	pid1 = getpid();
	sigemptyset(&sa.sa_mask);
	ft_putnbr_fd(pid1, 1);
	write(1, "\n", 1);
	while (1)
	{
		sigaction(SIGUSR1, &sa, NULL);
		sigaction(SIGUSR2, &sa, NULL);
		pause();
	}
	return (0);
}
