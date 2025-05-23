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

static long long	create_threads(t_philo *philosophers, int philo_count, t_monitors *philo_monitors);
static long long	join_threads(t_philo *philosophers, int philo_count, t_monitors *philo_monitors);

long long	init_simulation(t_philo *philosophers, int philo_count)
{
	long long	error_code;
	t_monitors	*philo_monitors;

	if (init_sim_flag(philosophers, philo_count) != 0)
		return (LLONG_MAX - 1);
	if (init_philo_mutex(philosophers, philo_count) != 0)
		return (LLONG_MAX - 2);
	if (init_print_mutex(philosophers, philo_count) != 0)
		return (LLONG_MAX - 3);
	if (init_sim_mutex(philosophers, philo_count) != 0)
		return (LLONG_MAX - 4);
	philo_monitors = malloc(sizeof(t_monitors));
	if (!philo_monitors)
		return (LLONG_MAX - 5);
	error_code = create_threads(philosophers, philo_count, philo_monitors);
	if (error_code != LLONG_MAX)
	{
		free(philo_monitors);
		return (error_code);
	}
	error_code = join_threads(philosophers, philo_count, philo_monitors);
	free(philo_monitors);
	return (error_code);
}

static long long	create_threads(t_philo *philosophers, int philo_count, t_monitors *philo_monitors)
{
	int	i;

	i = -1;
	while (++i < philo_count)
	{
		if (pthread_create(&philosophers[i].philo_thread, NULL, &philo_routine, &philosophers[i]) != 0)
			return (i);
	}
	if (pthread_create(&philo_monitors->t_death_monitor, NULL, &death_monitor, philosophers) != 0)
		return (42);
	if (philosophers[0].num_of_philo % 2 == 1)
	{
		if (pthread_create(&philo_monitors->t_eat_perm_monitor, NULL, &eat_perm_monitor, philosophers) != 0)
			return (42);
	}
	return (LLONG_MAX);
}

static long long	join_threads(t_philo *philosophers, int philo_count, t_monitors *philo_monitors)
{
	int	i;

	i = -1;
	while (++i < philo_count)
	{
		if (pthread_join(philosophers[i].philo_thread, NULL) != 0)
			return (i *= -1);
	}
	pthread_mutex_lock(philosophers[0].sim_mutex);
	philosophers[0].sim_flag = 0;
	pthread_mutex_unlock(philosophers[0].sim_mutex);
	if (pthread_join(philo_monitors->t_death_monitor, NULL) != 0)
		return (-42);
	if (philosophers[0].num_of_philo % 2 == 1)
	{
		if (pthread_join(philo_monitors->t_eat_perm_monitor, NULL) != 0)
			return (-42);
	}
	return (LLONG_MAX);
}
