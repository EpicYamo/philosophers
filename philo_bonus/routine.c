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
#include <stdlib.h>

static void	eat_philosopher(t_philo *philo);

void	*philo_routine(void *philosopher)
{
	t_philo		*philo;

	philo = (t_philo *)philosopher;
	while (1)
	{
		if (philo->done_eating == 0)
			eat_philosopher(philo);
		else
			exit(1);
		print_message(philo, "is sleeping");
		smart_sleep(philo->to_sleep, philo);
		print_message(philo, "is thinking");
	}
	exit(2);
}

static void	eat_philosopher(t_philo *philo)
{
	sem_wait(philo->s_fork);
	print_message(philo, "has taken a fork");
	sem_wait(philo->s_fork);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	philo->last_meal_time = get_timestamp_in_ms(philo->start_time);
	philo->current_meals++;
	smart_sleep(philo->to_eat, philo);
	if ((philo->required_meals != -1) && (philo->current_meals == philo->required_meals))
		philo->done_eating = 1;
	sem_post(philo->s_fork);
	sem_post(philo->s_fork);
}
