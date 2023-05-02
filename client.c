/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akapusti <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/05 15:08:09 by akapusti          #+#    #+#             */
/*   Updated: 2023/04/05 15:46:53 by akapusti         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	n;
	int	m;

	i = 0;
	n = 0;
	m = 1;
	while ((str[i] == 32) || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			m *= -1;
		i++;
	}
	while (str[i] != '\0' && (str[i] >= 48 && str[i] <= 57))
	{
		n *= 10;
		n += str[i] - '0';
		i++;
	}
	return (n * m);
}

void	send_signal(int pid, char c)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if (c & (0x01 << bit))
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(666);
		bit++;
	}
}

//for bonus part
void	message(int signum)
{
	if (signum == SIGUSR1)
		signal(SIGUSR1, message);
	else if (signum == SIGUSR2)
	{
		ft_printf("Message reseived\n");
		exit(0);
	}
}

int	main(int argc, char **argv)
{
	int	i;
	int	server_pid;

	if (argc != 3)
	{
		write(1, "Error!\n", 7);
		return (0);
	}
	argc++;
	i = 0;
	server_pid = ft_atoi(argv[1]);
	signal(SIGUSR1, message);
	signal(SIGUSR2, message);
	while (argv[2][i] != '\0')
	{
		send_signal(server_pid, argv[2][i]);
		i++;
	}
	send_signal(server_pid, 0);
}
