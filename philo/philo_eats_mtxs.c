/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats_mtxs.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:03:48 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/09 18:20:39 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int	update_last_ate(t_philo *philo)
{
	philo->last_ate = current_time(philo->info);
	philo->time_of_death = philo->last_ate + philo->info->time_to_die;
	philo->times_ate++;
	if (!printer(philo, current_time(philo->info), CFORK, LEN_FORK)
		|| !printer(philo, current_time(philo->info), CEATING, LEN_EATING))
	{
		pthread_mutex_unlock(&philo->right_f->mx);
		pthread_mutex_unlock(&philo->left_f->mx);
		return (0);
	}
	return (1);
}

static inline int	get_left_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->left_f->mx);
	if (!still_alife(philo))
	{
		pthread_mutex_unlock(&philo->left_f->mx);
		if (!philo->leftie)
			pthread_mutex_unlock(&philo->right_f->mx);
		return (set_philo_dead(philo));
	}
	if (!philo->leftie)
		return (update_last_ate(philo));
	else
	{
		if (!printer(philo, current_time(philo->info), CFORK, LEN_FORK))
		{
			pthread_mutex_unlock(&philo->left_f->mx);
			return (0);
		}
	}
	return (1);
}

static inline int	get_right_fork(t_philo *philo)
{
	pthread_mutex_lock(&philo->right_f->mx);
	if (!still_alife(philo))
	{
		pthread_mutex_unlock(&philo->right_f->mx);
		if (philo->leftie)
			pthread_mutex_unlock(&philo->left_f->mx);
		return (set_philo_dead(philo));
	}
	if (philo->leftie)
		return (update_last_ate(philo));
	else
	{
		if (!printer(philo, current_time(philo->info), CFORK, LEN_FORK))
		{
			pthread_mutex_unlock(&philo->right_f->mx);
			return (0);
		}
	}
	return (1);
}

static inline int	is_alone(t_philo *philo)
{
	if (philo->left_f == philo->right_f)
	{
		pthread_mutex_unlock(&philo->left_f->mx);
		ft_sleep(philo->time_of_death, philo->info);
		return (1);
	}
	return (0);
}

int	philo_eats(t_philo *philo)
{
	if (philo->leftie)
	{
		if (!get_left_fork(philo) || !get_right_fork(philo))
			return (set_philo_dead(philo));
	}
	else
	{
		if (!get_right_fork(philo) || is_alone(philo) || !get_left_fork(philo))
			return (set_philo_dead(philo));
	}
	ft_sleep(philo->last_ate + philo->info->time_to_eat, philo->info);
	pthread_mutex_unlock(&philo->right_f->mx);
	pthread_mutex_unlock(&philo->left_f->mx);
	return (1);
}
