/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   eat_perm_monitor.c                                            :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/05/13 16:22:49 by aaycan                       #+#    #+#              */
/*   Updated: 2025/05/13 16:22:49 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <unistd.h>

static int	mutex_control(t_philo *philo);

void	*eat_perm_monitor(void *philosophers)
{
	t_philo	*philo;
	int		philo_count;
	int		i;

	philo = (t_philo *)philosophers;
	philo_count = philo[0].num_of_philo;
	while (check_sim(philo))
	{
		if ((philo[0].eat_perm_mutex_flag != 1)
			&& (philo[0].last_meal_time > philo[philo_count - 1].last_meal_time
			|| philo[0].last_meal_time > philo[1].last_meal_time))
		{
			if (pthread_mutex_trylock(&philo[0].eat_perm_mutex) == 0)
				philo[0].eat_perm_mutex_flag = 1;
		}
		else if ((philo[0].eat_perm_mutex_flag == 1)
				&& ((philo[0].last_meal_time <= philo[philo_count - 1].last_meal_time)
				&& philo[0].last_meal_time <= philo[1].last_meal_time))
		{
			pthread_mutex_unlock(&philo[0].eat_perm_mutex);
			philo[0].eat_perm_mutex_flag = 0;
		}
		if ((philo[philo_count - 1].eat_perm_mutex_flag != 1)
			&& (philo[philo_count - 1].last_meal_time > philo[0].last_meal_time
			|| philo[philo_count - 1].last_meal_time > philo[philo_count - 2].last_meal_time))
		{
			if (pthread_mutex_trylock(&philo[philo_count - 1].eat_perm_mutex) == 0)
				philo[philo_count - 1].eat_perm_mutex_flag = 1;
		}
		else if ((philo[philo_count - 1].eat_perm_mutex_flag == 1)
				&& ((philo[philo_count - 1].last_meal_time <= philo[0].last_meal_time)
				&& philo[philo_count - 1].last_meal_time <= philo[philo_count - 2].last_meal_time))
		{
			pthread_mutex_unlock(&philo[philo_count - 1].eat_perm_mutex);
			philo[philo_count - 1].eat_perm_mutex_flag = 0;
		}
		i = 0;
		while (++i < (philo_count - 1))
		{
			if ((philo[i].eat_perm_mutex_flag != 1)
				&& (philo[i].last_meal_time > philo[i + 1].last_meal_time
				|| philo[i].last_meal_time > philo[i - 1].last_meal_time))
			{
				if(pthread_mutex_trylock(&philo[i].eat_perm_mutex) == 0)
					philo[i].eat_perm_mutex_flag = 1;
			}
			else if ((philo[i].eat_perm_mutex_flag == 1)
					&& ((philo[i].last_meal_time <= philo[i + 1].last_meal_time)
					&& philo[i].last_meal_time <= philo[i - 1].last_meal_time))
			{
				pthread_mutex_unlock(&philo[i].eat_perm_mutex);
				philo[i].eat_perm_mutex_flag = 0;
			}
		}
		usleep(500);
	}
	mutex_control(philo);
	return (NULL);
}

static int	mutex_control(t_philo *philo)
{
	int	i;

	i = -1;
	while (++i < philo[0].num_of_philo)
	{
		if (philo[i].eat_perm_mutex_flag == 1)
		{
			pthread_mutex_unlock(&philo[i].eat_perm_mutex);
			philo[i].eat_perm_mutex_flag = 0;
		}
	}
	return (0);
}
