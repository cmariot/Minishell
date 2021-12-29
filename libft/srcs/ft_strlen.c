/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/10 13:37:43 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/29 13:12:44 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_strlen() returns the len of a string */

size_t	ft_strlen(const char *str)
{
	const char	*s;

	s = str;
	while (*(++s))
		;
	return (s - str);
}
