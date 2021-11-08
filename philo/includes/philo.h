/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:58:35 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/05 21:26:02 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <unistd.h>
# include <stdio.h>
# include <pthread.h>

# define MSG_NARGS		"Wrong number of arguments: should be 4 or 5\n"
# define MSG_FORMAT		"Wrong formatting: each argument should be a positive number\n"

typedef struct			s_philo
{
	int					name;
	int					is_dead;
	int					times_ate;
	unsigned long long	last_ate;
	unsigned long long	time_of_death;
	int					*left_fork;
	int					*right_fork;
	t_philo				*next;
	t_philo				*prev;
}						t_philo;

typedef struct			s_info
{
	unsigned int		n_of_phils;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_must_eat;
}						t_info;

size_t	ft_strlen(const char *str);
long	ft_atoi(const char *str);
int		ft_isdigit(int c);

#endif
