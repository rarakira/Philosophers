/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 14:47:48 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/07 20:13:47 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	set_philo_dead(t_philo *philo)
{
	// print_death(philo, current_time(philo->info), CDEATH, LEN_DEATH);
	printf("%sMessage time: %llu%s\n", RED, current_time(philo->info), END);
	print_death(philo, philo->time_of_death, CDEATH, LEN_DEATH);
	exit (1);
}

void	philo_life(t_philo *philo)
{
	printf("Philo %d sat at the table!\n", philo->name);
	while (1)
	{
		if (!philo_eats(philo))
			break ;
		if (!philo_sleeps(philo))
			break ;
		if (philo->info->n_must_eat && done_eating(philo))
		{
			printf("Philo %d exiting with code 0\n", philo->name);
			exit (0);
		}
		if (!philo_thinks(philo))
			break ;
	}
	printf("Philo %d exiting with code 1\n", philo->name);
	exit (1);
}

static int	set_philo(unsigned int i, t_philo *philo, t_info *info)
{
	philo->info = info;
	philo->name = i + 1;
	philo->time_of_death = info->time_to_die;
	philo->pid = fork();
	if (philo->pid < 0)
	{
		printf ("SET_PHILO: Fork error on philo creation.\n");
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
		clean_all(info);
		write(2, MSG_TIMEERR, ft_strlen(MSG_TIMEERR));
		return (0);
	}
	while (i < info->n_of_phils)
	{
		if (!set_philo(i, (*phils + i), info))
		{
			printf("Philo %u creation failed\n", i);
			j = 0;
			while (j < i)
				kill(phils[j++]->pid, SIGKILL);
			while (waitpid (-1, NULL, 0))
				if (errno == ECHILD)
					break;
			clean_all(info);
			return (0);
		}
		i++;
	}
	return (1);
}
