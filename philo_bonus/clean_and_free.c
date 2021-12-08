/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:20:12 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/07 20:20:23 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_all(t_info *info)
{
	printf("sem_close(Forks) return: %d\n", sem_close(info->forks));
	free(info->philos);
	printf("sem_close(Table) return: %d\n", sem_close(info->table));
	printf("sem_close(Print) return: %d\n", sem_close(info->print));
	printf("All clean!\n");
}
