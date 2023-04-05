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

#include "minitalk.h"

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
}
