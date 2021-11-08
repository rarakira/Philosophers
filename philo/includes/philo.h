/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:58:35 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/08 17:34:14 by lbaela           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <stddef.h>
# include <unistd.h>
# include <stdlib.h>
# include <stdio.h>
# include <pthread.h>
# include <sys/time.h>

# define MSG_NARGS		"Wrong number of arguments: should be 4 or 5\n"
# define MSG_FORMAT		"Wrong formatting: each argument should be a positive number\n"
# define MSG_TIMEERR	"Gettimeofday function error\n"
# define MSG_MEM		"Memory allocation failed\n"
# define MSG_MUTEX		"Mutex creation failed\n"
# define MSG_THREAD		"Thread creation failed\n"

typedef struct			s_fork
{
	pthread_mutex_t		mutex;
	int					avail;
}						t_fork;

typedef struct s_info	t_info;

typedef struct			s_philo
{
	int					name;
	int					is_dead;
	int					times_ate;
	unsigned long long	last_ate;
	unsigned long long	time_of_death;
	t_fork				*left_f;
	t_fork				*right_f;
	pthread_t			t_id;
	struct s_info		*info;
	// struct s_philo		*next;
	// struct s_philo		*prev;
}						t_philo;

struct			s_info
{
	unsigned int		n_of_phils;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_must_eat;
	struct timeval		era_start;
	t_fork				*forks;
	t_philo				*philos;
};

/* philosephers functions */
int		create_philos(t_philo *phils, t_info *info);
void	printer(char *msg);

/* libft functions */
size_t	ft_strlen(const char *str);
long	ft_atoi(const char *str);
int		ft_isdigit(int c);

#endif
