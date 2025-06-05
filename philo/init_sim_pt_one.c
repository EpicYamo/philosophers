/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   init_sim_pt_one.c                                             :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/29 21:21:34 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/29 21:21:34 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <limits.h>
#include <stdlib.h>

static long long	create_threads(t_philo *philosophers, int philo_count, pthread_t *t_death_monitor);
static long long	join_threads(t_philo *philosophers, int philo_count, pthread_t *t_death_monitor);
static long long	thread_create_error_handler(t_philo *philosophers, long long error_code);

long long	init_simulation(t_philo *philosophers, int philo_count)
{
	long long	error_code;
	pthread_t	*t_death_monitor;

	if (init_sim_flag(philosophers, philo_count) != 0)
		return (LLONG_MAX - 1);
	if (init_philo_mutex(philosophers, philo_count) != 0)
		return (LLONG_MAX - 2);
	if (init_print_mutex(philosophers, philo_count) != 0)
		return (LLONG_MAX - 3);
	if (init_sim_mutex(philosophers, philo_count) != 0)
		return (LLONG_MAX - 4);
	t_death_monitor = malloc(sizeof(t_death_monitor));
	if (!t_death_monitor)
		return (LLONG_MAX - 5);
	error_code = create_threads(philosophers, philo_count, t_death_monitor);
	if (error_code != LLONG_MAX)
	{
		error_code = thread_create_error_handler(philosophers, error_code);
		free(t_death_monitor);
		return (error_code);
	}
	error_code = join_threads(philosophers, philo_count, t_death_monitor);
	free(t_death_monitor);
	return (error_code);
}

static long long	create_threads(t_philo *philosophers, int philo_count, pthread_t *t_death_monitor)
{
	int	i;

	i = -1;
	pthread_mutex_lock(philosophers[0].sim_mutex);
	while (++i < philo_count)
	{
		if (pthread_create(&philosophers[i].philo_thread, NULL, &philo_routine, &philosophers[i]) != 0)
			return (i + 1);
	}
	if (pthread_create(t_death_monitor, NULL, &death_monitor, philosophers) != 0)
		return (LLONG_MAX - 42);
	pthread_mutex_unlock(philosophers[0].sim_mutex);
	return (LLONG_MAX);
}

static long long	join_threads(t_philo *philosophers, int philo_count, pthread_t *t_death_monitor)
{
	int	i;

	i = -1;
	while (++i < philo_count)
	{
		if (pthread_join(philosophers[i].philo_thread, NULL) != 0)
			return (i = -(i + 1));
	}
	pthread_mutex_lock(philosophers[0].sim_mutex);
	*(philosophers[0].sim_flag) = 0;
	pthread_mutex_unlock(philosophers[0].sim_mutex);
	if (pthread_join(*t_death_monitor, NULL) != 0)
		return (LLONG_MIN + 42);
	return (LLONG_MAX);
}

static long long	thread_create_error_handler(t_philo *philosophers, long long error_code)
{
	int	i;

	i = -1;
	*(philosophers[0].sim_flag) = 0;
	pthread_mutex_unlock(philosophers[0].sim_mutex);
	if (error_code != LLONG_MAX - 42)
	{
		while (++i < error_code - 1)
		{
			if (pthread_join(philosophers[i].philo_thread, NULL) != 0)
				return (i = -(i + 1));
		}
	}
	else if (error_code == LLONG_MAX - 42)
	{
		i = -1;
		while (++i < philosophers[0].num_of_philo)
		{
			if (pthread_join(philosophers[i].philo_thread, NULL) != 0)
				return (i = -(i + 1));
		}
	}
	return (error_code);
}
