/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:17:01 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/17 20:33:59 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	create_forks(t_fork **forks, t_info *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->n_of_phils)
	{
		(*forks + i)->is_avail = 1;
		if (pthread_mutex_init(&(*forks + i)->mx, NULL) != 0)
		{
			clean_f_mxs(i, *forks);
			//clean_f_mxs(i, *forks);
			return (0);
		}
		i++;
	}
	return (1);
}
