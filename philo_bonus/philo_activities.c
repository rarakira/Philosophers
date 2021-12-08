/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:40:41 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/07 19:12:47 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	philo_thinks(t_philo *philo)
{
	unsigned long long	since_last_meal;

	printer(philo, current_time(philo->info), CTHINKING, LEN_THINKING);
	//thinking = (philo->time_of_death - current_time(philo->info));
	since_last_meal = (current_time(philo->info) - philo->last_ate);
	// printf("Time since food: %llu, life span 40%%: %u\n", current, philo->info->time_to_die / 10 * 4);
	if (since_last_meal < philo->info->time_to_die / 3 * 2)
		ft_sleep(philo->time_of_death - philo->info->time_to_die / 3, philo->info);
	return (1);
}

int	philo_sleeps(t_philo *philo)
{
	unsigned long long	started_sleeping;

	started_sleeping = current_time(philo->info);
	printer(philo, started_sleeping, CSLEEPING, LEN_SLEEPING);
	if (started_sleeping + philo->info->time_to_sleep >= philo->time_of_death)
	{
		ft_sleep(philo->time_of_death, philo->info);
		return (set_philo_dead(philo));
	}
	// usleep(philo->info->time_to_sleep * 1000);
	ft_sleep(started_sleeping + philo->info->time_to_sleep, philo->info);
	return (1);
}

int	done_eating(t_philo *philo)
{
	if (philo->times_ate == philo->info->n_must_eat)
		return (1);
	return (0);
}
