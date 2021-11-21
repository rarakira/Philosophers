/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:34 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/21 12:43:26 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	current_time(t_info *info)
{
	unsigned long long	res;
	struct timeval		current;

	gettimeofday(&current, NULL);
	res = (current.tv_sec - info->era_start.tv_sec) * 1000;
	res += (current.tv_usec - info->era_start.tv_usec) / 1000;
	return (res);
}

void	ft_sleep(unsigned long long wake_time, t_info *info)
{
	unsigned long long	current;

	current = current_time(info);
	while (current < wake_time)
	{
		usleep(100);
		current = current_time(info);
	}
}

void	end_feast(t_info *info)
{
	pthread_mutex_lock(&info->monitor_mx);
	info->feast_ended = 1;
	pthread_mutex_unlock(&info->monitor_mx);
}

int	feast_lasts(t_info *info)
{
	pthread_mutex_lock(&info->monitor_mx);
	if (info->feast_ended)
	{
		pthread_mutex_unlock(&info->monitor_mx);
		return (0);
	}
	pthread_mutex_unlock(&info->monitor_mx);
	return (1);
}

int	still_alife(t_philo *philo)
{
	if (current_time(philo->info) < philo->time_of_death)
		return (1);
	return (0);
}
