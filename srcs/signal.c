/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 09:25:58 by flee              #+#    #+#             */
/*   Updated: 2021/12/30 15:21:21 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handler(int sig, siginfo_t *info, void *secret)
{
    (void)info;
    (void)secret;
    if (sig == SIGINT)
    {
        size_t size;
        char buf[99];
        char *cwd;
        int len;
        size_t i;
    
        i = 0; 
        size = 99;
        cwd = getcwd(buf, size);
        len = ft_strlen(cwd) - 1;
        while (cwd[len] != '/' && len > -1)
        {
            len--;
            i++;
        }
        cwd = ft_substr(cwd, ++len, --i);
        write(0, "\n", 1);
        ft_putstr_fd(cwd, 0);
        write(0, " ➤ ", 6);
        free(cwd);
    }
}

int     signal_catcher(void)
{
    struct sigaction	new_act;
	struct sigaction	act;
	int					sig;

	new_act.sa_sigaction = ft_handler;
    sigemptyset(&new_act.sa_mask);
    sigemptyset(&act.sa_mask);
	new_act.sa_flags = 0;
	act.sa_flags = 0;
	act.sa_handler = SIG_IGN;
	sig = sigaction(SIGQUIT, &act, NULL);
	sig = sigaction(SIGINT, &new_act, NULL);
	if (sig == -1)
		return (0);
    return (1);
}
