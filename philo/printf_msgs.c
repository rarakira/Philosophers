/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_msgs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:17:05 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/20 19:06:37 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

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

int	printer(t_philo *philo, unsigned long long time, char *msg, int len)
{
	(void)len;
	pthread_mutex_lock(&philo->info->print_mx);
	if (!feast_lasts(philo->info))
	{
		pthread_mutex_unlock(&philo->info->print_mx);
		return (0);
	}
	printf("%llu %d %s", time, philo->name, msg);
	pthread_mutex_unlock(&philo->info->print_mx);
	return (1);
}
