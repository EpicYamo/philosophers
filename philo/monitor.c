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
#include <pthread.h>
#include <stdio.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

static int	check_philosophers(t_philo *philo, int *all_done);
static void	update_eating_permissions(t_philo *philo);

void	*monitor(void *philosophers)
{
	t_philo	*philo;
	int		all_done;

	philo = (t_philo *)philosophers;
	while (*(philo->sim_flag) == 1)
	{
		all_done = 1;
		if (check_philosophers(philo, &all_done))
			return (NULL);
		if ((philo[0].required_meals != -1) && (all_done == 1))
		{
			pthread_mutex_lock(philo[0].print_mutex);
			*(philo[0].sim_flag) = 0;
			pthread_mutex_unlock(philo[0].print_mutex);
			return (NULL);
		}
		update_eating_permissions(philo);
		usleep(500);
	}
	return (NULL);
}

static int	check_philosophers(t_philo *philo, int *all_done)
{
	int			i;
	long long	current_time;

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
			return (1);
		}
		if ((philo[i].required_meals != -1) && (philo[i].done_eating == 0))
			*all_done = 0;
	}
	return (0);
}

static void	update_eating_permissions(t_philo *philo)
{
	int			i;
	long long	curr;
	long long	left;
	long long	right;
	int			philo_count;

	philo_count = philo[0].num_of_philo;
	curr = philo[0].last_meal_time;
	left = philo[1].last_meal_time;
	right = philo[philo_count - 1].last_meal_time;
	if ((curr > left) || (curr > right))
		philo[0].allowed_to_eat = 1;
	else
		philo[0].allowed_to_eat = 0;
	i = 1;
	while (i < philo_count - 1)
	{
		curr = philo[i].last_meal_time;
		left = philo[i + 1].last_meal_time;
		right = philo[i - 1].last_meal_time;
		if ((curr > left) || (curr > right))
			philo[i].allowed_to_eat = 1;
		else
			philo[i].allowed_to_eat = 0;
		i++;
	}
	curr = philo[philo_count - 1].last_meal_time;
	left = philo[0].last_meal_time;
	right = philo[philo_count - 2].last_meal_time;
	if ((curr > left) || (curr > right))
		philo[philo_count - 1].allowed_to_eat = 1;
	else
		philo[philo_count - 1].allowed_to_eat = 0;
}
