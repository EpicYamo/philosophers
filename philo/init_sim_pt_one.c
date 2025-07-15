/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_sim_pt_one.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:47:53 by aaycan            #+#    #+#             */
/*   Updated: 2025/07/07 20:40:02 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <limits.h>

static long long	create_threads(t_philo *philosophers, int philo_count);
static long long	join_threads(t_philo *philosophers, int philo_count);
static long long	thread_create_error_handler(t_philo *philosophers,
						long long error_code);

long long	init_simulation(t_philo *philosophers, int philo_count)
{
	long long	error_code;

	if (init_sim_flag(philosophers, philo_count) != 0)
		return (LLONG_MAX - 1);
	if (init_philo_mutex(philosophers, philo_count) != 0)
		return (LLONG_MAX - 2);
	if (init_print_mutex(philosophers, philo_count) != 0)
		return (LLONG_MAX - 3);
	if (init_sim_mutex(philosophers, philo_count) != 0)
		return (LLONG_MAX - 4);
	error_code = create_threads(philosophers, philo_count);
	if (error_code != LLONG_MAX)
	{
		error_code = thread_create_error_handler(philosophers, error_code);
		return (error_code);
	}
	error_code = join_threads(philosophers, philo_count);
	return (error_code);
}

static long long	create_threads(t_philo *philosophers, int philo_count)
{
	int	i;

	i = -1;
	pthread_mutex_lock(philosophers[0].sim_mutex);
	while (++i < philo_count)
	{
		if (pthread_create(&philosophers[i].philo_thread, NULL, &philo_routine,
				&philosophers[i]) != 0)
			return (i + 1);
	}
	pthread_mutex_unlock(philosophers[0].sim_mutex);
	return (LLONG_MAX);
}

static long long	join_threads(t_philo *philosophers, int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
	{
		if (pthread_join(philosophers[i].philo_thread, NULL) != 0)
			return (i = -(i + 1));
	}
	return (LLONG_MAX);
}

static long long	thread_create_error_handler(t_philo *philosophers,
	long long error_code)
{
	int	i;

	i = -1;
	*(philosophers[0].sim_flag) = 0;
	pthread_mutex_unlock(philosophers[0].sim_mutex);
	while (++i < error_code - 1)
	{
		if (pthread_join(philosophers[i].philo_thread, NULL) != 0)
			return (i = -(i + 1));
	}
	return (error_code);
}
