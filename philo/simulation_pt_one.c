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
static int	init_mutex_func(t_philo *philosophers, int philo_count);
static void	*philo_routine(void *philosopherso);
static void	alone_philosopher(t_philo *philosopher);

long long	init_simulation(t_philo *philosophers, int philo_count)
{
	int	i;

	if (init_sim_flag(philosophers, philo_count) != 0)
		return (LLONG_MAX - 1);
	if (init_mutex_func(philosophers, philo_count) != 0)
		return (LLONG_MAX - 2);
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

static int	init_mutex_func(t_philo *philosophers, int philo_count)
{
	int	i;

	i = 0;
	while (i < philo_count)
	{
		if (pthread_mutex_init(&philosophers[i].mutex_fork, NULL) != 0)
		{
			mutex_destroy_func(philosophers, i - 1);
			return (1);
		}
		i++;
	}
	return (0);
}

static void	*philo_routine(void *philosopherso)
{
	t_philo *philosophers;

	philosophers = philosopherso;
	if (philosophers->num_of_philo == 1)
		alone_philosopher(philosophers);
	if (philosophers->eat_count == -1)
	{
		while (philosophers->dead_flag == 0 && *philosophers->sim_flag == 1)
		{
			//mutex lock both forks
			if (philosophers->right_fork == 1 && philosophers->left_fork == 1);
			//eat
			//else; think until you can eat again. while(right_fork == 0 || left_fort == 0){}
			//sleep right after eating and repeat.
			//mutex unlock both forks
		}
	}
	else if (philosophers->eat_count != -1)
	{
		;
	}
	if (philosophers->dead_flag == 1)
		*philosophers->sim_flag = 0;
}

static void alone_philosopher(t_philo *philosopher)
{
	gettimeofday(&philosopher->current_time, NULL);
	printf("%ld %d is thinking\n", philosopher->current_time.tv_usec, philosopher->philo_id);
	usleep(philosopher->to_die * 1000);
	gettimeofday(&philosopher->current_time, NULL);
	philosopher->dead_flag = 1;
	*philosopher->sim_flag = 0;
	printf("%ld %d died\n", philosopher->current_time.tv_usec, philosopher->philo_id);
}
