/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:47:48 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/19 14:48:28 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_life(t_philo *philo)
{
	while (!philo->last_ate || feast_lasts(philo->info))
	{
		if (philo->name % 2 && !philo_thinks(philo)) //think if odd ??? philo->time_of_death - current_time(philo->info)
			break ;
		if (!philo_eats(philo))
			break ;
		if (!philo_sleeps(philo))
			break ;
		if (philo->info->n_must_eat && done_eating(philo))
			break ;
		if (!(philo->name % 2) && !philo_thinks(philo)) //think if even
			break ;
	}
}

static int	set_philo(unsigned int i, t_philo *philo, t_info *info)
{
	//printf("Set philo %d\n", i + 1);
	philo->info = info;
	philo->name = i + 1;
	philo->time_of_death = info->time_to_die;
	philo->left_f = &info->forks[i];
	if (i == info->n_of_phils - 1)
		philo->right_f = &info->forks[0];
	else
		philo->right_f = &info->forks[i + 1];
	if (pthread_create(&philo->t_id, NULL, (void *)&philo_life, (void *)philo) != 0)
	{
		write(1, MSG_THREAD, ft_strlen(MSG_THREAD));
		return (0);
	}
	pthread_detach(philo->t_id);
	return (1);
}

int	create_philos(t_philo **phils, t_info *info)
{
	unsigned int	i;

	i = 0;
	if (gettimeofday(&info->era_start, NULL) == -1)
	{
		clean_all(info);
		write(1, MSG_TIMEERR, ft_strlen(MSG_TIMEERR));
		return (0);
	}
	while (i < info->n_of_phils)
	{
		if (!set_philo(i, (*phils + i), info))
		{
			end_feast(info);
			wait_for_threads(info->philos, i);
			clean_all(info);
			return (0);
		}
		i++;
	}
	return (1);
}

int	init_philos(t_philo **philos, t_info *info)
{
	unsigned int	i;

	i = 0;
	while (i < info->n_of_phils)
	{
		if (pthread_mutex_init(&(*philos + i)->mx, NULL) != 0)
		{
			clean_p_mxs(i, *philos);
			return (0);
		}
		i++;
	}
	return (1);
}
