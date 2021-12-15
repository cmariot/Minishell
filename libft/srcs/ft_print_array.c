/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_print_array.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/15 16:10:31 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/15 16:12:06 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

// Print the array of char * like this :
// name[i] = array[i]

void	ft_print_array(char *name, char **array)
{
	int	i;

	i = 0;
	while (array[i])
	{
		printf("%s[%d] = [%s]\n", name, i, array[i]);
		i++;
	}
}
