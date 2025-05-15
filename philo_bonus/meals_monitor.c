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
			sem_wait(&philo[i].s_done_eating);
            if (philo[i].done_eating == 0)
			    all_done = 0;
			sem_post(&philo[i].s_done_eating);
        }
		if (all_done == 1)
		{
			sem_wait(philo[0].s_simulation);
			*(philo[0].sim_flag) = 0;
			sem_post(philo[0].s_simulation);
			return (NULL);
		}
		usleep(500);
	}
	return (NULL);
}
