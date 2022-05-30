/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drumfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:03:11 by drumfred          #+#    #+#             */
/*   Updated: 2022/02/19 18:03:15 by drumfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "include/philo.h"

void	*check_time_death(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	while (cond_check_time(philo))
	{
		if (cond_check_eat(philo))
			return (NULL);
		usleep(SLEEP);
	}
	pthread_mutex_lock(&philo->data->data_dead_m);
	if (philo->data->death != 1)
	{
		philo->data->death = 1;
		printf("%lu %d %s", philo_time() - philo->data->time_start - START_MS, \
		philo->id, DIED);
	}
	pthread_mutex_unlock(&philo->data->data_dead_m);
	return (NULL);
}

void	*philo_live(void *arg)
{
	t_philo		*philo;
	pthread_t	death_t;

	philo = (t_philo *)arg;
	wait_start(philo);
	if (pthread_create(&death_t, NULL, check_time_death, philo))
		return (NULL);
	while (cond_check_data_dead(philo, 1))
	{
		if (cond_check_data_dead(philo, 2))
			break ;
		if (take_forks(philo) == 0)
			break ;
		if (eat(philo) == 0)
			break ;
		if (cond_check_data_dead(philo, 2))
			break ;
		if (philo_sleep(philo) == 0)
			break ;
		if (thinking(philo) == 0)
			break ;
	}
	pthread_join(death_t, NULL);
	return (NULL);
}

int	main(int argc, char **argv)
{
	t_data	data;
	t_philo	*philo;

	if (!validation(&argv[1]))
		return (0);
	init_data(&data, argc, argv);
	if (!init_forks(&data))
		return (0);
	if (!init_philo(&data, &philo))
		return (0);
	join_thread(&data);
	cleaner(&data, philo);
	return (0);
}
