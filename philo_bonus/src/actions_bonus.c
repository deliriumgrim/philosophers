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

int	take_forks(t_philo *philo)
{
	if (cond_first_check_time_death(philo) != 1)
		return (0);
	sem_wait(philo->data->sem_forks);
	if (message_status(philo, TAKE_FORK) == 0 || philo->data->num_of_philo == 1)
	{
		sem_post(philo->data->sem_forks);
		return (0);
	}
	sem_wait(philo->data->sem_forks);
	if (message_status(philo, TAKE_FORK) == 0)
	{
		sem_post(philo->data->sem_forks);
		sem_post(philo->data->sem_forks);
		return (0);
	}
	return (1);
}

int	eating(t_philo *philo)
{
	long	time;

	if (cond_first_check_time_death(philo) != 1)
		return (0);
	if (message_status(philo, EATING) == 0)
	{
		sem_post(philo->data->sem_forks);
		sem_post(philo->data->sem_forks);
		return (0);
	}
	sem_wait(philo->data->sem_last_eat);
	philo->last_eat = philo_time();
	sem_post(philo->data->sem_last_eat);
	time = philo_time();
	while (philo_time() < time + philo->data->time_to_eat)
		usleep(SLEEP);
	sem_post(philo->data->sem_forks);
	sem_post(philo->data->sem_forks);
	sem_wait(philo->data->sem_num_eat);
	if (philo->num_eat != -1)
		philo->num_eat++;
	sem_post(philo->data->sem_num_eat);
	return (1);
}

int	philo_sleeping(t_philo *philo)
{
	long	time;

	if (cond_first_check_time_death(philo) != 1)
		return (0);
	if (cond_second_check_time_death(philo))
		return (0);
	if (message_status(philo, SLEEPING) == 0)
		return (0);
	time = philo_time();
	while (philo_time() < time + philo->data->time_to_sleep)
		usleep(SLEEP);
	return (1);
}

int	thinking(t_philo *philo)
{
	long	time;

	if (cond_first_check_time_death(philo) != 1)
		return (0);
	if (cond_second_check_time_death(philo))
		return (0);
	if (message_status(philo, THINKING) == 0)
		return (0);
	if (philo->data->time_to_eat > philo->data->time_to_sleep)
	{
		time = philo_time();
		while (philo_time() < time + \
		philo->data->time_to_eat - philo->data->time_to_sleep)
			usleep(50);
	}
	if (philo->data->num_of_philo % 2)
		usleep(SLEEP);
	return (1);
}
