/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   inits.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drumfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:03:11 by drumfred          #+#    #+#             */
/*   Updated: 2022/02/19 18:03:15 by drumfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

t_philo	*init_philo_struct(t_data *data)
{
	t_philo	*philo;
	int		i;

	philo = malloc(sizeof(t_philo) * data->num_of_philo);
	if (!philo)
		return (NULL);
	i = 0;
	while (++i <= data->num_of_philo)
	{
		philo[i - 1].id = i;
		philo[i - 1].data = data;
		philo[i - 1].last_eat = 0;
		if (data->max_eat != -1)
			philo[i - 1].num_eat = 0;
		else
			philo[i - 1].num_eat = -1;
		philo[i - 1].r_fork = i;
		philo[i - 1].l_fork = get_l_fork(i, data);
		philo[i - 1].max_fork = get_max_fork(&philo[i - 1]);
		philo[i - 1].min_fork = get_min_fork(&philo[i - 1]);
		philo[i - 1].last_eat = data->time_start + START_MS;
	}
	return (philo);
}

int	init_philo(t_data *data, t_philo **philo)
{
	int	i;

	*philo = init_philo_struct(data);
	if (*philo == NULL)
		return (0);
	data->philo_t = malloc(sizeof(pthread_t) * data->num_of_philo);
	if (!data->philo_t)
		return (errors(4));
	i = -1;
	while (++i < data->num_of_philo)
	{
		if (pthread_create(&data->philo_t[i], NULL, philo_live, &(*philo)[i]))
			return (0);
	}
	return (1);
}

int	mutex_init(t_data *data)
{
	int	i;

	if (pthread_mutex_init(&data->last_eat_m, NULL))
		return (errors(3));
	if (pthread_mutex_init(&data->data_dead_m, NULL))
		return (errors(3));
	if (pthread_mutex_init(&data->num_eat_m, NULL))
		return (errors(3));
	i = 0;
	while (i < data->num_of_philo)
	{
		if (pthread_mutex_init(&data->forks[i++], NULL))
			return (errors(3));
	}
	return (1);
}

int	init_forks(t_data *data)
{
	data->forks = malloc(sizeof(pthread_mutex_t) * data->num_of_philo);
	if (!data->forks)
		return (errors(4));
	data->time_start = philo_time();
	if (!mutex_init(data))
		return (0);
	return (1);
}

int	init_data(t_data *data, int argc, char **argv)
{
	data->death = 0;
	data->max_eat = -1;
	data->time_start = 0;
	data->num_of_philo = ft_atoi(argv[1]);
	data->time_to_die = ft_atoi(argv[2]);
	data->time_to_eat = ft_atoi(argv[3]);
	data->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		data->max_eat = ft_atoi(argv[5]);
	return (1);
}
