/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handler.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 09:25:58 by flee              #+#    #+#             */
/*   Updated: 2021/12/29 09:26:00 by flee             ###   ########.fr       */
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
        write(0, "Minishell ➤  ",14);
    }
}