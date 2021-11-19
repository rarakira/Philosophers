/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:03:48 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/19 15:23:41 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_left_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->left_f->mx);
		if (philo->left_f->is_avail)
		{
			philo->left_f->is_avail = 0;
			pthread_mutex_unlock(&philo->left_f->mx);
			if (!printer(philo, current_time(philo->info), CFORK, LEN_FORK))
				return (0);
			return (1);
		}
		pthread_mutex_unlock(&philo->left_f->mx);
		if (!still_alife(philo))
			return (set_philo_dead(philo));
	}
	return (0);
}

int	get_right_fork(t_philo *philo)
{
	while (1)
	{
		if (!still_alife(philo))
			return (set_philo_dead(philo));
		pthread_mutex_lock(&philo->right_f->mx);
		if (philo->right_f->is_avail)
		{
			philo->right_f->is_avail = 0;
			pthread_mutex_lock(&philo->mx);
			philo->last_ate = current_time(philo->info);
			philo->time_of_death = philo->last_ate + philo->info->time_to_die;
			philo->times_ate++;
			pthread_mutex_unlock(&philo->mx);
			pthread_mutex_unlock(&philo->right_f->mx);
			return (1);
		}
		pthread_mutex_unlock(&philo->right_f->mx);
	}
	return (0);
}

static int	return_forks(t_philo *philo)
{
	// if (!feast_lasts(philo->info))
	// 	return (0);
	// printf("%d forks returned: %llu (enter)\n", philo->name, current_time(philo->info)); // remove
	pthread_mutex_lock(&philo->right_f->mx);
	philo->right_f->is_avail = 1;
	pthread_mutex_unlock(&philo->right_f->mx);
	pthread_mutex_lock(&philo->left_f->mx);
	philo->left_f->is_avail = 1;
	pthread_mutex_unlock(&philo->left_f->mx);
	// printf("%d forks returned: %llu\n", philo->name, current_time(philo->info)); // remove
	return (1);
}

int	philo_eats(t_philo *philo)
{
	if (!get_left_fork(philo) || &philo->left_f == &philo->right_f || !get_right_fork(philo))
		return (set_philo_dead(philo));
	if (!printer(philo, philo->last_ate, CFORK, LEN_FORK))
		return (0);
	if (!printer(philo, philo->last_ate, CEATING, LEN_EATING))
		return (0);
	// printf("%d before usleep: %llu\n", philo->name, current_time(philo->info));
	usleep((philo->info->time_to_eat - (current_time(philo->info) - philo->last_ate)) * 1000);
	// printf("%d after usleep: %llu\n", philo->name, current_time(philo->info));
	return (return_forks(philo));
}
