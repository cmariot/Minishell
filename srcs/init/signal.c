/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 09:25:58 by flee              #+#    #+#             */
/*   Updated: 2022/01/22 16:34:04 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interactive_handler(int signal)
{
	char	*prompt;

	if (signal == SIGINT)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		rl_on_new_line();
		prompt = get_prompt();
		if (!prompt)
			return ;
		ft_putstr(prompt);
		free(prompt);
	}
	else if (signal == SIGQUIT)
	{
		return ;
	}
}

void	command_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar('\n');
		return ;
	}
	else if (signal == SIGQUIT)
	{
		printf("Quit: %d\n", signal);
		global_exit_status(signal + 128);
		return ;
	}
}

void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
	{
		ft_putchar('\n');
		global_exit_status(signal + 128);
	}
	else if (signal == SIGQUIT)
	{
		return ;
	}
}

/* 
 * 3 comportements :
 *	- Interactive (prompt)
 *		ctrl-\ : do nothing
 *		ctrl-D : quit minishell (if empty prompt)
 *		ctrl-C : show a new line with a new prompt
 *	- Blocking command (cat)
 *		ctrl-\ : quit crash
 *		ctrl-D : quit don't crash
 *		ctrl-C : quit 
 *	- Heredoc (<< eof)
 *		ctrl-\ : do nothing
 *		ctrl-D : quit heredoc but without '\n'
 *		ctrl-C : quit heredoc with '\n'
 */

#define INTERACTIVE 0
#define COMMAND 1
#define HEREDOC 2

int	catch_signal(int comportement)
{
	struct sigaction	ctrl_c_primitive;
	struct sigaction	ctrl_slash_primitive;

	ctrl_c_primitive.sa_flags = 0;
	ctrl_slash_primitive.sa_flags = 0;
	if (comportement == INTERACTIVE)
	{
		ctrl_c_primitive.sa_handler = &interactive_handler;
		ctrl_slash_primitive.sa_handler = SIG_IGN;
	}
	else if (comportement == COMMAND)
	{
		ctrl_c_primitive.sa_handler = &command_handler;
		ctrl_slash_primitive.sa_handler = &command_handler;
	}
	else if (comportement == HEREDOC)
	{
		ctrl_c_primitive.sa_handler = &heredoc_handler;
		ctrl_slash_primitive.sa_handler = SIG_IGN;
	}
	sigaction(SIGINT, &ctrl_c_primitive, 0);
	sigaction(SIGQUIT, &ctrl_slash_primitive, 0);
	return (0);
}
