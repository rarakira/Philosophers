/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:20:12 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/08 16:36:23 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_all(t_info *info)
{
	int	er;
	printf("sem_close(Forks) return: %d\n", er = sem_close(info->forks));
	if (er)
		printf("Errno %d.\n", errno);
	free(info->philos);
	printf("sem_close(Table) return: %d\n", sem_close(info->table));
	printf("sem_close(Print) return: %d\n", sem_close(info->print));
	printf("sem_unlink(Forks) return: %d\n", sem_unlink("/forksem1"));
	printf("sem_unlink(Table) return: %d\n", sem_unlink("/tablesem1"));
	printf("sem_unlink(Print) return: %d\n", sem_unlink("/printsem1"));
	printf("All clean!\n");
}
