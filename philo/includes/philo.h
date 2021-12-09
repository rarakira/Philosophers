/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbaela <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 11:58:35 by lbaela            #+#    #+#             */
/*   Updated: 2021/12/09 18:10:04 by lbaela           ###   ########.fr       */
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
# include <string.h>

# define BUFFSIZE		50
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

# define CFORK			(GREEN "has taken a fork\e[0m\n")
# define CEATING		(YELL "is eating\e[0m\n")
# define CSLEEPING		(BLUE "is sleeping\e[0m\n")
# define CTHINKING		(VIOLT "is thinking\e[0m\n")
# define CDEATH			(RED "is dead\e[0m\n")

# define LEN_FORK		28
# define LEN_EATING		21
# define LEN_SLEEPING	23
# define LEN_THINKING	23
# define LEN_DEATH		19

typedef struct s_info	t_info;

typedef struct s_fork	t_fork;

typedef struct s_philo
{
	int					name;
	int					is_dead;
	int					leftie;
	unsigned int		times_ate;
	unsigned long long	current;
	unsigned long long	last_ate;
	unsigned long long	time_of_death;
	t_fork				*left_f;
	t_fork				*right_f;
	pthread_t			t_id;
	struct s_info		*info;
}						t_philo;

struct s_fork
{
	int					is_avail;
	pthread_mutex_t		mx;
};

struct					s_info
{
	unsigned int		n_of_phils;
	unsigned int		time_to_die;
	unsigned int		time_to_eat;
	unsigned int		time_to_sleep;
	unsigned int		n_must_eat;
	unsigned int		phils_done;
	int					feast_ended;
	struct timeval		era_start;
	pthread_mutex_t		monitor_mx;
	pthread_mutex_t		print_mx;
	t_fork				*forks;
	t_philo				*philos;
};

/* philosophers functions */
int					set_monitoring(t_philo **philos, t_info *info);
int					init_philos(t_philo **philos, t_info *info);
int					create_forks(t_fork **forks, t_info *info);
int					create_philos(t_philo **phils, t_info *info);

int					philo_eats(t_philo *philo);
int					philo_sleeps(t_philo *philo);
int					philo_thinks(t_philo *philo);

int					done_eating(t_philo *philo);
int					still_alife(t_philo *philo);
int					set_philo_dead(t_philo *philo);

/* time and printing functions */
unsigned long long	current_time(t_info *info);
void				ft_sleep(unsigned long long wake_time, t_info *info);

void				end_feast(t_info *info);
int					feast_lasts(t_info *info);

int					printer(t_philo *philo, unsigned long long time,
						char *msg, int len);
int					print_death(t_philo *philo, unsigned long long time,
						char *msg, int len);

/* clean up functions */
void				clean_f_mxs(int n, t_fork *obj);
void				clean_all(t_info *info);

/* libft functions */
size_t				ft_strlen(const char *str);
long				ft_atoi(const char *str);
int					ft_isdigit(int c);

#endif
