/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 09:25:58 by flee              #+#    #+#             */
/*   Updated: 2022/01/15 13:36:33 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig, siginfo_t *info, void *secret)
{
	(void)info;
	(void)secret;
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	ft_handler2(int sig, siginfo_t *info, void *secret)
{
	(void)info;
	(void)secret;
	if (sig == SIGINT)
	{
		write(0, "\n", 1);
		rl_replace_line("", 0);
	}
}

//status = 0 catch all signal
//status = 1 dont catch sig_int (ctrl-c)

int	signal_catcher(int status)
{
	struct sigaction	new_act;
	struct sigaction	act;
	int					sig;

	new_act.sa_sigaction = ft_handler;
	sigemptyset(&new_act.sa_mask);
	sigemptyset(&act.sa_mask);
	new_act.sa_flags = 0;
	if (status == 0)
		new_act.sa_sigaction = ft_handler;
	else if (status == 1)
		new_act.sa_sigaction = ft_handler2;
	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sig = sigaction(SIGQUIT, &act, NULL);
	sig = sigaction(SIGINT, &new_act, NULL);
	if (sig == -1)
		return (0);
	return (1);
}
