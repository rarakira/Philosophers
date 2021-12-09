/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:03:48 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/09 18:02:25 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static inline int	return_forks(t_philo *philo)
{
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	return (1);
}

static inline int	update_last_ate(t_philo *philo)
{
	philo->last_ate = current_time(philo->info);
	philo->time_of_death = philo->last_ate + philo->info->time_to_die;
	philo->times_ate++;
	printer(philo, current_time(philo->info), FORK, GREEN);
	printer(philo, current_time(philo->info), EATING, YELL);
	return (1);
}

static inline int	get_forks(t_philo *philo)
{
	sem_wait(philo->info->table);
	sem_wait(philo->info->forks);
	if (!still_alife(philo))
		return (set_philo_dead(philo));
	philo->current = current_time(philo->info);
	printer(philo, current_time(philo->info), FORK, GREEN);
	if (philo->single)
	{
		ft_sleep(philo->time_of_death, philo->info);
		return (0);
	}
	sem_wait(philo->info->forks);
	if (!still_alife(philo))
		return (set_philo_dead(philo));
	sem_post(philo->info->table);
	return (update_last_ate(philo));
}

int	philo_eats(t_philo *philo)
{
	if (!get_forks(philo))
		return (set_philo_dead(philo));
	ft_sleep(philo->last_ate + philo->info->time_to_eat, philo->info);
	return (return_forks(philo));
}
