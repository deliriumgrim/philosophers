/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: drumfred <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/19 18:03:11 by drumfred          #+#    #+#             */
/*   Updated: 2022/02/19 18:03:15 by drumfred         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

int	ft_atoi(const char *str)
{
	long int	output;

	output = 0;
	while (*str && (*str == ' ' || *str == '\n' || *str == '\t' \
		|| *str == '\v' || *str == '\f' || *str == '\r'))
		++str;
	while (*str)
	{
		if (*str < '0' || *str > '9')
			return (-1);
		if (output > INT_MAX)
			return (-1);
		output = (output * 10) + (*str - 48);
		++str;
	}
	return (output);
}

int	errors(int flag)
{
	if (flag == 1)
	{
		printf("params of program should be only integer and > 1\n");
		return (0);
	}
	else if (flag == 2)
	{
		printf("numbers of params < 5 or > 6\n");
		return (0);
	}
	else if (flag == 3)
	{
		printf("error mutex init\n");
		return (0);
	}
	else if (flag == 4)
	{
		printf("malloc failed\n");
		return (0);
	}
	return (1);
}

int	validation(char **argv)
{
	int	i;

	i = 0;
	while (argv[i])
	{
		if (ft_atoi(argv[i]) <= 0)
			return (errors(1));
		i++;
	}
	if (i < 4 || i > 5)
		return (errors(2));
	return (1);
}
