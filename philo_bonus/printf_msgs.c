/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_msgs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:17:05 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/09 16:37:15 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_death(t_philo *philo, unsigned long long time, char *msg, char *col)
{
	sem_wait(philo->info->print);
	printf("%s%llu %d %s", col, time, philo->name, msg);
	return (1);
}

int	printer(t_philo *philo, unsigned long long time, char *msg, char *col)
{
	sem_wait(philo->info->print);
	printf("%s%llu %d %s", col, time, philo->name, msg);
	sem_post(philo->info->print);
	return (1);
}
