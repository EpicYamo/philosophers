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

static void	eat_philosopher(t_philo *philo);

void	*philo_routine(void *philosopher)
{
	t_philo		*philo;

	philo = (t_philo *)philosopher;
	if (philo->philo_id % 2 == 0)
		smart_sleep(1, philo);
	while (*(philo->sim_flag) == 1)
	{
		print_message(philo, "is thinking");
		pthread_mutex_lock(&philo->eat_perm_mutex);
		pthread_mutex_unlock(&philo->eat_perm_mutex);
		eat_philosopher(philo);
		print_message(philo, "is sleeping");
		smart_sleep(philo->to_sleep, philo);
	}
	return (NULL);
}

static void	eat_philosopher(t_philo *philo)
{
	pthread_mutex_lock(&philo->mutex_fork_left);
	print_message(philo, "has taken a fork");
	pthread_mutex_lock(philo->mutex_fork_right);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	philo->last_meal_time = get_timestamp_in_ms(philo->start_time);
	smart_sleep(philo->to_eat, philo);
	philo->current_meals++;
	if ((philo->required_meals != -1) && (philo->current_meals == philo->required_meals))
		philo->done_eating = 1;
	pthread_mutex_unlock(&philo->mutex_fork_left);
	pthread_mutex_unlock(philo->mutex_fork_right);
}
