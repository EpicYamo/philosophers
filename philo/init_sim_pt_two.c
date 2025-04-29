/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   init_sim_pt_two.c                                             :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/29 21:25:07 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/29 21:25:07 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

int	init_sim_flag(t_philo *philosophers, int philo_count)
{
	int	i;
	int	*simulation_flag;

	simulation_flag = malloc(sizeof(int));
	if (!simulation_flag)
		return (1);
	*simulation_flag = 1;
	i = 0;
	while (i < philo_count)
	{
		philosophers[i].sim_flag = simulation_flag;
		i++;
	}
	return (0);
}

int	init_fork_mutex(t_philo *philosophers, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		if (pthread_mutex_init(&philosophers[i].mutex_fork_left, NULL) != 0)
		{
			mutex_destroy_func(philosophers, i - 1, 0);
			return (1);
		}
		i++;
	}
	if (philosophers->num_of_philo == 1)
		philosophers[0].mutex_fork_right = NULL;
	else
	{
		i = 1;
		philosophers[0].mutex_fork_right = &(philosophers[philo_count - 1].mutex_fork_left);
		while (i < philo_count)
		{
			philosophers[i].mutex_fork_right = &(philosophers[i - 1].mutex_fork_left);
			i++;
		}
	}
	return (0);
}

int	init_print_mutex(t_philo *philosophers, int philo_count)
{
	int				i;
	pthread_mutex_t	*print_mutex;

	print_mutex = malloc(sizeof(pthread_mutex_t));
	if (!print_mutex)
		return (1);
	if (pthread_mutex_init(print_mutex, NULL) != 0)
	{
		free(print_mutex);
		return (1);
	}
	i = 0;
	while (i < philo_count)
	{
		philosophers[i].print_mutex = print_mutex;
		i++;
	}
	return (0);
}
