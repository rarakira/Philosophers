/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_msgs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:17:05 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/10 14:07:15 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	print_death(t_philo *philo, unsigned long long time, char *msg, char *col)
{
	static int	print;

	print++;
	if (print > 1)
		return (0);
	pthread_mutex_lock(&philo->info->print_mx);
	printf("%s%llu %d %s", col, time, philo->name, msg);
	pthread_mutex_unlock(&philo->info->print_mx);
	return (1);
}

int	printer(t_philo *philo, unsigned long long time, char *msg, char *col)
{
	pthread_mutex_lock(&philo->info->print_mx);
	if (!feast_lasts(philo->info))
	{
		pthread_mutex_unlock(&philo->info->print_mx);
		return (0);
	}
	printf("%s%llu %d %s", col, time, philo->name, msg);
	pthread_mutex_unlock(&philo->info->print_mx);
	return (1);
}
