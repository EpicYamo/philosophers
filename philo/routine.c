/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   routine.c                                                     :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/29 21:28:11 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/29 21:28:11 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <pthread.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

static void	alone_philosopher(t_philo *philo);
static void	eat_philosopher(t_philo *philo);

void	*philo_routine(void *philosopher)
{
	t_philo		*philo;

	philo = (t_philo *)philosopher;
	if (philo->num_of_philo == 1)
		alone_philosopher(philo);
	else
	{
		while (*(philo->sim_flag) == 1)
		{
			print_message(philo, "is thinking");
			while (philo->allowed_to_eat != 0)
				usleep(1000);
			eat_philosopher(philo);
			print_message(philo, "is sleeping");
			smart_sleep(philo->to_sleep, philo);
			usleep(100);
		}
	}
	return (NULL);
}

static void	alone_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork_left);
	print_message(philo, "has taken a fork");
	smart_sleep(philo->to_die, philo);
	pthread_mutex_unlock(&philo->mutex_fork_left);
	print_message(philo, "died");
	*(philo->sim_flag) = 0;
}

static void	eat_philosopher(t_philo *philo)
{
	if (philo->philo_id % 2 == 1)
	{
		pthread_mutex_lock(&philo->mutex_fork_left);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(philo->mutex_fork_right);
		print_message(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->mutex_fork_right);
		print_message(philo, "has taken a fork");
		pthread_mutex_lock(&philo->mutex_fork_left);
		print_message(philo, "has taken a fork");
	}
	print_message(philo, "is eating");
	philo->last_meal_time = get_timestamp_in_ms(philo->start_time);
	smart_sleep(philo->to_eat, philo);
	philo->current_meals++;
	if ((philo->required_meals != -1) && (philo->current_meals == philo->required_meals))
		philo->done_eating = 1;
	pthread_mutex_unlock(&philo->mutex_fork_left);
	pthread_mutex_unlock(philo->mutex_fork_right);
}
