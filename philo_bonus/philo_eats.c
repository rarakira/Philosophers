/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_eats.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/17 18:03:48 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/07 20:22:24 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

static inline int	return_forks(t_philo *philo)
{
	sem_post(philo->info->forks);
	sem_post(philo->info->forks);
	printf("Philo %d returned forks\n", philo->name);
	return (1);
}

static inline int	update_last_ate(t_philo *philo)
{
	philo->last_ate = current_time(philo->info);
	philo->time_of_death = philo->last_ate + philo->info->time_to_die;
	philo->times_ate++;
	printer(philo, current_time(philo->info), CFORK, LEN_FORK);
	printer(philo, current_time(philo->info), CEATING, LEN_EATING);
	return (1);
}

static inline int	get_forks(t_philo *philo)
{
	sem_wait(philo->info->table);
	if (!sem_wait(philo->info->forks))
	{
		printf("Philo %d got a 1st fork\n", philo->name);
		if (!still_alife(philo))
			return (set_philo_dead(philo));
	}
	else
	{
		if (errno == EAGAIN)
		{
			printf("Philo %d could not obtain a fork. Exit (1)\n", philo->name);
			printf("The semaphore is already locked\n");
			exit (1);
		}
		if (errno == EDEADLK)
		{
			printf("Philo %d could not obtain a fork. Exit (2)\n", philo->name);
			printf("A deadlock was detected\n");
			exit (2);
		}
		if (errno == EINTR)
		{
			printf("Philo %d could not obtain a fork. Exit (3)\n", philo->name);
			printf("The call was interrupted by a signal\n");
			exit (3);
		}
	}
	philo->current = current_time(philo->info);
	printer(philo, current_time(philo->info), CFORK, LEN_FORK);
	if (!sem_wait(philo->info->forks))
	{
		printf("Philo %d got a 2nd fork\n", philo->name);
		if (!still_alife(philo))
			return (set_philo_dead(philo));
	}
	else
	{
		if (errno == EAGAIN)
		{
			printf("Philo %d could not obtain a 2nd fork. Exit (1)\n", philo->name);
			printf("The semaphore is already locked\n");
			exit (1);
		}
		if (errno == EDEADLK)
		{
			printf("Philo %d could not obtain a 2nd fork. Exit (2)\n", philo->name);
			printf("A deadlock was detected\n");
			exit (2);
		}
		if (errno == EINTR)
		{
			printf("Philo %d could not obtain a 2nd fork. Exit (3)\n", philo->name);
			printf("The call was interrupted by a signal\n");
			exit (3);
		}
	}
	sem_post(philo->info->table);
	printf("Philo %d updating last_ate\n", philo->name);
	return (update_last_ate(philo));
}

int	philo_eats(t_philo *philo)
{
	if (!get_forks(philo))
		return (set_philo_dead(philo));
	// printf("%d before usleep: %llu\n", philo->name, current_time(philo->info));
	ft_sleep(philo->last_ate + philo->info->time_to_eat, philo->info);
	// usleep(philo->info->time_to_eat * 1000);
	// printf("%d after usleep: %llu\n", philo->name, current_time(philo->info));
	return (return_forks(philo));
}
