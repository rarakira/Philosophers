/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   monitoring.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/10 13:14:35 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/09 16:53:35 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_bonus.h"

int	set_monitoring(t_philo **philos, t_info *info)
{
	int					status;
	unsigned int		finished;

	finished = 0;
	while (finished < info->n_of_phils)
	{
		if (waitpid (-1, &status, WUNTRACED) < 0)
		{
			if (errno == ECHILD)
				break ;
		}
		if (!(WIFEXITED(status) && (WEXITSTATUS(status) == 0)))
		{
			finished = 0;
			while (finished < info->n_of_phils)
				kill((*philos + finished++)->pid, SIGKILL);
			while (waitpid (-1, NULL, 0))
				if (errno == ECHILD)
					break ;
			return (1);
		}
		finished++;
	}
	printf("%s%llu %s", GREEN, current_time(info), SUCCESS);
	return (0);
}
