/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers_utils_pt_one.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan < aaycan@student.42kocaeli.com.t    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 21:21:31 by aaycan            #+#    #+#             */
/*   Updated: 2025/04/15 21:21:31 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>

static int	init_allocation(t_philo *philosophers);

int	check_arguments(int argc, char **argv)
{
	int	i;
	int j;

	if (argc != 6)
	{
		write(2, "Error\nArguments should look like:\n", 34);
		write(2, "number_of_philosophers time_to_die time_to_eat time_to_sleep", 60);
		write(2, " number_of_times_each_philosopher_must_eat\n", 43);
		return (1);
	}
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (((argv[i][j] < '0') && (argv[i][j] != '+'))
				|| ((argv[i][j] > '9') && (argv[i][j] != '+')))
			{
				write(2, "All arguments must only contain positive numbers.\n", 50);
				return (1);
			}
		}
	}
	return (0);
}

int	init_philosophers(t_philo *philosophers, char **argv)
{
	int i;

	philosophers->num_of_philo = ft_atoi_mod(argv[1]);
	philosophers->to_die = ft_atoi_mod(argv[2]);
	philosophers->to_eat = ft_atoi_mod(argv[3]);
	philosophers->to_sleep = ft_atoi_mod(argv[4]);
	philosophers->eat_count = ft_atoi_mod(argv[5]);
	philosophers->test_counter = 0;
	if (init_allocation(philosophers) != 0)
	{
		write(2, "Malloc Error\n", 13);
		return (1);
	}
	i = philosophers->num_of_philo;
	while (i)
	{
		
		philosophers->philo_id[i - 1] = i;
		philosophers->dead[i - 1] = 0;
		philosophers->time_left[i - 1] = philosophers->to_die;
		philosophers->wait_time[i - 1] = 0;
		i--;
	}
	return (0);
}

static int	init_allocation(t_philo *philosophers)
{
	philosophers->philo_id = malloc(sizeof(int) * philosophers->num_of_philo);
	if (!philosophers->philo_id)
		return (1);
	philosophers->dead = malloc(sizeof(int) * philosophers->num_of_philo);
	if (!philosophers->dead)
	{
		free(philosophers->philo_id);
		return (1);
	}
	philosophers->time_left = malloc(sizeof(int) * philosophers->num_of_philo);
	if (!philosophers->time_left)
	{
		free(philosophers->philo_id);
		free(philosophers->dead);
		return (1);
	}
	philosophers->wait_time = malloc(sizeof(int) * philosophers->num_of_philo);
	if (!philosophers->wait_time)
	{
		free(philosophers->philo_id);
		free(philosophers->dead);
		free(philosophers->time_left);
		return (1);
	}
	return (0);
}
