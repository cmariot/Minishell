/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_without_bn.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/12 14:35:22 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/29 13:20:20 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*gnl_without_bn(int fd)
{
	char	*line;

	line = get_next_line(fd);
	line[ft_strlen(line) - 1] = '\0';
	return (line);
}

