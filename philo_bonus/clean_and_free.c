/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:20:12 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/09 16:46:06 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_all(t_info *info)
{
	sem_close(info->forks);
	free(info->philos);
	sem_close(info->table);
	sem_close(info->print);
}
