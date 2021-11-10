/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:59:02 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/10 12:02:54 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	printer(char *msg)
{
	write(1, msg, ft_strlen(msg));
}

int	valid_args(char **argv, int argc)
{
	int	i;
	int	j;

	i = 1;
	while (i < argc)
	{
		j = 0;
		while (argv[i][j] != '\0')
		{
			if (!ft_isdigit(argv[i][j]) || j > 9)
				return (0);
			j++;
		}
		if (ft_atoi(argv[i]) > 2147483647)
			return (0);
		i++;
	}
	return (1);
}

int	parse_args(t_info *info, char **argv, int argc)
{
	if (!valid_args(argv, argc))
	{
		printer(MSG_FORMAT);
		return (0);
	}
	if (gettimeofday(&info->era_start, NULL) == -1)
	{
		printer(MSG_TIMEERR);
		return (0);
	}
	info->n_must_eat = 0;
	info->phils_done = 0;
	info->g_death = 0;
	info->n_of_phils = (unsigned int)ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->n_must_eat = ft_atoi(argv[5]);
	if (pthread_mutex_init(&info->print_mx, NULL) != 0 &&
			pthread_mutex_init(&info->monitor_mx, NULL) != 0)
	{
		printf("MTX ERROR\n");
		printer(MSG_MUTEX);
		return (0);
	}
	return (1);
}

void	clean_up(int n, pthread_mutex_t *forks)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_mutex_destroy((forks + i));
		i++;
	}
}

int	create_forks(pthread_mutex_t **forks, t_info *info)
{
	unsigned int	i;

	i = 0;
	*forks = (pthread_mutex_t *)malloc(sizeof(pthread_mutex_t) * (info->n_of_phils));
	if (*forks == NULL)
	{
		printer(MSG_MEM);
		return (0);
	}
	while (i < info->n_of_phils)
	{
		//printf("Fork creation: %d\n", i);
		if (pthread_mutex_init((*forks + i), NULL) != 0)
		{
			printf("MTX ERROR\n");
			clean_up(i, *forks);
			free(*forks);
			printer(MSG_MUTEX);
			return (0);
		}
		i++;
	}
	return (1);
}

void	wait_for_threads(t_philo **philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join((*philos + i)->t_id, NULL);
		i++;
	}
}

void	detach_threads(t_philo **philos, int n)
{
	int	i;

	i = 0;
	while (i < n)
	{
		pthread_join((*philos + i)->t_id, NULL);
		i++;
	}
}

int	set_monitoring(t_philo **philos, t_info *info)
{
	unsigned int	i;

	i = 0;
	while (!info->g_death && info->n_of_phils != info->phils_done)
	{
		// if (i == 0)
		// 	printf("MONITOR: %d phils done of %d\n", info->phils_done, info->n_of_phils);
		if ((*philos)[i].times_ate != info->n_must_eat &&
				(*philos)[i].time_of_death <= current_time(info))
		{
			(*philos)[i].is_dead = 1;
			pthread_mutex_lock(&info->monitor_mx);
			info->g_death = 1;
			pthread_mutex_unlock(&info->monitor_mx);
			break ;
		}
		i++;
		if (i == info->n_of_phils)
			i = 0;
	}
	//detach_threads(philos, info->n_of_phils);
	printf("MONITOR FIN: %d phils done of %d\n", info->phils_done, info->n_of_phils);
	if (info->g_death)
	{
		printf("%s%lld %d %s%s", RED, (*philos)[i].time_of_death, (*philos)[i].name, DEATH, END);
		//detach_threads(philos, info->n_of_phils);
	}
	else
		printf("%s%lld %s%s", GREEN, current_time(info), SUCCESS, END);
	return (0);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc == 5 || argc == 6)
	{
		if (!parse_args(&info, argv, argc))
			return (0);
		//printf("Time started: %ld, %u\n", info.era_start.tv_sec, info.era_start.tv_usec);
		if (!create_forks(&info.fork_mxs, &info))
			return (0);
		if (!create_philos(&info.philos, &info))
			return (0);
		set_monitoring(&info.philos, &info);
		wait_for_threads(&info.philos, info.n_of_phils);
		//clean_all() - mxs, 2 arrays
	}
	else
		printer(MSG_NARGS);
	return (0);
}
