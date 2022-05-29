/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   actions.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drumfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:03:11 by drumfred          #+#    #+#             */
/*   Updated: 2022/02/19 18:03:15 by drumfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	check_death_m(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->data_dead_m);
	if (philo->data->death == 1)
	{
		pthread_mutex_unlock(&philo->data->data_dead_m);
		return (0);
	}
	return (1);
}

int	take_forks(t_philo *philo)
{
	if (check_death_m(philo) == 0)
		return (0);
	pthread_mutex_unlock(&philo->data->data_dead_m);
	pthread_mutex_lock(&philo->data->forks[philo->min_fork]);
	if (write_status(philo, TAKE_FORK) == 0 || philo->data->num_of_philo == 1)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->data->forks[philo->max_fork]);
	if (write_status(philo, TAKE_FORK) == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->max_fork]);
		return (0);
	}
	return (1);
}

int	eat(t_philo *philo)
{
	long	time;

	if (check_death_m(philo) == 0)
		return (0);
	pthread_mutex_unlock(&philo->data->data_dead_m);
	if (write_status(philo, EATING) == 0)
	{
		pthread_mutex_unlock(&philo->data->forks[philo->max_fork]);
		pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
		return (0);
	}
	pthread_mutex_lock(&philo->data->last_eat_m);
	philo->last_eat = philo_time();
	pthread_mutex_unlock(&philo->data->last_eat_m);
	time = philo_time();
	while (philo_time() < time + philo->data->time_to_eat)
		usleep(50);
	pthread_mutex_unlock(&philo->data->forks[philo->max_fork]);
	pthread_mutex_unlock(&philo->data->forks[philo->min_fork]);
	pthread_mutex_lock(&philo->data->num_eat_m);
	if (philo->num_eat != -1)
		philo->num_eat++;
	pthread_mutex_unlock(&philo->data->num_eat_m);
	return (1);
}

int	philo_sleep(t_philo *philo)
{
	long	time;

	if (check_death_m(philo) == 0)
		return (0);
	pthread_mutex_unlock(&philo->data->data_dead_m);
	if (write_status(philo, SLEEPING) == 0)
		return (0);
	time = philo_time();
	while (philo_time() < time + philo->data->time_to_sleep)
		usleep(50);
	return (1);
}

int	thinking(t_philo *philo)
{
	long	time;

	if (check_death_m(philo) == 0)
		return (0);
	pthread_mutex_unlock(&philo->data->data_dead_m);
	if (write_status(philo, THINKING) == 0)
		return (0);
	if (philo->data->time_to_eat > philo->data->time_to_sleep)
	{
		time = philo_time();
		while (philo_time() < time + philo->data->time_to_eat - philo->data->time_to_sleep)
			usleep(50);
	}
	if (philo->data->num_of_philo % 2)
	{
		time = philo_time();
		while (philo_time() < time + DELAY_MS)
			usleep(50);
	}
	return (1);
}
