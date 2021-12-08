/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_buff_msgs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:17:05 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/07 19:26:23 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_death(t_philo *philo, unsigned long long time, char *msg, int len)
{
	(void)len;
	sem_wait(philo->info->print);
	printf("%llu %d %s", time, philo->name, msg);
	return (1);
}

static inline size_t	ft_itoa_mem(char *str, register unsigned long long n)
{
	register size_t					len;
	register unsigned long long		mod;
	register size_t					i;

	mod = 10;
	len = 1;
	while (n % mod != n)
	{
		mod *= 10;
		len++;
	}
	i = 0;
	while (mod != 1)
	{
		mod /= 10;
		str[i++] = (n / mod) + '0';
		n = n % mod;
	}
	return (len);
}

static inline size_t	ft_memcpy(void *dst, const void *src, size_t n)
{
	register size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (i);
}

int	printer(t_philo *philo, unsigned long long time, char *msg, int len)
{
	char	message[BUFFSIZE];
	size_t	i;

	i = 0;
	memset(message, ' ', BUFFSIZE);
	i += (ft_itoa_mem(message, time) + 1);
	i += (ft_itoa_mem(&message[i], (unsigned long long) philo->name) + 1);
	i += ft_memcpy(&message[i], msg, len);
	message[i] = 0;
	sem_wait(philo->info->print);
	write(1, message, i);
	sem_post(philo->info->print);
	return (1);
}
