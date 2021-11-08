/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/18 16:16:51 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/05 14:10:30 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>

static int	isspace(int ch)
{
	if (ch == ' ' || ch == '\f' || ch == '\n')
		return (1);
	if (ch == '\r' || ch == '\t' || ch == '\v')
		return (1);
	return (0);
}

/* Function converts the initial portion of the string pointed to by 'str'
to int representation. */
int	ft_atoi(const char *str)
{
	int	i;
	int	sign;
	int	result;

	i = 0;
	result = 0;
	sign = 1;
	while ((isspace(str[i])) && str[i] != '\0')
	{
		if (isspace(str[i]))
			i++;
	}
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			sign = -1;
		i++;
	}
	while ((str[i] >= '0' && str[i] <= '9') && str[i] != '\0')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	printf("result = %d\n", result);
	return (result * sign);
}

int	main(void)
{
	printf("%d\n",ft_atoi("2147483647"));
	printf("%d\n",atoi("2147483647"));
	printf("%d\n",ft_atoi("-2147483648"));
	printf("%d\n",atoi("-2147483648"));
	printf("%d\n",ft_atoi("2147483648"));
	printf("%d\n",atoi("2147483648"));
}
