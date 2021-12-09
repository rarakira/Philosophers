/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:47:48 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/09 18:01:09 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	set_philo_dead(t_philo *philo)
{
	print_death(philo, philo->time_of_death, DEATH, RED);
	exit (1);
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
			exit (0);
		if (!philo_thinks(philo))
			break ;
	}
	exit (1);
}

static int	set_philo(unsigned int i, t_philo *philo, t_info *info)
{
	philo->info = info;
	philo->name = i + 1;
	if (!i && info->n_of_phils == 1)
		philo->single = 1;
	philo->time_of_death = info->time_to_die;
	philo->pid = fork();
	if (philo->pid < 0)
	{
		printf("An error occured while creating %u'th philo\n", i + 1);
		printf("Wrapping up program\n");
		return (0);
	}
	else if (philo->pid == 0)
		philo_life(philo);
	return (1);
}

int	create_philos(t_philo **phils, t_info *info)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (gettimeofday(&info->era_start, NULL) == -1)
	{
		write(2, MSG_TIMEERR, ft_strlen(MSG_TIMEERR));
		return (0);
	}
	while (i < info->n_of_phils)
	{
		if (!set_philo(i, (*phils + i), info))
		{
			sem_wait(info->print);
			j = 0;
			while (j < i)
				kill((*phils + j++)->pid, SIGKILL);
			while (waitpid (-1, NULL, 0))
				if (errno == ECHILD)
					break ;
			return (0);
		}
		i++;
	}
	return (1);
}
