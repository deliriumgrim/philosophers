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

long	philo_time(void)
{
	struct timeval	t;

	gettimeofday(&t, NULL);
	return ((t.tv_sec * 1000) + (t.tv_usec / 1000));
}

void	wait_time(t_philo *philo, long time)
{
	long	start;
	long	now;

	start = philo->data->time_start;
	now = philo_time();
	while (now < start + time)
	{
		usleep(SLEEP);
		now = philo_time();
	}
}

void	wait_start(t_philo *philo)
{
	long	first;
	long	second;
	long	third;

	first = START_MS;
	second = START_MS + philo->data->time_to_eat;
	third = START_MS * 2 + philo->data->time_to_eat;
	if (philo->data->num_of_philo == 1)
		wait_time(philo, first);
	else if (philo->id % 2 == 0)
		wait_time(philo, second);
	else
	{
		if (philo->data->num_of_philo % 2 == 0)
			wait_time(philo, first);
		else
		{
			if (philo->id == philo->data->num_of_philo)
				wait_time(philo, third);
			else
				wait_time(philo, first);
		}
	}
}
