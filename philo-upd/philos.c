/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:47:48 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/16 17:35:53 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

unsigned long long	current_time(t_info *info)
{
	unsigned long long	res;
	struct timeval		current;

	if (gettimeofday(&current, NULL) == -1)
	{
		printer(MSG_TIMEERR);
		//free all;
		exit (1);
	}
	res = (current.tv_sec - info->era_start.tv_sec) * 1000;
	res += (current.tv_usec - info->era_start.tv_usec) / 1000;
	return (res);
}

void	philo_life(t_philo *philo)
{
}

int	init_philo(unsigned int i, t_philo *philo, t_info *info)
{
	//printf("Create philo %d\n", i + 1);
	philo->info = info;
	philo->is_dead = 0;
	philo->name = i + 1;
	philo->times_ate = 0;
	philo->last_ate = 0;
	philo->time_of_death = info->time_to_die;
	philo->left_f = &info->forks[i];
	if (i == info->n_of_phils - 1)
		philo->right_f = &info->forks[0];
	else
		philo->right_f = &info->forks[i + 1];
	if (pthread_create(&philo->t_id, NULL, (void *)&philo_life, (void *)philo) != 0)
	{
		//free
		printer(MSG_THREAD);
		return (0);
	}
	pthread_detach(philo->t_id);
	return (1);
}

int	create_philos(t_philo **phils, t_info *info)
{
	unsigned int	i;

	i = 0;
	*phils = (t_philo *)malloc(sizeof(t_philo) * (info->n_of_phils));
	if (*phils == NULL)
	{
		printer(MSG_MEM);
		//free
		return (0);
	}
	if (gettimeofday(&info->era_start, NULL) == -1) // ???
	{
		printer(MSG_TIMEERR);
		return (0);
	}
	while (i < info->n_of_phils)
	{
		if (!init_philo(i, (*phils + i), info))
			return (0);
		i++;
	}
	return (1);
}