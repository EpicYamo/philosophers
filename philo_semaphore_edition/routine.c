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
#include <unistd.h>
#include <limits.h>

static void	eat_philosopher(t_philo *philo);

void	*philo_routine(void *philosopher)
{
	t_philo		*philo;

	philo = (t_philo *)philosopher;
	if (philo->philo_id % 2 == 0)
		smart_sleep(1, philo);
	if (philo->num_of_philo % 2 == 1)
		smart_sleep(1, philo);
	while (check_sim(philo))
	{
		sem_wait(&philo->s_eat_perm);
		sem_post(&philo->s_eat_perm);
		if (philo->done_eating == 0)
			eat_philosopher(philo);
		else
		{
			sem_wait(&philo->s_last_meal_time);
			philo->last_meal_time = LLONG_MAX;
			sem_post(&philo->s_last_meal_time);
			break;
		}
		print_message(philo, "is sleeping");
		smart_sleep(philo->to_sleep, philo);
		print_message(philo, "is thinking");
	}
	return (NULL);
}

static void	eat_philosopher(t_philo *philo)
{
	sem_wait(philo->s_fork);
	print_message(philo, "has taken a fork");
	sem_wait(philo->s_fork);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	sem_wait(&philo->s_last_meal_time);
	philo->last_meal_time = get_timestamp_in_ms(philo->start_time);
	sem_post(&philo->s_last_meal_time);
	philo->current_meals++;
	smart_sleep(philo->to_eat, philo);
	if ((philo->required_meals != -1) && (philo->current_meals == philo->required_meals))
	{
		sem_wait(&philo->s_done_eating);
		philo->done_eating = 1;
		sem_post(&philo->s_done_eating);
	}
	sem_post(philo->s_fork);
	sem_post(philo->s_fork);
}
