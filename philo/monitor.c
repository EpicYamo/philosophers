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
static void	update_eating_permissions_pt_two(t_philo *philo, int *philo_count);

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
	int			philo_count;

	update_eating_permissions_pt_two(philo, &philo_count);
	if ((philo[0].last_meal_time > philo[1].last_meal_time)
		|| (philo[0].last_meal_time > philo[philo_count - 1].last_meal_time))
	{
		if (pthread_mutex_trylock(&philo[0].eat_perm_mutex) == 0)
			philo[0].who_locked_me = 1;
	}
	else
	{
		if (philo[0].who_locked_me == 1)
			pthread_mutex_unlock(&philo[0].eat_perm_mutex);
	}
	if ((philo[philo_count - 1].last_meal_time > philo[0].last_meal_time)
		|| (philo[philo_count - 1].last_meal_time > philo[philo_count - 2].last_meal_time))
	{
		if (pthread_mutex_trylock(&philo[philo_count - 1].eat_perm_mutex) == 0)
			philo[philo_count - 1].who_locked_me = 1;
	}
	else
	{
		if (philo[philo_count - 1].who_locked_me == 1)
			pthread_mutex_unlock(&philo[philo_count - 1].eat_perm_mutex);
	}		
}

static void	update_eating_permissions_pt_two(t_philo *philo, int *philo_count)
{
	int	i;

	i = -1;
	*philo_count = philo[0].num_of_philo;
	while (++i < *philo_count - 1)
	{
		if ((philo[i].last_meal_time > philo[i + 1].last_meal_time)
			|| (philo[i].last_meal_time > philo[i - 1].last_meal_time))
		{
			if (pthread_mutex_trylock(&philo[i].eat_perm_mutex) == 0)
				philo[i].who_locked_me = 1;
		}
		else
		{
			if (philo[i].who_locked_me == 1)
				pthread_mutex_unlock(&philo[i].eat_perm_mutex);
		}
	}
}
