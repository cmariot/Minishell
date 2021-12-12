/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/11 14:08:16 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/12 12:09:21 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *src)
{
	char	*new;
	int		src_len;
	int		i;

	src_len = ft_strlen(src);
	new = ft_calloc(src_len + 1, sizeof(char));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < src_len)
	{
		new[i] = src[i];
		i++;
	}
	return (new);
}
