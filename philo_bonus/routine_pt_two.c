/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_pt_one.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 17:09:04 by aaycan            #+#    #+#             */
/*   Updated: 2025/06/25 17:24:58 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	eat_philosopher(t_philo *philo)
{
	sem_wait(philo->s_fork);
	print_message(philo, "has taken a fork");
	sem_wait(philo->s_fork);
	print_message(philo, "has taken a fork");
	print_message(philo, "is eating");
	philo->last_meal_time = get_timestamp_in_ms(philo->start_time);
	philo->current_meals++;
	smart_sleep(philo->to_eat, philo);
	if ((philo->required_meals != -1)
		&& (philo->current_meals == philo->required_meals))
		philo->done_eating = 1;
	sem_post(philo->s_fork);
	sem_post(philo->s_fork);
}

void	alone_philosopher(t_philo *philo)
{
	print_message(philo, "has taken a fork");
	smart_sleep(philo->to_die, philo);
}

void	*end_sim_monitor(void *philosopher)
{
	t_philo	*philo;

	philo = (t_philo *)philosopher;
	sem_wait(philo->s_death);
	philo->sim_flag = 0;
	return (NULL);
}
