/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:47:48 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/15 20:01:46 by lbaela           ###   ########.fr       */
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
	unsigned long long	time_left;

	while (!philo->is_dead && !philo->info->g_death)
	{
		time_left = philo->time_of_death - current_time(philo->info);
		if (philo->name % 2 && time_left > (unsigned long long)philo->info->time_to_eat)
			philo_thinks(philo, time_left);
		else if (philo->name % 2)
			philo_thinks(philo, 1);
		if (philo_eats(philo) == -1)
			break ;
		philo_sleeps(philo);
		if (philo->times_ate == philo->info->n_must_eat)
		{
			pthread_mutex_lock(&philo->info->monitor_mx);
			philo->info->phils_done++;
			pthread_mutex_unlock(&philo->info->monitor_mx);
			//printf("%lld Philo %d has finished eating\n", current_time(philo->info), philo->name);
			break ;
		}
		time_left = philo->time_of_death - current_time(philo->info);
		if (philo->name % 2 == 0 && time_left > (unsigned long long)philo->info->time_to_eat)
			philo_thinks(philo, time_left);
		else if (philo->name % 2 == 0)
			philo_thinks(philo, 1);
	}
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
	philo->left_f = &info->forks[i].mx;
	if (i == info->n_of_phils - 1)
		philo->right_f = &info->forks[0].mx;
	else
		philo->right_f = &info->forks[i + 1].mx;
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

/*
int	create_philos(t_philo **phils, t_info *info)
{
	unsigned int	i;

	i = 0;
	*phils = (t_philo *)malloc(sizeof(t_philo) * (info->n_of_phils));
	if (*phils == NULL)
	{
		printer(MSG_MEM);
		return (0);
	}
	while (i < info->n_of_phils)
	{
		if (!init_philo(i, (*phils + i), info))
			return (0);
		i += 2;
	}
	usleep(1000);
	i = 1;
	while (i < info->n_of_phils)
	{
		if (!init_philo(i, (*phils + i), info))
			return (0);
		i += 2;
	}
	return (1);
} */

/*
while (pthread_mutex_lock(philo->left_f) != 0)
	printf("ERROR(%d): L_FORK MX is unavail\n", philo->name);
*/
