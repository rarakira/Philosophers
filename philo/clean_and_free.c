/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:20:12 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/10 11:57:15 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	clean_f_mxs(int n, t_fork *obj)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy(&(obj + i)->mx);
		i++;
	}
	free(obj);
}

void	clean_all(t_info *info)
{
	usleep(100000);
	clean_f_mxs(info->n_of_phils, info->forks);
	free(info->philos);
	pthread_mutex_destroy(&info->monitor_mx);
	pthread_mutex_unlock(&info->print_mx);
	pthread_mutex_destroy(&info->print_mx);
}
