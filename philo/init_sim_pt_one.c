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
#include <pthread.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

static long long	init_simulation_pt_two(t_philo *philosophers, int philo_count);

long long	init_simulation(t_philo *philosophers, int philo_count)
{
	long long		i;
	pthread_t		monitor_thread;

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
	if (pthread_create(&monitor_thread, NULL, &monitor, philosophers) != 0)
		return (42);
	i = init_simulation_pt_two(philosophers, philo_count);
	if (i != LLONG_MAX)
		return (i);
	if (pthread_join(monitor_thread, NULL) != 0)
		return (-42);
	return (LLONG_MAX);
}

static long long	init_simulation_pt_two(t_philo *philosophers, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		if (pthread_join(philosophers[i].philo_thread, NULL) != 0)
			return (i *= -1);
		i++;
	}
	return (LLONG_MAX);
}
