/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 09:25:58 by flee              #+#    #+#             */
/*   Updated: 2022/02/06 13:24:03 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	interactive_handler(int signal)
{
	char	*prompt;

	if (signal == SIGINT)
	{
		print(1, "\b\b  \b\b");
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
		global_exit_status(signal + 128);
		return ;
	}
	else if (signal == SIGQUIT)
	{
		ft_putstr_fd("Quit: 3\n", 0);
		global_exit_status(signal + 128);
		return ;
	}
}

void	heredoc_handler(int signal)
{
	if (signal == SIGINT)
		global_exit_status(signal + 128);
	else if (signal == SIGQUIT)
		return ;
}

/* 
 * 3 comportements :
 *	- Interactive (prompt)
 *		ctrl-\ : do nothing
 *		ctrl-D : eof -> if line == NULL : quit
 *		ctrl-C : show a new line with a new prompt
 *	- Blocking command (cat)
 *		ctrl-\ : quit crash
 *		ctrl-D : eof -> end of cat
 *		ctrl-C : quit 
 *	- Heredoc (<< eof)
 *		ctrl-\ : do nothing
 *		ctrl-D : eof -> line == NULL 
 *		ctrl-C : quit heredoc with '\n'
 */

#define INTERACTIVE 0
#define COMMAND 1
#define HEREDOC 2

int	catch_signal(int comportement)
{
	struct sigaction	ctrl_c_primitive;
	struct sigaction	ctrl_slash_primitive;

	ft_memset(&ctrl_c_primitive, 0, sizeof(ctrl_c_primitive));
	ft_memset(&ctrl_slash_primitive, 0, sizeof(ctrl_slash_primitive));
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
