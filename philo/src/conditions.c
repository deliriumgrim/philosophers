/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   conditions.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drumfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:03:11 by drumfred          #+#    #+#             */
/*   Updated: 2022/02/19 18:03:15 by drumfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	cond_check_time(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->last_eat_m);
	if (philo_time() - philo->last_eat <= philo->data->time_to_die)
	{
		pthread_mutex_unlock(&philo->data->last_eat_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->last_eat_m);
	return (0);
}

int	cond_check_eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->data->num_eat_m);
	if (philo->data->max_eat != -1 && philo->num_eat == philo->data->max_eat)
	{
		pthread_mutex_unlock(&philo->data->num_eat_m);
		return (1);
	}
	else
	{
		pthread_mutex_unlock(&philo->data->num_eat_m);
		return (0);
	}
}

int	cond_check_data_dead(t_philo *philo, int mode)
{
	pthread_mutex_lock(&philo->data->data_dead_m);
	pthread_mutex_lock(&philo->data->num_eat_m);
	if ((mode == 1 && \
	(philo->data->death != 1 && philo->num_eat <= philo->data->max_eat)) || \
	(mode == 2 && \
	(philo->data->max_eat != -1 && philo->num_eat == philo->data->max_eat)))
	{
		pthread_mutex_unlock(&philo->data->num_eat_m);
		pthread_mutex_unlock(&philo->data->data_dead_m);
		return (1);
	}
	pthread_mutex_unlock(&philo->data->num_eat_m);
	pthread_mutex_unlock(&philo->data->data_dead_m);
	return (0);
}
