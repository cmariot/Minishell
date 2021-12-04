/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_readline.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/24 14:18:47 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/04 09:25:30 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*readline_outpout(ssize_t read_return, char **str_input)
{
	int		len;
	char	*tmp;
	char	*str_return;

	if (read_return == 0 && **str_input == '\0')
	{
		ft_strdel(str_input);
		return (NULL);
	}
	len = 0;
	while ((*str_input)[len] != '\n' && (*str_input)[len] != '\0')
		len++;
	if ((*str_input)[len] == '\n')
	{
		str_return = ft_substr(*str_input, 0, len);
		tmp = ft_strdup(&(*str_input)[len + 2]);
		ft_strdel(str_input);
		*str_input = tmp;
		return (str_return);
	}
	str_return = ft_substr(*str_input, 0, len);
	ft_strdel(str_input);
	return (str_return);
}

char	*ft_readline(char *prompt)
{
	static char	*str;
	char		buf[BUFFER_SIZE + 1];
	ssize_t		read_return;

	if (BUFFER_SIZE <= 0)
		return (NULL);
	ft_putstr(prompt);
	ft_putstr(": ");
	read_return = 1;
	while (read_return)
	{
		read_return = read(1, buf, BUFFER_SIZE);
		if (read_return == -1)
			return (NULL);
		buf[read_return] = '\0';
		if (str == NULL)
			str = ft_strdup(buf);
		else if (str != NULL)
			ft_add_buf_to_str(&str, buf);
		if (ft_strchr(str, '\n'))
			break ;
	}
	return (readline_outpout(read_return, &str));
}
