/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   death_monitor.c                                               :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/05/15 15:33:02 by aaycan                       #+#    #+#              */
/*   Updated: 2025/05/15 15:33:02 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

static void	death_monitor_pt_two(t_philo *philo, int i);

void	*death_monitor(void *philosophers)
{
	t_philo	*philo;
	int		i;

	philo = (t_philo *)philosophers;
	pthread_mutex_lock(philo[0].sim_mutex);
	pthread_mutex_unlock(philo[0].sim_mutex);
	while (check_sim(philo))
	{
		i = -1;
		while (++i < philo[0].num_of_philo)
			death_monitor_pt_two(philo, i);
		usleep(1000);
	}
	return (NULL);
}

static void	death_monitor_pt_two(t_philo *philo, int i)
{
	long long	current_time;

	current_time = get_timestamp_in_ms(philo[i].start_time);
	pthread_mutex_lock(&philo[i].m_last_meal_time);
	if (current_time - philo[i].last_meal_time >= philo[i].to_die)
	{
		pthread_mutex_lock(philo[i].print_mutex);
		pthread_mutex_lock(philo[i].sim_mutex);
		if (*(philo[i].sim_flag) == 1)
		{
			printf("%lld %d died\n", current_time, philo[i].philo_id);
			*(philo[i].sim_flag) = 0;
		}
		pthread_mutex_unlock(philo[i].sim_mutex);
		pthread_mutex_unlock(philo[i].print_mutex);
	}
	pthread_mutex_unlock(&philo[i].m_last_meal_time);
}
