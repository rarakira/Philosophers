/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:14:35 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/02 17:13:42 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_monitoring(t_philo **philos, t_info *info)
{
	(void) philos;
	while (feast_lasts(info))
	{
		pthread_mutex_lock(&info->monitor_mx);
		if (info->n_must_eat && info->n_of_phils == info->phils_done)
		{
			pthread_mutex_unlock(&info->monitor_mx);
			printf("%s%llu %s", GREEN, current_time(info), SUCCESS);
			return (0);
		}
		pthread_mutex_unlock(&info->monitor_mx);
		usleep(500);
	}
	return (1);
}
