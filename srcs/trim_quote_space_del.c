/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quote_in_command.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: flee <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/31 11:16:10 by flee              #+#    #+#             */
/*   Updated: 2021/12/31 11:16:12 by flee             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char    **trim_quote_space_del(char **third_array)
{
    char    **final_array;
    char    **cmd_without_quote;

    cmd_without_quote = del_quote_command(third_array);
    ft_free_array(cmd_without_quote));
	if (!cmd_without_quote)
	    return (NULL);
    final_array = ta_fonction(boum);
    return (final_array);
}
