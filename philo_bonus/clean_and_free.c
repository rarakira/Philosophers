/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_free.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:20:12 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/06 16:05:20 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

void	clean_all(t_info *info)
{
	sem_close(info->forks);
	free(info->philos);
	printf("monitor_mx_destroy return: %d\n", pthread_mutex_destroy(&info->monitor_mx));
	printf("print_mx_destroy return: %d\n", pthread_mutex_destroy(&info->print_mx));
	// while (pthread_mutex_destroy(&info->monitor_mx))
	// 	usleep(100);
	// while (pthread_mutex_destroy(&info->print_mx))
	// 	usleep(100);
}
