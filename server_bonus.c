/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cvu <marvin@42.fr>                         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/29 21:12:53 by cvu               #+#    #+#             */
/*   Updated: 2023/05/29 21:13:14 by cvu              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include "libft/libft.h"
#include <stdio.h>
#include "ft_printf.h"

/*void	ft_handler(int signal, siginfo_t *info, void *s)
{
	static int	bit;
	static int	i;

	(void)info;
	(void)s;
	if (signal == SIGUSR1)
		i |= (0x01 << bit);
	bit++;
	if (bit == 8)
	{
		ft_printf("%c", i);
		bit = 0;
		i = 0;
		kill(info->si_pid, SIGUSR2);
	}
}

int	main(int argc, char **argv)
{
	int					pid;
	struct sigaction	sig;

	(void)argv;
	if (argc != 1)
	{
		ft_printf("\033[91mError: wrong format.\033[0m\n");
		ft_printf("\033[33mTry: ./server\033[0m\n");
		return (0);
	}
	pid = getpid();
	ft_printf("\033[94mPID\033[0m \033[96m->\033[0m %d\n", pid);
	ft_printf("\033[90mWaiting for a message...\033[0m\n");
	sig.sa_sigaction = ft_handler;
	sigemptyset(&sig.sa_mask);
	sig.sa_flags = 0;
	while (argc == 1)
	{
		sigaction(SIGUSR1, &sig, NULL);
		sigaction(SIGUSR2, &sig, NULL);
		pause();
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

void	ft_signal_handler(int sig, siginfo_t *info, void *context)
{
	static unsigned char	val = 0;
	static int				bit = 1;
	static int				id = 0;

	if (info->si_pid != 0)
		id = info->si_pid;
	(void)context ;
	if (sig == SIGUSR1)
		val += 0;
	if (sig == SIGUSR2)
		val += bit;
	bit *= 2;
	if (bit == 256)
	{
		bit = 1;
		if (val == 0)
			if (kill(id, SIGUSR2) == -1)
				ft_error_handler(0);
		if (val != 0)
			write(1, &val, 1);
		val = 0;
	}
	if (kill(id, SIGUSR1) == -1)
		ft_error_handler(0);
}

int	main(void)
{
	pid_t				pid;
	struct sigaction	action;

	action.sa_flags = SA_SIGINFO;
	action.sa_sigaction = ft_signal_handler;
	pid = getpid();
	if (sigaction(SIGUSR1, &action, NULL) == -1
		|| sigaction(SIGUSR2, &action, NULL) == -1)
	{
		ft_error_handler(1);
		return (1);
	}
	write(1, "PID = ", 6);
	ft_putstr(ft_itoa(pid));
	write(1, "\n", 1);
	while (1)
		pause();
	return (0);
}
