/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_activities.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:40:41 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/17 21:28:55 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	philo_thinks(t_philo *philo, unsigned long long	time_left)
{
	pthread_mutex_unlock(&philo->mx);
	if (time_left < (unsigned long long)philo->info->time_to_eat) // think better of the numbers
		time_left = 0;
	pthread_mutex_lock(&philo->info->print_mx);
	printf("%s%llu %d %s", VIOLT, current_time(philo->info), philo->name, THINKING);
	pthread_mutex_unlock(&philo->info->print_mx);
	usleep(time_left * 250);
	if (!feast_lasts(philo->info))
		return (0);
	return (1);
}

int	philo_sleeps(t_philo *philo)
{
	if (!feast_lasts(philo->info))
		return (0);
	pthread_mutex_lock(&philo->info->print_mx);
	printf("%s%lld %d %s", BLUE, current_time(philo->info), philo->name, SLEEPING);
	pthread_mutex_unlock(&philo->info->print_mx);
	if (current_time(philo->info) + philo->info->time_to_sleep >= philo->time_of_death)
	{
		usleep((philo->time_of_death - current_time(philo->info)) * 1000);
		return (set_philo_dead(philo));
	}
	usleep(philo->info->time_to_sleep * 1000);
	return (1);
}

int	done_eating(t_philo *philo)
{
	if (philo->times_ate == philo->info->n_must_eat)
	{
		pthread_mutex_lock(&philo->info->monitor_mx);
		philo->info->phils_done++;
		pthread_mutex_unlock(&philo->info->monitor_mx);
		//printf("%lld Philo %d has finished eating\n", current_time(philo->info), philo->name); // delete later
		return (1);
	}
	return (0);
}
