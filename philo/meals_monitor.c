/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   meals_monitor.c                                               :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/05/13 16:22:55 by aaycan                       #+#    #+#              */
/*   Updated: 2025/05/13 16:22:55 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

void	*meals_monitor(void *philosophers)
{
	t_philo	*philo;
	int		all_done;
    int     i;

	philo = (t_philo *)philosophers;
	while (*(philo->sim_flag) == 1)
	{
		all_done = 1;
        i = -1;
        while(++i < philo[0].num_of_philo)
        {
            if ((philo[i].required_meals != -1) && (philo[i].done_eating == 0))
			    all_done = 0;
        }
		if ((philo[0].required_meals != -1) && (all_done == 1))
		{
			pthread_mutex_lock(philo[0].print_mutex);
			*(philo[0].sim_flag) = 0;
			pthread_mutex_unlock(philo[0].print_mutex);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
