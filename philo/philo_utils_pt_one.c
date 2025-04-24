/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   philo_utils_pt_one.c                                          :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/18 16:28:04 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/18 16:28:04 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

static void	error_message_func(int option, int *flag);
static void	init_philosophers_pt_two(t_philo *philosophers, int philo_count);

int	check_arguments(int argc, char **argv)
{
	int	i;
	int j;
	int	error;

	error = 0;
	if (argc > 6 || argc < 5)
		error_message_func(0, &error);
	if (ft_atoi_mod(argv[1]) < 1)
		error_message_func(1, &error);
	i = 0;
	while (argv[++i])
	{
		j = -1;
		while (argv[i][++j])
		{
			if (((argv[i][j] < '0') && (argv[i][j] != '+'))
				|| ((argv[i][j] > '9') && (argv[i][j] != '+')))
				error_message_func(2, &error);
		}
	}
	if (error != 0)
		return (1);
	return (0);
}

static void	error_message_func(int option, int *flag)
{
	if (option == 0)
	{
		write(2, "Error\nArguments should look like:\n", 34);
		write(2, "number_of_philosophers time_to_die time_to_eat time_to_sleep", 60);
		write(2, " (optional)number_of_times_each_philosopher_must_eat\n", 53);
	}
	if (option == 1)
	{
		write(2, "Error\nFirst Argument Which is", 29);
		write(2, " the <Philosopher Count> Should be above 0\n", 43);
	}
	if (option == 2)
	{
		write(2, "Error\nAll arguments must only contain positive numbers.\n", 56);
	}
	*flag = 1;
}

void	init_philosophers(t_philo *philosophers, char **argv, int philo_count, int argc)
{
	int i;

	i = 0;
	while (i < philo_count)
	{
		philosophers[i].philo_id = i + 1;
		philosophers[i].eating_flag = 0;
		philosophers[i].sleeping_flag = 0;
		philosophers[i].thinking_flag = 0;
		philosophers[i].left_fork = 1;
		philosophers[i].wait_time = 0;
		philosophers[i].dead_flag = 0;
		philosophers[i].num_of_philo = philo_count;
		gettimeofday(&philosophers[i].current_time, NULL);
		philosophers[i].to_die = ft_atoi_mod(argv[2]);
		philosophers[i].to_eat = ft_atoi_mod(argv[3]);
		philosophers[i].to_sleep = ft_atoi_mod(argv[4]);
		if (argc == 6)
			philosophers[i].eat_count = ft_atoi_mod(argv[5]);
		else
			philosophers[i].eat_count = -1;
		i++;
	}
	init_philosophers_pt_two(philosophers, philo_count);
}

static void	init_philosophers_pt_two(t_philo *philosophers, int philo_count)
{
	int	i;

	i = 1;
	if (philo_count != 1)
	{
		philosophers[0].right_fork = &(philosophers[philo_count - 1].left_fork);
		while (i < philo_count)
		{
			philosophers[i].right_fork = &(philosophers[i - 1].left_fork);
			i++;
		}
	}
}
