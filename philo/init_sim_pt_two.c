/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   init_sim_pt_two.c                                             :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/29 21:25:07 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/29 21:25:07 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

static int	init_philo_mutex_pt_two(t_philo *philosophers, int philo_count);
static void	init_philo_mutex_pt_three(t_philo *philosophers, int philo_count);

int	init_sim_flag(t_philo *philosophers, int philo_count)
{
	int	i;
	int	*simulation_flag;

	simulation_flag = malloc(sizeof(int));
	if (!simulation_flag)
		return (1);
	*simulation_flag = 1;
	i = -1;
	while (++i < philo_count)
		philosophers[i].sim_flag = simulation_flag;
	return (0);
}

int	init_philo_mutex(t_philo *philosophers, int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
	{
		if (pthread_mutex_init(&philosophers[i].mutex_fork_left, NULL) != 0)
		{
			mutex_destroy_func(philosophers, i - 1, 1);
			return (1);
		}
	}
	i = -1;
	while (++i < philo_count)
	{
		if (pthread_mutex_init(&philosophers[i].eat_perm_mutex, NULL) != 0)
		{
			mutex_destroy_func(philosophers, i - 1, 2);
			return (1);
		}
	}
	if (init_philo_mutex_pt_two(philosophers, philo_count) != 0)
		return (1);
	init_philo_mutex_pt_three(philosophers, philo_count);
	return (0);
}

static int	init_philo_mutex_pt_two(t_philo *philosophers, int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
	{
		if (pthread_mutex_init(&philosophers[i].m_last_meal_time, NULL) != 0)
		{
			mutex_destroy_func(philosophers, i - 1, 3);
			return (1);
		}
	}
	i = -1;
	while (++i < philo_count)
	{
		if (pthread_mutex_init(&philosophers[i].m_done_eating, NULL) != 0)
		{
			mutex_destroy_func(philosophers, i - 1, 4);
			return (1);
		}
	}
	return (0);
}

static void	init_philo_mutex_pt_three(t_philo *philosophers, int philo_count)
{
	int	i;

	if (philosophers->num_of_philo == 1)
		philosophers[0].mutex_fork_right = NULL;
	else
	{
		i = 1;
		philosophers[0].mutex_fork_right = &(philosophers[philo_count - 1].mutex_fork_left);
		while (i < philo_count)
		{
			philosophers[i].mutex_fork_right = &(philosophers[i - 1].mutex_fork_left);
			i++;
		}
	}
}
