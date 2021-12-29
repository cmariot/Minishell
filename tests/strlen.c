/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   strlen.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 01:03:42 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/29 01:18:15 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>

size_t	ft_strlen(const char *str)
{
	const char *s;

	s = str;
	while (*(++s));
	return(s - str);
}

int	main(int argc, char **argv, char **env)
{
	if (argc && *argv && *env)
	{
		printf("%lu\n", ft_strlen("TEST"));
	}
	return (0);
}
