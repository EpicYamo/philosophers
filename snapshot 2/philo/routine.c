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

static void	eat_philosopher(t_philo *philo);

void	*philo_routine(void *philosopher)
{
	t_philo		*philo;

	philo = (t_philo *)philosopher;
	if (philo->philo_id % 2 == 1)
		usleep(1);
	while (*(philo->sim_flag) == 1)
	{
		print_message(philo, "is thinking");
		while(((philo->last_meal_time) > (philo->philo_left->last_meal_time))
			|| ((philo->last_meal_time) > (philo->philo_right->last_meal_time)))
			usleep(100);
		eat_philosopher(philo);
		philo->current_meals++;
		if ((philo->required_meals != -1) && (philo->current_meals == philo->required_meals))
			philo->done_eating = 1;
		print_message(philo, "is sleeping");
		usleep(philo->to_sleep * 1000);
		usleep(100);
	}
	return (NULL);
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
	usleep(philo->to_eat * 1000);
	pthread_mutex_unlock(&philo->mutex_fork_left);
	pthread_mutex_unlock(philo->mutex_fork_right);
}
