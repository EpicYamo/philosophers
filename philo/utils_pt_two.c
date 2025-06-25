/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_pt_two.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/25 16:48:40 by aaycan            #+#    #+#             */
/*   Updated: 2025/06/25 17:05:07 by aaycan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

static void	mutex_destroy_func_pt_two(t_philo *philosophers, int option);

void	mutex_destroy_func(t_philo *philosophers, int mutex_count, int option)
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
			pthread_mutex_destroy(&philosophers[i].m_last_meal_time);
	}
	if (option > 2)
		mutex_destroy_func_pt_two(philosophers, option);
}

static void	mutex_destroy_func_pt_two(t_philo *philosophers, int option)
{
	if (option > 2)
	{
		if (philosophers[0].print_mutex)
		{
			pthread_mutex_destroy(philosophers[0].print_mutex);
			free(philosophers[0].print_mutex);
		}
	}
	if (option > 3)
	{
		if (philosophers[0].sim_mutex)
		{
			pthread_mutex_destroy(philosophers[0].sim_mutex);
			free(philosophers[0].sim_mutex);
		}
	}
}
