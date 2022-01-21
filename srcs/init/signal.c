/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 09:25:58 by flee              #+#    #+#             */
/*   Updated: 2022/01/21 18:02:50 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//ctrl-C normal
void	ft_handler(int sig, siginfo_t *info, void *secret)
{
	char	*prompt;

	(void)info;
	(void)secret;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		prompt = get_prompt();
		if (!prompt)
			exit(1);
		ft_putstr(prompt);
		rl_replace_line("", 0);
	}
}

//ctrl-C cat
void	ft_handler2(int sig, siginfo_t *info, void *secret)
{
	(void)info;
	(void)secret;
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
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
