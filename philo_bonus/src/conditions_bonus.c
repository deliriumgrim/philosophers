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

int	cond_first_check_time_death(t_philo *philo)
{
	sem_wait(philo->data->sem_last_eat);
	if (philo_time() - philo->last_eat < philo->data->time_to_die)
	{
		sem_post(philo->data->sem_last_eat);
		return (1);
	}
	sem_post(philo->data->sem_last_eat);
	return (0);
}

int	cond_second_check_time_death(t_philo *philo)
{
	sem_wait(philo->data->sem_num_eat);
	if (philo->data->max_eat != -1 && philo->num_eat == philo->data->max_eat)
	{
		sem_post(philo->data->sem_num_eat);
		return (1);
	}
	sem_post(philo->data->sem_num_eat);
	return (0);
}

int	cond_third_check_time_death(t_philo *philo)
{
	sem_wait(philo->data->sem_last_eat);
	if (philo_time() - philo->last_eat - philo->data->time_to_die \
	< DELAY_DEATH_MS)
	{
		sem_post(philo->data->sem_last_eat);
		return (1);
	}
	sem_post(philo->data->sem_last_eat);
	return (0);
}

int	cond_philo_live(t_philo *philo, int mode)
{
	sem_wait(philo->data->sem_num_eat);
	if ((mode == 1 && \
	(cond_first_check_time_death(philo) \
	&& philo->num_eat <= philo->data->max_eat)) || \
	(mode == 2 && \
	(philo->data->max_eat != -1 && philo->num_eat >= philo->data->max_eat)))
	{
		sem_post(philo->data->sem_num_eat);
		return (1);
	}
	sem_post(philo->data->sem_num_eat);
	return (0);
}
