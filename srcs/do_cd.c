/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 13:48:19 by flee              #+#    #+#             */
/*   Updated: 2021/12/29 13:48:20 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void    do_cd(t_shell *minishell)
{
    char        *path;
    int         ret;
    size_t      size = 99;
    char        buf[99];
    char        *cwd;
    char        *home;

    path = "~/Minishell";
    home = get_env_value("HOME", minishell->env);
    printf("home = %s\n", home);
    ret = chdir(path);
    cwd = getcwd(buf, size);
    printf("cwd = %s\n", cwd);
    if (ret == 0)
        printf("done\n");
    else
        printf("fuck\n");
}
