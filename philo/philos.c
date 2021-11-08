/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:47:48 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/08 17:50:43 by lbaela           ###   ########.fr       */
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
	//printf("\nCurrent time: %ld, %u\n", current.tv_sec, current.tv_usec);
	res = (current.tv_sec - info->era_start.tv_sec) * 1000;
	//printf("Sec only: %lld (ms)\n", res);
	res += (current.tv_usec - info->era_start.tv_usec) / 1000;
	printf("Current time: %lld (ms)\n", res);
	return (res);
}

void	philo_life(t_philo *philo)
{
	printf("Philo %d is up\n", philo->name);
	while (!philo->is_dead)
	{
		if (current_time(philo->info) < philo->time_of_death)
		{
			printf("%d is still alife!\n", philo->name);
		}
		if (philo->times_ate == philo->info->n_must_eat)
			{}
		if (1)
			break ;
	}
}

int	create_philos(t_philo *phils, t_info *info)
{
	unsigned int	i;

	i = 0;
	phils = (t_philo *)malloc(sizeof(t_philo) * (info->n_of_phils));
	if (phils == NULL)
	{
		printer(MSG_MEM);
		return (0);
	}
	while (i < info->n_of_phils)
	{
		printf("Create philo %d\n", i + 1);
		(phils + i)->info = info;
		(phils + i)->is_dead = 0;
		(phils + i)->name = i + 1;
		(phils + i)->times_ate = 0;
		(phils + i)->last_ate = 0;
		(phils + i)->time_of_death = info->time_to_die;
		(phils + i)->left_f = &info->forks[i];
		if (i == info->n_of_phils - 1)
			(phils + i)->right_f = &info->forks[0];
		else
			(phils + i)->right_f = &info->forks[i + 1];
		if (pthread_create(&(phils + i)->t_id, NULL, (void *)&philo_life, (void *)(phils + i)) != 0)
		{
			//free
			printer(MSG_THREAD);
			return (0);
		}
		pthread_detach((phils + i)->t_id);
		i++;
	}
	return (1);
}