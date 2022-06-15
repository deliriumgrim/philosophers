/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drumfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:03:11 by drumfred          #+#    #+#             */
/*   Updated: 2022/02/19 18:03:15 by drumfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>

# ifndef CONSTANT
#  define CONSTANT
#  define TAKE_FORK "has taken a fork\n"
#  define EATING "is eating\n"
#  define SLEEPING "is sleeping\n"
#  define THINKING "is thinking\n"
#  define DIED "died\n"
#  define START_MS 10
#  define DELAY_MS 10
#  define SLEEP 250
# endif

typedef struct s_data
{
	int				num_of_philo;
	int				death;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_start;
	int				max_eat;
	pthread_t		*philo_t;
	pthread_mutex_t	*forks;
	pthread_mutex_t	last_eat_m;
	pthread_mutex_t	data_dead_m;
	pthread_mutex_t	num_eat_m;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	long			last_eat;
	int				num_eat;
	int				l_fork;
	int				r_fork;
	int				max_fork;
	int				min_fork;
}	t_philo;

int		validation(char **argv);
int		ft_atoi(const char *str);
int		errors(int flag);
int		init_data(t_data *data, int argc, char **argv);
long	philo_time(void);
int		init_forks(t_data *data);
int		init_philo(t_data *data, t_philo **arg);
int		wait_start(t_philo *philo);
int		get_l_fork(int i, t_data *data);
int		get_max_fork(t_philo *philo);
int		get_min_fork(t_philo *philo);
void	*philo_live(void *arg);
int		cond_check_time(t_philo *philo);
int		cond_check_eat(t_philo *philo);
int		cond_check_data_dead(t_philo *philo, int mode);
int		write_status(t_philo *philo, char *str);
int		take_forks(t_philo *philo);
int		eat(t_philo *philo);
int		philo_sleep(t_philo *philo);
int		thinking(t_philo *philo);
void	join_thread(t_data *data);
void	cleaner(t_data *data, t_philo *philo);
#endif
