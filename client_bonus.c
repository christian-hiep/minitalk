/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:12:29 by cvu               #+#    #+#             */
/*   Updated: 2023/05/29 21:12:35 by cvu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include <stdio.h>
#include "ft_printf.h"

/*static void	ft_confirm(int signal)
{
	if (signal == SIGUSR1)
		ft_printf("\033[0;32mQSL!\033[0;32m\n", 1);
	else
		ft_printf("\033[0;32mQSL!\033[0;32m\n", 1);
}

void	ft_send_bits(int pid, char i)
{
	int	bit;

	bit = 0;
	while (bit < 8)
	{
		if ((i & (0x01 << bit)) != 0)
			kill(pid, SIGUSR1);
		else
			kill(pid, SIGUSR2);
		usleep(100);
		bit++;
	}
}

int	main(int argc, char **argv)
{
	int	pid;
	int	i;

	i = 0;
	if (argc == 3)
	{
		pid = ft_atoi(argv[1]);
		while (argv[2][i] != '\0')
		{
			signal(SIGUSR1, ft_confirm);
			signal(SIGUSR2, ft_confirm);
			ft_send_bits(pid, argv[2][i]);
			i++;
		}
		ft_send_bits(pid, '\n');
	}
	else
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("\033[33mTry: ./client_bonus [PID] [MESSAGE]\033[0m\n");
		return (1);
	}
	return (0);
}*/

void	ft_error_handler(int i)
{
	if (i == 0)
	{
		write(1, "Error KILL\n", 12);
		exit(1);
	}
	if (i == 1)
	{
		write(1, "Error SIGACTION\n", 17);
		exit(1);
	}
}

void	ft_send_terminator(int pid)
{
	static int	i = 0;

	if (i <= 8)
		if (kill(pid, SIGUSR1) == -1)
			ft_error_handler(0);
	i++;
}

void	ft_send_signal(int pid, char *str)
{
	static int	bit = 0;
	static char	*str_bis = 0;

	if (str)
		str_bis = str;
	if (*str_bis)
	{
		if ((((unsigned char)*str_bis >> bit) % 2) == 0)
			if (kill(pid, SIGUSR1) == -1)
				ft_error_handler(0);
		if ((((unsigned char)*str_bis >> bit) % 2) == 1)
			if (kill(pid, SIGUSR2) == -1)
				ft_error_handler(0);
		bit++;
		if (bit == 8)
		{
			str_bis++;
			bit = 0;
		}
	}
	if (!(*str_bis))
		ft_send_terminator(pid);
}

void	ft_receipt(int sig, siginfo_t *info, void *context)
{
	static int	id;

	if (info->si_pid != 0)
		id = info->si_pid;
	(void)context ;
	if (sig == SIGUSR1)
		ft_send_signal(id, NULL);
	if (sig == SIGUSR2)
	{
		write(1, "Server >> \"The message came through\"\n", 38);
		exit(EXIT_SUCCESS);
	}
}

int	main(int ac, char **av)
{
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = ft_receipt;
	if (sigaction(SIGUSR1, &action, NULL) == -1
		|| sigaction(SIGUSR2, &action, NULL) == -1)
		ft_error_handler(1);
	if (ac != 3)
	{
		write(1, "Utilisez le format: ./client <PID> <String>\n", 44);
		exit(EXIT_FAILURE);
	}
	ft_send_signal(ft_atoi(av[1]), av[2]);
	while (1)
		pause();
	return (0);
}
