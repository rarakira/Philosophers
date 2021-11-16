/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:34 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/16 15:09:31 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_thinks(t_philo *philo, unsigned long long	time_left)
{
}

void	philo_sleeps(t_philo *philo)
{
}

int	still_alife(t_philo *philo)
{
	if (current_time(philo->info) < philo->time_of_death)
		return (1);
	return (0);
}

static void	set_philo_dead(t_philo *philo)
{
}

int	get_left_fork(t_philo *philo)
{
	return (0);
}

int	get_right_fork(t_philo *philo)
{
}

void	return_fork(t_philo *philo, char side)
{
}

int	philo_eats(t_philo *philo)
{
	return (0);
}
