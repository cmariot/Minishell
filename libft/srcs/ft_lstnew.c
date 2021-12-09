/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstnew.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/05/20 14:11:04 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/09 09:54:49 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/* ft_lstnew create a new chained list,
 * the content is put in the content variable
 * and the next value is set to NULL */

t_list	*ft_lstnew(void *content)
{
	t_list	*tmp;

	tmp = malloc(sizeof(t_list));
	if (tmp)
	{
		tmp->content = content;
		tmp->next = NULL;
		return (tmp);
	}
	else
		return (NULL);
}
