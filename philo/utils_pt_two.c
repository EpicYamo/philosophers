/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   utils_pt_two.c                                                :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/04/29 21:19:06 by aaycan                       #+#    #+#              */
/*   Updated: 2025/04/29 21:19:06 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

static void	mutex_destroy_func_pt_two(t_philo *philosophers, int mutex_count, int option);
static void	mutex_destroy_func_pt_three(t_philo *philosophers, int option);

void mutex_destroy_func(t_philo *philosophers, int mutex_count, int option)
{
	int	i;
	int	compare;

	if (option > 0)
	{
		if (option > 1)
			compare = philosophers[0].num_of_philo;
		else
			compare = mutex_count;
		i = -1;
		while (++i < compare)
			pthread_mutex_destroy(&philosophers[i].mutex_fork_left);
	}
	if (option > 1)
	{
		if (option > 2)
			compare = philosophers[0].num_of_philo;
		else
			compare = mutex_count;
		i = -1;
		while (++i < compare)
			pthread_mutex_destroy(&philosophers[i].eat_perm_mutex);
	}
	if (option > 2)
		mutex_destroy_func_pt_two(philosophers, mutex_count, option);
}

static void	mutex_destroy_func_pt_two(t_philo *philosophers, int mutex_count, int option)
{
	int	i;
	int	compare;

	if (option > 2)
	{
		if (option > 3)
			compare = philosophers[0].num_of_philo;
		else
			compare = mutex_count;
		i = -1;
		while (++i < compare)
			pthread_mutex_destroy(&philosophers[i].m_last_meal_time);
	}
	if (option > 3)
	{
		if (option > 4)
			compare = philosophers[0].num_of_philo;
		else
			compare = mutex_count;
		i = -1;
		while (++i < compare)
			pthread_mutex_destroy(&philosophers[i].m_done_eating);
	}
	if (option > 4)
		mutex_destroy_func_pt_three(philosophers, option);
}

static void	mutex_destroy_func_pt_three(t_philo *philosophers, int option)
{
	if (option > 4)
	{
		if (philosophers[0].print_mutex)
		{
			pthread_mutex_destroy(philosophers[0].print_mutex);
			free(philosophers[0].print_mutex);
		}
	}
	if (option > 5)
	{
		if (philosophers[0].sim_mutex)
		{
			pthread_mutex_destroy(philosophers[0].sim_mutex);
			free(philosophers[0].sim_mutex);
		}
	}
}
