/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:59:02 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/08 17:21:42 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

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
		write(2, MSG_FORMAT, ft_strlen(MSG_FORMAT));
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
	info->philos = (t_philo *)malloc(sizeof(t_philo) * (info->n_of_phils));
	if (info->philos == NULL)
	{
		write(2, MSG_MEM, ft_strlen(MSG_MEM));
		return (0);
	}
	memset(info->philos, 0, sizeof(t_philo) * (info->n_of_phils));
	return (1);
}

static int	init_sems(t_info *info)
{
	if (!create_forks(&info->forks, info))
		return (0);
	printf("sem_unlink(Table) return: %d\n", sem_unlink("/tablesem1"));
	printf("sem_unlink(Print) return: %d\n", sem_unlink("/printsem1"));
	info->print = sem_open("/printsem1", O_CREAT, S_IRWXU | S_IRWXG, 1);
	if (info->print == SEM_FAILED)
		return (0);
	info->table = sem_open("/tablesem1", O_CREAT, S_IRWXU | S_IRWXG, 1);
	if (info->table == SEM_FAILED)
		return (0);
	// if (sem_unlink("/printsem") == -1 || sem_unlink("/tablesem") == -1)
	// {
	// 	printf("Could not unlink the semaphore\n");
	// 	sem_close(info->forks);
	// 	sem_close(info->print);
	// 	sem_close(info->table);
	// 	free(info->philos);
	// 	return (0);
	// }
	printf("All semaphors created!\n");
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;
	int		res;

	res = 1;
	if (argc == 5 || argc == 6)
	{
		if (!parse_args(&info, argv, argc))
			return (1);
		if (!malloc_arrays(&info))
			return (1);
		if (!init_sems(&info))
		{
			write(2, MSG_MUTEX, ft_strlen(MSG_MUTEX));
			return (1);
		}
		if (!create_philos(&info.philos, &info))
			return (1);
		res = set_monitoring(&info.philos, &info);
		clean_all(&info);
	}
	else
		write(2, MSG_NARGS, ft_strlen(MSG_NARGS));
	return (res);
}
