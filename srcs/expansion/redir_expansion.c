/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_expansion.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/28 10:46:28 by cmariot           #+#    #+#             */
/*   Updated: 2022/01/28 17:58:11 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*filename_expand(char *filename, t_env *env)
{
	char	*final;
	char	**array;

	final = ft_strdup(filename);
	if (!final)
		return (NULL);
	search_dollar_in_str(&final, env);
	str_quotes_removal(&final);
	str_tilde_expansion(&final, env);
	array = ft_split(final, ' ');
	if (!array || array[1] != NULL || array[0][0] == '$')
	{
		ft_free_array(array);
		free(final);
		print(2, "minishell: %s: ambiguous redirect\n", filename);
		global_exit_status(1);
		return (NULL);
	}
	ft_free_array(array);
	return (final);
}

int	filename_expansion(t_redir *redir, char **array,
		int array_index, t_env *env)
{
	redir->filename = filename_expand(array[array_index + 1], env);
	if (redir->filename == NULL)
		return (1);
	return (0);
}
