/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:20:12 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/06 13:56:43 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	wait_for_threads(t_philo *philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		// printf("pthread [%d] join return: %d\n", (philos + i)->name, pthread_join((philos + i)->t_id, NULL));
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
		printf("mtx_[%d]_destroy return: %d\n", i, pthread_mutex_destroy(&(obj + i)->mx));
		// while (pthread_mutex_destroy(&(obj + i)->mx))
		// 	usleep(100);
		i++;
	}
	free(obj);
}

void	clean_all(t_info *info)
{
	clean_f_mxs(info->n_of_phils, info->forks);
	free(info->philos);
	printf("monitor_mx_destroy return: %d\n", pthread_mutex_destroy(&info->monitor_mx));
	printf("print_mx_destroy return: %d\n", pthread_mutex_destroy(&info->print_mx));
	// while (pthread_mutex_destroy(&info->monitor_mx))
	// 	usleep(100);
	// while (pthread_mutex_destroy(&info->print_mx))
	// 	usleep(100);
}
