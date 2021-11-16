/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:17:01 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/16 15:22:54 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_fork **forks, t_info *info)
{
	unsigned int	i;

	i = 0;
	*forks = (t_fork *)malloc(sizeof(t_fork) * (info->n_of_phils));
	if (*forks == NULL)
	{
		printer(MSG_MEM);
		return (0);
	}
	while (i < info->n_of_phils)
	{
		(*forks + i)->is_avail = 1;
		if (pthread_mutex_init(&(*forks + i)->mx, NULL) != 0)
		{
			printf("MTX ERROR\n");
			clean_forks(i, *forks);
			free(*forks);
			pthread_mutex_destroy(&info->monitor_mx);
			pthread_mutex_destroy(&info->print_mx);
			printer(MSG_MUTEX);
			return (0);
		}
		i++;
	}
	return (1);
}