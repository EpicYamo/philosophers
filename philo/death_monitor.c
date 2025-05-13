/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   monitor.c                                                     :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/29 21:28:13 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/29 21:28:13 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <unistd.h>
#include <stdio.h>

void	*death_monitor(void *philosophers)
{
	t_philo		*philo;
	int			i;
	long long	current_time;

	philo = (t_philo *)philosophers;
	while (*(philo->sim_flag) == 1)
	{
		i = -1;
		while (++i < philo[0].num_of_philo)
		{
			current_time = get_timestamp_in_ms(philo[i].start_time);
			if (current_time - philo[i].last_meal_time >= philo[i].to_die)
			{
				pthread_mutex_lock(philo[i].print_mutex);
				if (*(philo[i].sim_flag) == 1)
				{
					printf("%lld %d died\n", current_time, philo[i].philo_id);
					*(philo[i].sim_flag) = 0;
				}
				pthread_mutex_unlock(philo[i].print_mutex);
			}
		}
		usleep(500);
	}
	return (NULL);
}
