/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   simulation_pt_one.c                                           :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/24 00:13:53 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/24 00:13:53 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

static int	init_sim_flag(t_philo *philosophers, int philo_count);
static int	init_fork_mutex(t_philo *philosophers, int philo_count);
static int	init_print_mutex(t_philo *philosophers, int philo_count);

long long	init_simulation(t_philo *philosophers, int philo_count)
{
	int	i;

	if (init_sim_flag(philosophers, philo_count) != 0)
		return (LLONG_MAX - 1);
	if (init_fork_mutex(philosophers, philo_count) != 0)
		return (LLONG_MAX - 2);
	if (init_print_mutex(philosophers, philo_count) != 0)
		return (LLONG_MAX - 3);
	i = 0;
	while (i < philo_count)
	{
		if (pthread_create(&philosophers[i].philo_thread, NULL, &philo_routine, &philosophers[i]) != 0)
			return (i);
		i++;
	}
	i = 0;
	while (i < philo_count)
	{
		if (pthread_join(philosophers[i].philo_thread, NULL) != 0)
			return (i *= -1);
		i++;
	}
	return (LLONG_MAX);
}

static int	init_sim_flag(t_philo *philosophers, int philo_count)
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

static int	init_fork_mutex(t_philo *philosophers, int philo_count)
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

static int	init_print_mutex(t_philo *philosophers, int philo_count)
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
