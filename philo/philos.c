/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:47:48 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/10 12:04:37 by lbaela           ###   ########.fr       */
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
	// printf("\nCurrent time: %ld, %u\n", current.tv_sec, current.tv_usec);
	res = (current.tv_sec - info->era_start.tv_sec) * 1000;
	res += (current.tv_usec - info->era_start.tv_usec) / 1000;
	// printf("Current time: %lld (ms)\n", res);
	return (res);
}

int		philo_eats(t_philo *philo)
{
	// printf("%lld %d trying to pick up 1st fork\n", current_time(philo->info), philo->name);
	while (pthread_mutex_lock(philo->left_f) != 0)
		printf("ERROR(%d): L_FORK MX is unavail\n", philo->name);
	printf("%s%lld %d %s%s", GREEN, current_time(philo->info), philo->name, FORK, END);
	// printf("%lld %d trying to pick up 2nd fork\n", current_time(philo->info), philo->name);
	while (pthread_mutex_lock(philo->right_f) != 0)
		printf("ERROR(%d): R_FORK MX is unavail\n", philo->name);
	philo->last_ate = current_time(philo->info);
	if (philo->last_ate < philo->time_of_death)
		printf("%s%lld %d %s%s", YELL, philo->last_ate, philo->name, EATING, END);
	else
	{
		philo->is_dead = 1;
		printf("%s%lld %d %s%s", RED, philo->time_of_death, philo->name, DEATH, END);
		pthread_mutex_lock(&philo->info->monitor_mx);
		philo->info->g_death = 1;
		pthread_mutex_unlock(&philo->info->monitor_mx);
		return (-1);
	}
	philo->time_of_death = philo->last_ate + philo->info->time_to_die;
	philo->times_ate++;
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
	return (0);
}

void	philo_life(t_philo *philo)
{
	while (!philo->is_dead && !philo->info->g_death)
	{
		if (philo_eats(philo) == -1)
			break ;
		if (philo->times_ate == philo->info->n_must_eat)
		{
			pthread_mutex_lock(&philo->info->monitor_mx);
			philo->info->phils_done++;
			pthread_mutex_unlock(&philo->info->monitor_mx);
			//printf("%lld Philo %d has finished eating\n", current_time(philo->info), philo->name);
			break ;
		}
		printf("%s%lld %d %s%s", BLUE, current_time(philo->info), philo->name, SLEEPING, END);
		usleep(philo->info->time_to_sleep * 1000);
		printf("%s%lld %d %s%s", VIOLT, current_time(philo->info), philo->name, THINKING, END);
		usleep(1000);
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
	philo->left_f = &info->fork_mxs[i];
	if (i == info->n_of_phils - 1)
		philo->right_f = &info->fork_mxs[0];
	else
		philo->right_f = &info->fork_mxs[i + 1];
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
}