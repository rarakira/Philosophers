/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:34 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/19 15:20:55 by lbaela           ###   ########.fr       */
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
	pthread_mutex_lock(&philo->mx);
	if (current_time(philo->info) < philo->time_of_death)
	{
		pthread_mutex_unlock(&philo->mx);
		return (1);
	}
	pthread_mutex_unlock(&philo->mx);
	return (0);
}

int	set_philo_dead(t_philo *philo)
{
	if (still_alife(philo) || !feast_lasts(philo->info))
		return (0);
	end_feast(philo->info);
	pthread_mutex_lock(&philo->mx);
	philo->is_dead = 1;
	pthread_mutex_unlock(&philo->mx);
	// printf("from philo:\n");
	printer(philo, philo->time_of_death, CDEATH, LEN_DEATH); // remove later:
	// printf("%sCurrent time: %llu %d \n", RED, current_time(philo->info), philo->name);
	// printf("Last eat: %llu, time to eat: %d, time to sleep: %d, time to die: %d\n", philo->last_ate, philo->info->time_to_eat, philo->info->time_to_sleep, philo->info->time_to_die);
	return (0);
}
