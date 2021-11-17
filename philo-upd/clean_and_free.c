/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:20:12 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/17 20:34:58 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_threads(t_philo *philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join((philos + i)->t_id, NULL);
		i++;
	}
}

void	clean_f_mxs(int n, t_fork *obj)
{
	int	i;

	i = 0;
	while (i < n)
	{
		while (pthread_mutex_destroy(&(obj + i)->mx))
		{
			usleep(100);
			printf("Cleaning threads\n");
		}
		i++;
	}
	free(obj);
}

void	clean_p_mxs(int n, t_philo *obj)
{
	int	i;

	i = 0;
	while (i < n)
	{
		while (pthread_mutex_destroy(&(obj + i)->mx))
		{
			usleep(100);
			printf("Cleaning threads\n");
		}
		i++;
	}
	free(obj);
}

void	clean_all(t_info *info)
{
	clean_f_mxs(info->n_of_phils, info->forks);
	clean_p_mxs(info->n_of_phils, info->philos);
	while (pthread_mutex_destroy(&info->monitor_mx))
			usleep(100);
	if (pthread_mutex_destroy(&info->print_mx) != 0) // ?
	{
		pthread_mutex_unlock(&info->print_mx);
		pthread_mutex_destroy(&info->print_mx);
	}
}
