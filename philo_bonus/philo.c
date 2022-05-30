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
#include "include/philo.h"

void	*check_time_death(void *arg)
{
	t_philo	*philo;
	long	time;

	philo = (t_philo *)arg;
	while (cond_first_check_time_death(philo))
	{
		if (cond_second_check_time_death(philo))
			return (NULL);
	}
	sem_wait(philo->data->sem_print);
	if (cond_third_check_time_death(philo))
	{
		message(philo, DIED);
		time = philo_time();
		while (philo_time() < time + philo->data->time_to_die)
			usleep(SLEEP);
	}
	sem_post(philo->data->sem_print);
	return (NULL);
}

void	philo_live(t_data *data, int id)
{
	t_philo		philo;
	pthread_t	death_t;

	philo = init_philo_struct(data, id);
	wait_start(&philo);
	if (pthread_create(&death_t, NULL, check_time_death, &philo))
		exit(ft_exit(data, 2, "Error pthread_create\n"));
	while (cond_philo_live(&philo, 1))
	{
		if (cond_philo_live(&philo, 2))
			break ;
		if (take_forks(&philo) == 0)
			break ;
		if (eating(&philo) == 0)
			break ;
		if (philo_sleeping(&philo) == 0)
			break ;
		if (thinking(&philo) == 0)
			break ;
		if (cond_philo_live(&philo, 2))
			break ;
	}
	pthread_join(death_t, NULL);
	exit(ft_exit(data, 3, ""));
}

int	main(int argc, char **argv)
{
	t_data	data;

	if (!validation(&argv[1]))
		return (0);
	init_data(&data, argc, argv);
	init_forks(&data);
	init_philo(&data);
	ft_exit(&data, 3, "");
	return (0);
}
