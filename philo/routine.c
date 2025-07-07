/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:48:23 by aaycan            #+#    #+#             */
/*   Updated: 2025/07/07 21:26:22 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <limits.h>

static void	eat_philosopher(t_philo *philo);
static void	routine_prep(t_philo *philo);

void	*philo_routine(void *philosopher)
{
	t_philo		*philo;

	philo = (t_philo *)philosopher;
	routine_prep(philo);
	while (check_sim(philo))
	{
		eat_philosopher(philo);
		if (philo->done_eating == 1)
			break ;
		print_message(philo, "is sleeping");
		smart_sleep(philo->to_sleep, philo);
		print_message(philo, "is thinking");
		if (philo->num_of_philo % 2 == 1)
			smart_sleep(((philo->to_eat * 2) - philo->to_sleep), philo);
		else
			smart_sleep((philo->to_eat - philo->to_sleep), philo);
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
	philo->current_meals++;
	smart_sleep(philo->to_eat, philo);
	if ((philo->required_meals != -1)
		&& (philo->current_meals == philo->required_meals))
		philo->done_eating = 1;
	pthread_mutex_unlock(&philo->mutex_fork_left);
	pthread_mutex_unlock(philo->mutex_fork_right);
}

static void	routine_prep(t_philo *philo)
{
	pthread_mutex_lock(philo->sim_mutex);
	pthread_mutex_unlock(philo->sim_mutex);
	gettimeofday(&philo->start_time, NULL);
	philo->last_meal_time = get_timestamp_in_ms(philo->start_time);
	if (philo->philo_id % 2 == 0)
		smart_sleep(10, philo);
	if ((philo->num_of_philo % 2 == 1)
		&& (philo->philo_id == philo->num_of_philo))
		smart_sleep(((philo->to_eat * 3) - philo->to_sleep), philo);
}
