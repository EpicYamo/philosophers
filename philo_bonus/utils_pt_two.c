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

static void	destroy_semaphores_pt_two(t_philo *philosophers, int sem_count, int option);
static void	destroy_semaphores_pt_three(t_philo *philosophers, int sem_count, int option);

void	destroy_semaphores(t_philo *philosophers, int sem_count, int option)
{
	if (option > 0)
	{
		sem_destroy(philosophers[0].s_fork);
		free(philosophers[0].s_fork);
	}
	if (option > 1)
	{
		sem_destroy(philosophers[0].s_print);
		free(philosophers[0].s_print);
	}
	if (option > 2)
	{
		sem_destroy(philosophers[0].s_simulation);
		free(philosophers[0].s_simulation);
	}
	if (option > 3)
		destroy_semaphores_pt_two(philosophers, sem_count, option);
}

static void	destroy_semaphores_pt_two(t_philo *philosophers, int sem_count, int option)
{
	int	i;
	int	compare;

	if (option > 3)
	{
		if (option > 4)
			compare = philosophers[0].num_of_philo;
		else
			compare = sem_count;
		i = -1;
		while (++i < compare)
			sem_destroy(&philosophers[i].s_eat_perm);
	}
	if (option > 4)
	{
		if (option > 5)
			compare = philosophers[0].num_of_philo;
		else
			compare = sem_count;
		i = -1;
		while (++i < compare)
			sem_destroy(&philosophers[i].s_last_meal_time);
	}
	if (option > 5)
		destroy_semaphores_pt_three(philosophers, sem_count, option);
}

static void	destroy_semaphores_pt_three(t_philo *philosophers, int sem_count, int option)
{
	int	i;
	int	compare;

	if (option > 5)
	{
		if (option > 6)
			compare = philosophers[0].num_of_philo;
		else
			compare = sem_count;
		i = -1;
		while (++i < compare)
			sem_destroy(&philosophers[i].s_done_eating);
	}
}
