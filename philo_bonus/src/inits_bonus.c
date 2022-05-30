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
#include "../include/philo_bonus.h"

t_philo	init_philo_struct(t_data *data, int id)
{
	t_philo	philo;

	philo.id = id;
	philo.data = data;
	if (data->max_eat != -1)
		philo.num_eat = 0;
	else
		philo.num_eat = -1;
	philo.last_eat = data->time_start + START_MS;
	return (philo);
}

void	init_forks(t_data *data)
{
	sem_unlink("/forks");
	sem_unlink("/last_eat");
	sem_unlink("/num_eat");
	sem_unlink("/print");
	data->sem_forks = sem_open("/forks", O_CREAT | O_EXCL, \
	0777, data->num_of_philo);
	data->sem_last_eat = sem_open("/last_eat", O_CREAT | O_EXCL, 0777, 1);
	data->sem_num_eat = sem_open("/num_eat", O_CREAT | O_EXCL, 0777, 1);
	data->sem_print = sem_open("/print", O_CREAT | O_EXCL, 0777, 1);
	if (data->sem_forks == SEM_FAILED)
		exit(ft_exit(data, 1, "Error sem_open\n"));
	if (data->sem_last_eat == SEM_FAILED)
		exit(ft_exit(data, 1, "Error sem_open\n"));
	if (data->sem_num_eat == SEM_FAILED)
		exit(ft_exit(data, 1, "Error sem_open\n"));
	if (data->sem_print == SEM_FAILED)
		exit(ft_exit(data, 1, "Error sem_open\n"));
	data->time_start = philo_time();
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->max_eat = -1;
	data->time_start = 0;
	data->sem_forks = NULL;
	data->arr_pid = NULL;
	data->philo_thread = NULL;
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	return (1);
}

void	init_wait_pthread(t_data *data)
{
	int	i;

	data->philo_thread = malloc(sizeof(pthread_t) * data->num_of_philo);
	if (data->philo_thread == NULL)
		exit(ft_exit(data, 2, "Error malloc\n"));
	i = 0;
	while (i < data->num_of_philo)
	{
		if (!pthread_create(&data->philo_thread[i], NULL, \
		ft_waitpid, &(data->arr_pid[i])))
							i++;
		else
		{
			free(data->philo_thread);
			exit(ft_exit(data, 2, "Error pthread_create\n"));
		}
	}
	i = 0;
	while (i < data->num_of_philo)
	{
		pthread_join(data->philo_thread[i], NULL);
		i++;
	}
	free(data->philo_thread);
}

void	init_philo(t_data *data)
{
	int		i;
	pid_t	pid;

	data->arr_pid = malloc(sizeof(int) * data->num_of_philo);
	if (data->arr_pid == NULL)
		exit(ft_exit(data, 1, "Error malloc failed\n"));
	i = -1;
	pid = 1;
	while (++i < data->num_of_philo)
	{
		if (pid != 0)
		{
			pid = fork();
			if (pid == -1)
				exit(ft_exit(data, 2, "Error fork\n"));
			if (pid != 0)
				data->arr_pid[i] = pid;
			if (pid == 0)
				philo_live(data, i + 1);
		}
	}
	init_wait_pthread(data);
}
