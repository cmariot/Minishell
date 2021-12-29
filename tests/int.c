/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cmariot <cmariot@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/29 00:40:21 by cmariot           #+#    #+#             */
/*   Updated: 2021/12/29 16:15:37 by cmariot          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <limits.h>

int	main(int argc, char **argv, char **env)
{
	if (argc && *argv && *env)
	{
		printf("\n");
		printf("The number of bits in a byte %d\n", CHAR_BIT);
		printf("\n");
		printf("MIN CHAR = %d\n", CHAR_MIN);
		printf("MAX CHAR = %d\n", CHAR_MAX);
		printf("MAX UNSIGNED CHAR = %d\n", UCHAR_MAX);
		printf("\n");
		printf("MIN SHORT INT = %d\n", SHRT_MIN);
		printf("MAX SHORT INT = %d\n", SHRT_MAX); 
		printf("\n");
		printf("MIN INT = %d\n", INT_MIN);
		printf("MAX INT = %d\n", INT_MAX);
		printf("MAX UNSIGNED INT = %u\n", UINT_MAX);
		printf("\n");
		printf("MIN LONG = %ld\n", LONG_MIN);
		printf("MAX LONG = %ld\n", LONG_MAX);
		printf("MAX UNSIGNED LONG = %lu\n", ULONG_MAX);
		printf("\n");
	}
	return (0);
}
