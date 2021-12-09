/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:17:01 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/09 16:54:34 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_forks(sem_t **forks, t_info *info)
{
	*forks = sem_open("/fork_sem", O_CREAT, S_IRWXU | S_IRWXG,
			info->n_of_phils);
	if (*forks == SEM_FAILED)
		return (0);
	if (sem_unlink("/fork_sem") == -1)
	{
		write(2, MSG_UNLINK, ft_strlen(MSG_UNLINK));
		sem_close(*forks);
		free(info->philos);
		exit (1);
	}
	return (1);
}
