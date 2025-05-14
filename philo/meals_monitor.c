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
	while (check_sim(philo))
	{
		all_done = 1;
        i = -1;
        while(++i < philo[0].num_of_philo)
        {
			pthread_mutex_lock(&philo[i].m_done_eating);
            if (philo[i].done_eating == 0)
			    all_done = 0;
			pthread_mutex_unlock(&philo[i].m_done_eating);
        }
		if (all_done == 1)
		{
			pthread_mutex_lock(philo[0].sim_mutex);
			*(philo[0].sim_flag) = 0;
			pthread_mutex_unlock(philo[0].sim_mutex);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
