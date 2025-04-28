/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   simulation_pt_two.c                                           :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/24 00:13:20 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/24 00:13:20 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

static long long	get_timestamp_in_ms(struct timeval start_time);
static void			print_message(t_philo *philo, char *message);

void	*philo_routine(void *philosopher)
{
	t_philo		*philo;
	long long	last_meal;

	philo = (t_philo *)philosopher;
	last_meal = get_timestamp_in_ms(philo->start_time);
	if (philo->num_of_philo == 1)
	{
		pthread_mutex_lock(&philo->mutex_fork_left);
		print_message(philo, "has taken a fork");
		usleep(philo->to_die * 1000);
		pthread_mutex_unlock(&philo->mutex_fork_left);
		print_message(philo, "died");
		*(philo->sim_flag) = 0;
		return (NULL);
	}
	while (*(philo->sim_flag) == 1 && philo->dead_flag == 0)
	{
		if (get_timestamp_in_ms(philo->start_time) - last_meal >= philo->to_die)
		{
			print_message(philo, "died");
			*(philo->sim_flag) = 0;
			break;
		}
		// deadlock fix it
		while (1)
		{
			if (pthread_mutex_trylock(&philo->mutex_fork_left) == 0)
			{
				print_message(philo, "has taken the left fork");
				if (pthread_mutex_trylock(philo->mutex_fork_right) != 0)
				{
					pthread_mutex_unlock(&philo->mutex_fork_left);
					print_message(philo, "has left the left fork");
				}
				else
				{
					print_message(philo, "has taken the right fork");
					break;
				}
			}
		}
		// deadlock poor fix ;) fix it
		if (get_timestamp_in_ms(philo->start_time) - last_meal >= philo->to_die)
		{
			print_message(philo, "died");
			pthread_mutex_unlock(&philo->mutex_fork_left);
			pthread_mutex_unlock(philo->mutex_fork_right);
			*(philo->sim_flag) = 0;
			break;
		}
		print_message(philo, "is eating");
		last_meal = get_timestamp_in_ms(philo->start_time);
		usleep(philo->to_eat * 1000);
		pthread_mutex_unlock(&philo->mutex_fork_left);
		pthread_mutex_unlock(philo->mutex_fork_right);
		print_message(philo, "is sleeping");
		usleep(philo->to_sleep * 1000);
		print_message(philo, "is thinking");
		usleep(100);
	}
	return (NULL);
}

static long long	get_timestamp_in_ms(struct timeval start_time)
{
	struct timeval	current_time;
	long long		ms;

	gettimeofday(&current_time, NULL);
	ms = (current_time.tv_sec - start_time.tv_sec) * 1000;
	ms += (current_time.tv_usec - start_time.tv_usec) / 1000;
	return (ms);
}

static void	print_message(t_philo *philo, char *message)
{
	long long	timestamp;

	pthread_mutex_lock(philo->print_mutex);
	timestamp = get_timestamp_in_ms(philo->start_time);
	if (*(philo->sim_flag) == 1)
		printf("%lld %d %s\n", timestamp, philo->philo_id, message);
	pthread_mutex_unlock(philo->print_mutex);
}
