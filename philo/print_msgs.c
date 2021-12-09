/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_msgs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:17:05 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/09 18:07:34 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	ft_putnbr_fd(unsigned long long	n)
{
	unsigned long long	len;
	unsigned long long	mod;
	char				ch;

	mod = 10;
	len = 1;
	while (n % mod != n)
	{
		mod *= 10;
		len++;
	}
	while (mod >= 10)
	{
		mod /= 10;
		ch = (n / mod) + '0';
		n = n % mod;
		write(1, &ch, 1);
	}
}

int	printer(t_philo *philo, unsigned long long time, char *msg, int len)
{
	pthread_mutex_lock(&philo->info->print_mx);
	if (!feast_lasts(philo->info))
	{
		pthread_mutex_unlock(&philo->info->print_mx);
		return (0);
	}
	ft_putnbr_fd(time);
	write(1, " ", 1);
	ft_putnbr_fd((unsigned long long) philo->name);
	write(1, " ", 1);
	write(1, msg, len);
	pthread_mutex_unlock(&philo->info->print_mx);
	return (1);
}

int	print_death(t_philo *philo, unsigned long long time, char *msg, int len)
{
	static int	print;

	print++;
	if (print > 1)
		return (0);
	(void)len;
	pthread_mutex_lock(&philo->info->print_mx);
	printf("%llu %d %s", time, philo->name, msg);
	pthread_mutex_unlock(&philo->info->print_mx);
	return (1);
}
