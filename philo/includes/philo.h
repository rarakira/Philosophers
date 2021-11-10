/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:58:35 by lbaela            #+#    #+#             */
/*   Updated: 2021/11/10 14:22:37 by lbaela           ###   ########.fr       */
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
# define MSG_FORMAT		"Wrong formatting: \
each argument should be a positive number\n"
# define MSG_TIMEERR	"Gettimeofday function error\n"
# define MSG_MEM		"Memory allocation failed\n"
# define MSG_MUTEX		"Mutex creation failed\n"
# define MSG_THREAD		"Thread creation failed\n"

# define FORK			"has taken a fork\e[0m\n"
# define EATING			"is eating\e[0m\n"
# define SLEEPING		"is sleeping\e[0m\n"
# define THINKING		"is thinking\e[0m\n"
# define DEATH			"is dead\e[0m\n"
# define SUCCESS		"Everyone has finished eating\e[0m\n"

# define BOLD			"\e[1m"
# define RED			"\e[1;31m"
# define YELL			"\e[1;33m"
# define GREEN			"\e[1;32m"
# define BLUE			"\e[1;34m"
# define VIOLT			"\e[1;35m"
# define END			"\e[0m"

typedef struct s_info	t_info;

typedef struct s_philo
{
	int					name;
	int					is_dead;
	int					times_ate;
	unsigned long long	last_ate;
	unsigned long long	time_of_death;
	pthread_mutex_t		*left_f;
	pthread_mutex_t		*right_f;
	pthread_t			t_id;
	struct s_info		*info;
}						t_philo;

struct					s_info
{
	unsigned int		n_of_phils;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					n_must_eat;
	unsigned int		phils_done;
	int					g_death;
	struct timeval		era_start;
	pthread_mutex_t		monitor_mx;
	pthread_mutex_t		print_mx;
	pthread_mutex_t		*fork_mxs;
	t_philo				*philos;
};

/* philosephers functions */
int					set_monitoring(t_philo **philos, t_info *info);
int					create_philos(t_philo **phils, t_info *info);
int					philo_eats(t_philo *philo);
void				philo_sleeps(t_philo *philo);
void				philo_thinks(t_philo *philo, unsigned long long	time_left);

/* time and printing functions */
unsigned long long	current_time(t_info *info);
void				printer(char *msg);

/* clean up functions */
void				clean_forks(int n, pthread_mutex_t *forks);

/* libft functions */
size_t				ft_strlen(const char *str);
long				ft_atoi(const char *str);
int					ft_isdigit(int c);

#endif
