/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philos_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:10:34 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/10 15:06:43 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	philo_thinks(t_philo *philo, unsigned long long	time_left)
{
	pthread_mutex_lock(&philo->info->print_mx);
	printf("%s%llu %d %s", VIOLT, current_time(philo->info), philo->name, THINKING);
	pthread_mutex_unlock(&philo->info->print_mx);
	usleep(time_left * 500);
}

void	philo_sleeps(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print_mx);
	printf("%s%lld %d %s", BLUE, current_time(philo->info), philo->name, SLEEPING);
	pthread_mutex_unlock(&philo->info->print_mx);
	usleep(philo->info->time_to_sleep * 1000);
	// return (0);
}

static void	set_philo_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->info->print_mx);
	printf("from philo:\n");
	printf("%s%llu %d %s", RED, philo->time_of_death, philo->name, DEATH);
	pthread_mutex_unlock(&philo->info->print_mx);
	pthread_mutex_lock(&philo->info->monitor_mx);
	philo->is_dead = 1;
	philo->info->g_death = 1;
	pthread_mutex_unlock(&philo->info->monitor_mx);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
}

int	philo_eats(t_philo *philo)
{
	// printf("%llu %d trying to pick up 1st fork\n", current_time(philo->info), philo->name);
	pthread_mutex_lock(philo->left_f);
	pthread_mutex_lock(&philo->info->print_mx);
	printf("%s%llu %d %s", GREEN, current_time(philo->info), philo->name, FORK);
	pthread_mutex_unlock(&philo->info->print_mx);
	// printf("%llu %d trying to pick up 2nd fork\n", current_time(philo->info), philo->name);
	if (philo->left_f == philo->right_f)
	{
		set_philo_dead(philo);
		return (-1);
	}
	pthread_mutex_lock(philo->right_f);
	philo->last_ate = current_time(philo->info);
	if (philo->last_ate < philo->time_of_death)
	{
		pthread_mutex_lock(&philo->info->print_mx);
		printf("%s%llu %d %s", GREEN, philo->last_ate, philo->name, FORK);
		printf("%s%llu %d %s", YELL, philo->last_ate, philo->name, EATING);
		pthread_mutex_unlock(&philo->info->print_mx);
	}
	else
	{
		set_philo_dead(philo);
		return (-1);
	}
	philo->time_of_death = philo->last_ate + philo->info->time_to_die;
	philo->times_ate++;
	usleep(philo->info->time_to_eat * 1000);
	pthread_mutex_unlock(philo->right_f);
	pthread_mutex_unlock(philo->left_f);
	return (0);
}
