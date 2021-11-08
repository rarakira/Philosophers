/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:59:02 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/08 09:09:21 by lbaela           ###   ########.fr       */
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
	info->n_must_eat = 0;
	info->n_of_phils = (unsigned int)ft_atoi(argv[1]);
	info->time_to_die = ft_atoi(argv[2]);
	info->time_to_eat = ft_atoi(argv[3]);
	info->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		info->n_must_eat = ft_atoi(argv[5]);
	return (1);
}

int	create_philos(t_philo **first, t_info *info)
{
	unsigned int	i;
	t_philo			*tmp;

	i = 1;
	while (i <= info->n_of_phils)
	{

	}
	return (1);
}

int	main(int argc, char **argv)
{
	t_info	info;
	t_philo	*philo;

	if (argc == 5 || argc == 6)
	{
		if (!parse_args(&info, argv, argc))
			return (0);
		if (!create_philos(&philo, &info))
			return (0);
		//create_forks();
		create_threads();
	}
	else
		printer(MSG_NARGS);
	return (0);
}
