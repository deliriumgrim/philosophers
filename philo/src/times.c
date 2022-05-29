/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   times.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drumfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:03:11 by drumfred          #+#    #+#             */
/*   Updated: 2022/02/19 18:03:15 by drumfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	philo_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

int	wait_to_time(t_philo *phl, long sleep_to_time_ms)
{
	long	start;
	long	now;

	start = phl->data->time_start;
	now = philo_time();
	while (now < start + sleep_to_time_ms)
	{
		usleep(50);
		now = philo_time();
	}
	return (0);
}

int	wait_start(t_philo *philo)
{
	long	first;
	long	second;
	long	third;

	first = START_MS;
	second = START_MS + philo->data->time_to_eat;
	third = START_MS * 2 + philo->data->time_to_eat;
	if (philo->data->num_of_philo == 1)
		wait_to_time(philo, first);
	else if (philo->id % 2 == 0)
		wait_to_time(philo, second);
	else
	{
		if (philo->data->num_of_philo % 2 == 0)
			wait_to_time(philo, first);
		else
		{
			if (philo->id == philo->data->num_of_philo)
				wait_to_time(philo, third);
			else
				wait_to_time(philo, first);
		}
	}
	return (0);
}
