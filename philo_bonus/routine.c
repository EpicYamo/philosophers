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
#include <stdlib.h>
#include <stdio.h>

static void	eat_philosopher(t_philo *philo);
static void	alone_philosopher(t_philo *philo);
static void	*end_sim_monitor(void *philosopher);
static void	philo_loop(t_philo *philo);

void	*philo_routine(t_philo *philo)
{
	int	thread_creation;

	thread_creation = 1;
	if (pthread_create(&philo->end_sim_mon, NULL, &end_sim_monitor, philo) != 0)
	{
		end_sim_func(philo);
		printf("Thread Creation at Philo: %d Failed Ending the Simulation\n", philo->philo_id);
		philo->sim_flag = 0;
		thread_creation = 0;
	}
	sem_wait(philo->s_print);
	sem_post(philo->s_print);
	philo_loop(philo);
	if (thread_creation == 1)
		pthread_join(philo->end_sim_mon, NULL);
	sem_close(philo->s_death);
	sem_close(philo->s_fork);
	sem_close(philo->s_print);
	if (philo->dead_flag == 1)
		exit(3);
	else
		exit(EXIT_SUCCESS);
}

static void	philo_loop(t_philo *philo)
{
	if (philo->philo_id % 2 == 1)
		smart_sleep(1, philo);
	if (philo->num_of_philo == 1)
		alone_philosopher(philo);
	else
	{
		while (check_sim(philo))
		{
			eat_philosopher(philo);
			if (philo->done_eating == 1)
				break;
			print_message(philo, "is sleeping");
			smart_sleep(philo->to_sleep, philo);
			print_message(philo, "is thinking");
			if (philo->num_of_philo % 2 == 1)
				smart_sleep(((philo->to_eat * 2) - philo->to_sleep), philo);
			else
				smart_sleep((philo->to_eat - philo->to_sleep), philo);
		}
	}
	if (philo->done_eating == 1)
	{
		smart_sleep((philo->to_eat * 2), philo);
		sem_post(philo->s_death);
	}
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

static void alone_philosopher(t_philo *philo)
{
	print_message(philo, "has taken a fork");
	smart_sleep(philo->to_die, philo);
}

static void	*end_sim_monitor(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	sem_wait(philo->s_death);
	philo->sim_flag = 0;
	return (NULL);
}
