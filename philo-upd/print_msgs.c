/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:17:05 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/19 15:25:16 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static void	ft_translate_nums(char *num, unsigned long long n, size_t len)
{
	if (n == 0)
		num[--len] = '0';
	while (n)
	{
		num[--len] = (n % 10) + '0';
		n = (n - (n % 10)) / 10;
	}
}

size_t	ft_itoa_mem(char *str, unsigned long long n)
{
	size_t					len;
	unsigned long long		mod;

	mod = 10;
	len = 1;
	while (n % mod != n)
	{
		mod *= 10;
		len++;
	}
	ft_translate_nums(str, n, len);
	return (len);
}

/* The function copies 'n' bytes from memory area 'src' to memory area 'dst'. */
size_t	ft_memcpy(void *dst, const void *src, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		((unsigned char *)dst)[i] = ((unsigned char *)src)[i];
		i++;
	}
	return (i);
}

size_t	insert_msg(char *str, char msg)
{
	size_t	i;

	i = 0;
	if (msg == 'f')
		i += ft_memcpy(str, CFORK, LEN_FORK);
	else if (msg == 'e')
		i += ft_memcpy(str, CEATING, LEN_EATING);
	else if (msg == 's')
		i += ft_memcpy(str, CSLEEPING, LEN_SLEEPING);
	else if (msg == 't')
		i += ft_memcpy(str, CTHINKING, LEN_THINKING);
	else if (msg == 'd')
		i += ft_memcpy(str, CDEATH, LEN_DEATH);
	return (i);
}

int	printer(t_philo *philo, unsigned long long time, char *msg, int len)
{
	char	message[BUFFSIZE];
	size_t	i;

	i = 0;
	if (!feast_lasts(philo->info) && still_alife(philo))
		return (0);
	// if (msg == 'd')
	// 	end_feast(philo->info);
	memset(message, ' ', BUFFSIZE);
	i += (ft_itoa_mem(message, time) + 1);
	i += (ft_itoa_mem(&message[i], (unsigned long long) philo->name) + 1);
	i += ft_memcpy(&message[i], msg, len);
	message[i] = 0;
	pthread_mutex_lock(&philo->info->print_mx);
	write(1, message, ft_strlen(message));
	pthread_mutex_unlock(&philo->info->print_mx);
	return (1);
}

/*
size_t	insert_color(char *str, char msg)
{
	size_t	i;

	i = 0;
	if (msg == 'f')
		i += ft_memcpy(str, GREEN, ft_strlen(GREEN));
	else if (msg == 'e')
		i += ft_memcpy(str, YELL, ft_strlen(YELL));
	else if (msg == 's')
		i += ft_memcpy(str, BLUE, ft_strlen(BLUE));
	else if (msg == 't')
		i += ft_memcpy(str, VIOLT, ft_strlen(VIOLT));
	else if (msg == 'd')
		i += ft_memcpy(str, RED, ft_strlen(RED));
	return (i);
}

size_t	insert_msg(char *str, char msg)
{
	size_t	i;

	i = 0;
	if (msg == 'f')
		i += ft_memcpy(str, FORK, ft_strlen(FORK));
	else if (msg == 'e')
		i += ft_memcpy(str, EATING, ft_strlen(EATING));
	else if (msg == 's')
		i += ft_memcpy(str, SLEEPING, ft_strlen(SLEEPING));
	else if (msg == 't')
		i += ft_memcpy(str, THINKING, ft_strlen(THINKING));
	else if (msg == 'd')
		i += ft_memcpy(str, DEATH, ft_strlen(DEATH));
	return (i);
}

int	printer(t_philo *philo, unsigned long long time, char msg)
{
	char	message[BUFFSIZE];
	size_t	i;

	i = 0;
	if (!feast_lasts(philo->info))
		return (0);
	if (msg == 'd')
		end_feast(philo->info);
	memset(message, ' ', BUFFSIZE);
	i += insert_color(message, msg);
	i += (ft_itoa_mem(&message[i], time) + 1);
	i += (ft_itoa_mem(&message[i], (unsigned long long) philo->name) + 1);
	i += insert_msg(&message[i], msg);
	message[i] = 0;
	pthread_mutex_lock(&philo->info->print_mx);
	write(1, message, ft_strlen(message));
	pthread_mutex_unlock(&philo->info->print_mx);
	return (1);
}
*/
