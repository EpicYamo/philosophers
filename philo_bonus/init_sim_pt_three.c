/* ************************************************************************************** */
/*                                                                                        */
/*                                                                   :::      ::::::::    */
/*   init_sim_pt_three.c                                           :+:      :+:    :+:    */
/*                                                               +:+ +:+         +:+      */
/*   By: aaycan <aaycan@student.42kocaeli.com.tr>              +#+  +:+       +#+         */
/*                                                           +#+#+#+#+#+   +#+            */
/*   Created: 2025/05/15 19:05:17 by aaycan                       #+#    #+#              */
/*   Updated: 2025/05/15 19:05:17 by aaycan                      ###   ########.tr        */
/*                                                                                        */
/* ************************************************************************************** */

#include "philosophers.h"
#include <stdlib.h>

static int	init_philo_semaphores_pt_two(t_philo *philosophers, int philo_count);

int	init_philo_semaphores(t_philo *philosophers, int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
	{
		if (sem_init(&philosophers[i].s_eat_perm, 0, 1) != 0)
		{
			destroy_semaphores(philosophers, i - 1, 4);
			return (1);
		}
	}
	i = -1;
	while (++i < philo_count)
	{
		if (sem_init(&philosophers[i].s_last_meal_time, 0, 1) != 0)
		{
			destroy_semaphores(philosophers, i - 1, 5);
			return (1);
		}
	}
	if (init_philo_semaphores_pt_two(philosophers, philo_count) != 0)
		return (1);
	return (0);
}

static int	init_philo_semaphores_pt_two(t_philo *philosophers, int philo_count)
{
	int	i;

	i = -1;
	while (++i < philo_count)
	{
		if (sem_init(&philosophers[i].s_done_eating, 0, 1) != 0)
		{
			destroy_semaphores(philosophers, i - 1, 6);
			return (1);
		}
	}
	return (0);
}
