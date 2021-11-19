/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:40:41 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/19 15:19:50 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_thinks(t_philo *philo)
{
	if (!printer(philo, current_time(philo->info), CTHINKING, LEN_THINKING))
		return (0);
	usleep(50);
	return (1);
}

int	philo_sleeps(t_philo *philo)
{
	unsigned long long	started_sleeping;

	started_sleeping = current_time(philo->info);
	if (!printer(philo, started_sleeping, CSLEEPING, LEN_SLEEPING))
		return (0);
	if (started_sleeping + philo->info->time_to_sleep >= philo->time_of_death)
	{
		usleep((philo->time_of_death - current_time(philo->info)) * 1000);
		return (set_philo_dead(philo));
	}
	usleep((philo->info->time_to_sleep - (current_time(philo->info) - started_sleeping)) * 1000);
	return (1);
}

int	done_eating(t_philo *philo)
{
	if (philo->times_ate == philo->info->n_must_eat)
	{
		pthread_mutex_lock(&philo->info->monitor_mx);
		philo->info->phils_done++;
		pthread_mutex_unlock(&philo->info->monitor_mx);
		// printf("%lld Philo %d has finished eating\n", current_time(philo->info), philo->name); // delete later
		return (1);
	}
	return (0);
}
