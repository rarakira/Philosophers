/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:17:01 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/06 13:47:42 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_forks(sem_t *forks, t_info *info)
{
	*forks = sem_open("/fork_sem", O_CREAT | O_EXCL, 0644, info->n_of_phils);
	if (*forks == SEM_FAILED)
		return (0);
	if (sem_unlink("/fork_sem") == -1)
	{
		printf("Could not unlink the semaphore\n");
		sem_close(*forks);
		free(info->philos);
		return (0);
	}
	return (1);
}
