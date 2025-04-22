/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   thread_and_routine.c                                          :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/18 16:27:21 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/18 16:27:21 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <unistd.h>

static long long	init_mutex_func(t_philo *philosophers, int philo_count);
static void			*philo_routine(void *philosopherso);

long long	init_process(t_philo *philosophers, int philo_count)
{
	int	i;

	if (init_mutex_func(philosophers, philo_count) != 0)
		return (LONG_LONG_MAX);
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
	mutex_destroy_func(philosophers, philo_count);
	return (LONG_LONG_MAX - 1);
}

static long long	init_mutex_func(t_philo *philosophers, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		if (pthread_mutex_init(&philosophers[i].mutex_fork, NULL) != 0)
		{
			mutex_destroy_func(philosophers, i - 1);
			return (LONG_LONG_MAX);
		}
		i++;
	}
	return (0);
}

static void	*philo_routine(void *philosopherso)
{
	t_philo *philosophers = philosopherso;
	while (philosophers->dead_flag == 0)
	{
		if (waitress_function(philosophers))
		{
																
		}
	}
}
