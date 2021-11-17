/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:03:48 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/17 21:03:01 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	get_left_fork(t_philo *philo)
{
	while (feast_lasts(philo->info))
	{
		if (!still_alife(philo))
			return (set_philo_dead(philo));
		pthread_mutex_lock(&philo->left_f->mx);
		if (philo->left_f->is_avail)
		{
			philo->left_f->is_avail = 0;
			pthread_mutex_unlock(&philo->left_f->mx);
			pthread_mutex_lock(&philo->info->print_mx);
			printf("%s%llu %d %s", GREEN, current_time(philo->info), philo->name, FORK);
			pthread_mutex_unlock(&philo->info->print_mx);
			return (1);
		}
		pthread_mutex_unlock(&philo->left_f->mx);
		//usleep(100);
	}
	return (0);
}

int	get_right_fork(t_philo *philo)
{
	while (feast_lasts(philo->info))
	{
		if (!still_alife(philo))
			return (set_philo_dead(philo));
		pthread_mutex_lock(&philo->right_f->mx);
		if (philo->right_f->is_avail)
		{
			philo->right_f->is_avail = 0;
			pthread_mutex_unlock(&philo->right_f->mx);
			pthread_mutex_lock(&philo->mx);
			philo->last_ate = current_time(philo->info);
			pthread_mutex_unlock(&philo->mx);
			return (1);
		}
		pthread_mutex_unlock(&philo->right_f->mx);
	}
	return (0);
}

static void	return_forks(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_f->mx);
	philo->right_f->is_avail = 1;
	pthread_mutex_unlock(&philo->right_f->mx);
	pthread_mutex_lock(&philo->left_f->mx);
	philo->left_f->is_avail = 1;
	pthread_mutex_unlock(&philo->left_f->mx);
}

int	philo_eats(t_philo *philo)
{
	//printf("Philo %d entered eats\n", philo->name);
	if (!get_left_fork(philo) || &philo->left_f->mx == &philo->right_f->mx || !get_right_fork(philo))
		return (set_philo_dead(philo));
	if (still_alife(philo))
	{
		pthread_mutex_lock(&philo->info->print_mx);
		if (!feast_lasts(philo->info))
		{
			pthread_mutex_unlock(&philo->info->print_mx);
			return (0);
		}
		printf("%s%llu %d %s", GREEN, philo->last_ate, philo->name, FORK);
		printf("%s%llu %d %s", YELL, philo->last_ate, philo->name, EATING);
		pthread_mutex_unlock(&philo->info->print_mx);
	}
	else
		return (set_philo_dead(philo));
	pthread_mutex_lock(&philo->mx);
	philo->time_of_death = philo->last_ate + philo->info->time_to_die;
	philo->times_ate++;
	pthread_mutex_unlock(&philo->mx);
	usleep((philo->last_ate + philo->info->time_to_eat - current_time(philo->info)) * 1000); // check times
	return_forks(philo);
	return (1);
}
