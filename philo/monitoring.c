/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:14:35 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/16 15:01:28 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_monitoring(t_philo **philos, t_info *info)
{
	unsigned int	i;

	i = 0;
	pthread_mutex_lock(&info->monitor_mx);
	while (!info->g_death &&
		(!info->n_must_eat || info->n_of_phils != info->phils_done))
	{
		pthread_mutex_unlock(&info->monitor_mx);
		// if (i == 0)
		// 	printf("MONITOR: %d phils done of %d\n", info->phils_done, info->n_of_phils);
		usleep(1000);
		pthread_mutex_lock(&(*philos)[i].left_f->mx);
		if ((*philos)[i].times_ate != info->n_must_eat &&
				(*philos)[i].time_of_death <= current_time(info))
		{
			pthread_mutex_lock(&info->monitor_mx);
			(*philos)[i].is_dead = 1;
			info->g_death = 1;
			pthread_mutex_unlock(&info->monitor_mx);
			pthread_mutex_unlock(&(*philos)[i].left_f->mx);
			break ;
		}
		pthread_mutex_unlock(&(*philos)[i].left_f->mx);
		i++;
		if (i == info->n_of_phils)
			i = 0;
		pthread_mutex_lock(&info->monitor_mx);
	}
	pthread_mutex_lock(&info->print_mx);
	printf("MONITOR FIN: %d phils done of %d\n", info->phils_done, info->n_of_phils);
	if (info->g_death)
	{
		printf("from monitor:\n");
		if ((*philos)[i].is_dead)
			printf("%s%llu [actual: %llu] %d %s", RED, current_time(info), (*philos)[i].time_of_death, (*philos)[i].name, DEATH);
	}
	else
		printf("%s%llu %s", GREEN, current_time(info), SUCCESS);
	pthread_mutex_unlock(&info->print_mx);
	return (0);
}

/*
int	set_monitoring(t_philo **philos, t_info *info)
{
	unsigned int	i;

	i = 0;
	while (!info->g_death &&
		(!info->n_must_eat || info->n_of_phils != info->phils_done))
	{
		// if (i == 0)
		// 	printf("MONITOR: %d phils done of %d\n", info->phils_done, info->n_of_phils);
		usleep(1000);
		if ((*philos)[i].times_ate != info->n_must_eat &&
				(*philos)[i].time_of_death <= current_time(info))
		{
			pthread_mutex_lock(&info->monitor_mx);
			(*philos)[i].is_dead = 1;
			info->g_death = 1;
			pthread_mutex_unlock(&info->monitor_mx);
			break ;
		}
		i++;
		if (i == info->n_of_phils)
			i = 0;
	}
	pthread_mutex_lock(&info->print_mx);
	printf("MONITOR FIN: %d phils done of %d\n", info->phils_done, info->n_of_phils);
	if (info->g_death)
	{
		printf("from monitor:\n");
		if ((*philos)[i].is_dead)
			printf("%s%llu [actual: %llu] %d %s", RED, current_time(info), (*philos)[i].time_of_death, (*philos)[i].name, DEATH);
	}
	else
		printf("%s%llu %s", GREEN, current_time(info), SUCCESS);
	pthread_mutex_unlock(&info->print_mx);
	return (0);
} */