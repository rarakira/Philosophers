/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:47:48 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/22 17:29:54 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	set_philo_dead(t_philo *philo)
{
	if (still_alife(philo) || !feast_lasts(philo->info))
		return (0);
	end_feast(philo->info);
	philo->is_dead = 1;
	// print_death(philo, current_time(philo->info), CDEATH, LEN_DEATH);
	printf("%sMessage time: %llu%s\n", RED, current_time(philo->info), END);
	print_death(philo, philo->time_of_death, CDEATH, LEN_DEATH);
	return (0);
}

void	philo_life(t_philo *philo)
{
	while (1)
	{
		if (!philo_eats(philo))
			break ;
		if (!philo_sleeps(philo))
			break ;
		if (philo->info->n_must_eat && done_eating(philo))
			break ;
		if (!philo_thinks(philo))
			break ;
	}
}

static int	set_philo(unsigned int i, t_philo *philo, t_info *info)
{
	philo->info = info;
	philo->name = i + 1;
	if (i % 2)
		philo->leftie = 1;
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
			// wait_for_threads(info->philos, i);
			clean_all(info);
			return (0);
		}
		i += 2;
	}
	usleep(50);
	i = 1;
	while (i < info->n_of_phils)
	{
		if (!set_philo(i, (*phils + i), info))
		{
			end_feast(info);
			// wait_for_threads(info->philos, i);
			clean_all(info);
			return (0);
		}
		i += 2;
	}
	return (1);
}
