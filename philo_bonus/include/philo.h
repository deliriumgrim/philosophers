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

# include <string.h>
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <semaphore.h>
# include <fcntl.h>

# define TAKE_FORK "has taken a fork\n"
# define EATING "is eating\n"
# define SLEEPING "is sleeping\n"
# define THINKING "is thinking\n"
# define DIED "died\n"
# define START_MS 60
# define SLEEP 250

typedef struct s_data
{
	int				num_of_philo;
	long			time_to_die;
	long			time_to_eat;
	long			time_to_sleep;
	long			time_start;
	int				max_eat;
	sem_t			*sem_forks;
	sem_t			*sem_last_eat;
	sem_t			*sem_num_eat;
	sem_t			*sem_print;
	pid_t			*arr_pid;
	pthread_t 		*philo_thread;
}	t_data;

typedef struct s_philo
{
	t_data			*data;
	int				id;
	long			last_eat;
	int				num_eat;
}	t_philo;

int	validation(char **argv);
int	ft_atoi(const char *str);
int	init_data(t_data *data, int argc, char **argv);
long	philo_time(void);
int ft_exit(t_data *data, int mode, char *str_err);
void	init_forks(t_data *data);
void *ft_waitpid(void *arg);
void	init_philo(t_data *data);
t_philo init_philo_struct(t_data *data, int id);
void	wait_start(t_philo *philo);
int message(t_philo *philo, char *str);
void	philo_live(t_data * data, int id);
int take_forks(t_philo *philo);
int	eating(t_philo *philo);
int	philo_sleeping(t_philo *philo);
int message_status(t_philo *philo, char *str);
int thinking(t_philo *philo);

int cond_first_check_time_death(t_philo *philo);
int cond_second_check_time_death(t_philo *philo);
int cond_third_check_time_death(t_philo *philo);
int	cond_philo_live(t_philo *philo, int mode);

#endif