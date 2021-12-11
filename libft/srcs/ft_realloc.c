/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/09 22:23:23 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/09 22:55:49 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_realloc(void *previous, char *new)
{
	char	*str;

	str = NULL;
	if (previous != NULL && new != NULL)
	{
		free(previous);
		str = ft_strdup(new);
	}
	return (str);
}

/*
int	main(int argc, char **argv, char **env)
{
	char	*lol;

	if (argc && *argv && *env)
	{
		lol = ft_strdup("lol");
		printf("1 : %s\n", lol);
		lol = ft_realloc(lol, "lol2");
		printf("2 : %s\n", lol);
		free(lol);
	}
	return (0);
}
*/
