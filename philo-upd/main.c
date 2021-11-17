/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:59:02 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/17 20:40:18 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	valid_args(char **argv, int argc)
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

static int	parse_args(t_info *info, char **argv, int argc)
{
	if (!valid_args(argv, argc))
	{
		printer(MSG_FORMAT);
		return (0);
	}
	memset(info, 0, sizeof(t_info));
	info->n_of_phils = (unsigned int)ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->n_must_eat = ft_atoi(argv[5]);
	return (1);
}

static int	malloc_arrays(t_info *info)
{
	info->forks = (t_fork *)malloc(sizeof(t_fork) * (info->n_of_phils));
	if (info->forks == NULL)
	{
		printer(MSG_MEM);
		return (0);
	}
	memset(info->forks, 0, sizeof(t_fork) * (info->n_of_phils));
	info->philos = (t_philo *)malloc(sizeof(t_philo) * (info->n_of_phils));
	if (info->philos == NULL)
	{
		free(info->forks);
		printer(MSG_MEM);
		return (0);
	}
	memset(info->philos, 0, sizeof(t_fork) * (info->n_of_phils));
	return (1);
}

static int	init_mxs(t_info *info)
{
	if (!create_forks(&info->forks, info))
		return (0);
	if (!init_philos(&info->philos, info))
	{
		clean_f_mxs(info->n_of_phils, info->forks);
		return (0);
	}
	if (pthread_mutex_init(&info->print_mx, NULL) != 0)
	{
		clean_f_mxs(info->n_of_phils, info->forks);
		clean_p_mxs(info->n_of_phils, info->philos);
		return (0);
	}
	if (pthread_mutex_init(&info->monitor_mx, NULL) != 0)
	{
		pthread_mutex_destroy(&info->print_mx);
		clean_f_mxs(info->n_of_phils, info->forks);
		clean_p_mxs(info->n_of_phils, info->philos);
		return (0);
	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;

	if (argc == 5 || argc == 6)
	{
		if (!parse_args(&info, argv, argc))
			return (1);
		if (!malloc_arrays(&info))
			return (1);
		if (!init_mxs(&info))
		{
			printer(MSG_MUTEX);
			return (1);
		}
		if (!create_philos(&info.philos, &info))
			return (1);
		set_monitoring(&info.philos, &info);
		wait_for_threads(info.philos, info.n_of_phils);
		clean_all(&info);
	}
	else
		printer(MSG_NARGS);
	return (0);
}
