/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 13:08:10 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/12 11:56:52 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_bzero() writes n zeroed bytes to the string s. */

void	ft_bzero(void *str, size_t bytes_nb)
{
	char	*dest;
	size_t	i;

	dest = (char *)str;
	i = 0;
	while (i < bytes_nb)
	{
		dest[i] = 0;
		i++;
	}
}
