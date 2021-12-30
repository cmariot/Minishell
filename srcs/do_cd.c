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

char    *new_path(t_shell *minishell, char *path)
{
    char    *home;
    char    *new_path;
    size_t  size;

    size = ft_strlen(path) - 1;
    home = get_env_value("HOME", minishell->env);
    path = ft_substr((const char *)path, 1, size);
    new_path = ft_strjoin(home, path);
    free(path);
    return (new_path);
}

void    do_cd(t_shell *minishell)
{
    char        *path;
    int         ret;
    size_t      size = 99;
    char        buf[99];
    char        *cwd;

    printf("enter do_cd\n");
    if (minishell->command_line.number_of_simple_commands != 2)
        printf("ERROR\n");
    path = minishell->command_line.command->command_and_args[1];
    printf("path = %s\n",path);
    if (path[0] == '~')
        path = new_path(minishell, path);
    ret = chdir(path);
    cwd = getcwd(buf, size);
    printf("cwd = %s\n", cwd);
    if (ret == 0)
        printf("done\n");
    else
        printf("fuck\n");   
}
