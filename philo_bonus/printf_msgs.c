/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_msgs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:17:05 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/07 19:25:54 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	print_death(t_philo *philo, unsigned long long time, char *msg, int len)
{
	(void)len;
	sem_wait(philo->info->print);
	printf("%llu %d %s", time, philo->name, msg);
	return (1);
}

int	printer(t_philo *philo, unsigned long long time, char *msg, int len)
{
	(void)len;
	sem_wait(philo->info->print);
	printf("%llu %d %s", time, philo->name, msg);
	sem_post(philo->info->print);
	return (1);
}
