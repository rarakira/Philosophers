/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:34 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/06 17:21:33 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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

int	still_alife(t_philo *philo)
{
	if (current_time(philo->info) < philo->time_of_death)
		return (1);
	return (0);
}
