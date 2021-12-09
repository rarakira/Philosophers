/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:40:41 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/09 16:47:55 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_thinks(t_philo *philo)
{
	unsigned long long	since_last_meal;

	printer(philo, current_time(philo->info), THINKING, VIOLT);
	since_last_meal = (current_time(philo->info) - philo->last_ate);
	if (since_last_meal < philo->info->time_to_die / 3 * 2)
		ft_sleep(philo->time_of_death - philo->info->time_to_die / 3,
			philo->info);
	return (1);
}

int	philo_sleeps(t_philo *philo)
{
	unsigned long long	started_sleeping;

	started_sleeping = current_time(philo->info);
	printer(philo, started_sleeping, SLEEPING, BLUE);
	if (started_sleeping + philo->info->time_to_sleep >= philo->time_of_death)
	{
		ft_sleep(philo->time_of_death, philo->info);
		return (set_philo_dead(philo));
	}
	ft_sleep(started_sleeping + philo->info->time_to_sleep, philo->info);
	return (1);
}

int	done_eating(t_philo *philo)
{
	if (philo->times_ate == philo->info->n_must_eat)
		return (1);
	return (0);
}
