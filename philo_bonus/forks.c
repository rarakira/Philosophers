/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:17:01 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/08 17:21:56 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	create_forks(sem_t **forks, t_info *info)
{
	if (sem_unlink("/forksem1") == -1)
	{
		printf("Sem_unlink res: %d, errno == %d\n", -1, errno);
		// if (errno == EACCES)
		// 	printf("Permission is denied to remove the semaphore.\n");
		// else if (errno == ENAMETOOLONG)
		// 	printf("Name exceeded PSEMNAMLEN characters.\n");
		// else if (errno == ENOENT)
		// 	printf("The named semaphore does not exist.\n");
		// else if (errno == EFAULT)
		// 	printf("While attempting to access a parameter passed to this function, the system detected an address that is not valid.\n");
	}
	*forks = sem_open("/forksem1", O_CREAT, S_IRWXU | S_IRWXG, info->n_of_phils);
	if (*forks == SEM_FAILED)
		return (0);
	// if (sem_unlink("/forksem") == -1)
	// {
	// 	printf("Could not unlink the semaphore\n");
	// 	sem_close(forks);
	// 	free(info->philos);
	// 	return (0);
	// }
	printf("Forks created!\n");
	return (1);
}
