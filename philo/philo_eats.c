/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:03:48 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/10 14:09:05 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static inline int	update_last_ate(t_philo *philo)
{
	philo->last_ate = current_time(philo->info);
	philo->time_of_death = philo->last_ate + philo->info->time_to_die;
	philo->times_ate++;
	if (!printer(philo, current_time(philo->info), FORK, GREEN)
		|| !printer(philo, current_time(philo->info), EATING, YELL))
		return (0);
	return (1);
}

static inline int	get_left_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->left_f->mx);
		if (!still_alife(philo))
		{
			pthread_mutex_unlock(&philo->left_f->mx);
			return (set_philo_dead(philo));
		}
		if (!philo->left_f->is_avail)
		{
			pthread_mutex_unlock(&philo->left_f->mx);
			usleep(50);
			continue ;
		}
		philo->left_f->is_avail = 0;
		pthread_mutex_unlock(&philo->left_f->mx);
		if (!philo->leftie)
			return (update_last_ate(philo));
		else
			return (printer(philo, current_time(philo->info), FORK, GREEN));
	}
}

static inline int	get_right_fork(t_philo *philo)
{
	while (1)
	{
		pthread_mutex_lock(&philo->right_f->mx);
		if (!still_alife(philo))
		{
			pthread_mutex_unlock(&philo->right_f->mx);
			return (set_philo_dead(philo));
		}
		if (!philo->right_f->is_avail)
		{
			pthread_mutex_unlock(&philo->right_f->mx);
			usleep(50);
			continue ;
		}
		philo->right_f->is_avail = 0;
		pthread_mutex_unlock(&philo->right_f->mx);
		if (philo->leftie)
			return (update_last_ate(philo));
		else
			return (printer(philo, current_time(philo->info), FORK, GREEN));
	}
}

static inline int	is_alone(t_philo *philo)
{
	if (philo->left_f == philo->right_f)
	{
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
	pthread_mutex_lock(&philo->right_f->mx);
	philo->right_f->is_avail = 1;
	pthread_mutex_unlock(&philo->right_f->mx);
	pthread_mutex_lock(&philo->left_f->mx);
	philo->left_f->is_avail = 1;
	pthread_mutex_unlock(&philo->left_f->mx);
	return (1);
}
